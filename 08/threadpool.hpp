#ifndef MSU_CPP_SPRING_2020_THREADPOOL_HPP
#define MSU_CPP_SPRING_2020_THREADPOOL_HPP
//Создаем N потоков, каждый поток либо выполняет задачу, либо спит
//Новая задача добавляется в очередь, при этом происходит оповещение спящих потоков
//Проснувшись поток проверяет, что в очереди есть задача, после чего извлекает ее из очереди и выполняет
//Если задачи нет, поток засыпает ожидая оповещения
#include <thread>
#include <future>
#include <queue>

class ThreadPool
{
    std::thread *pools_;
    std::mutex mutex_;
    std::condition_variable condition_;
    std::queue<std::function<void()>> tasks_;
    size_t pool_count_;
    volatile bool active_ = true;
public:
    explicit ThreadPool(size_t poolSize)
    {
        pool_count_ = poolSize;
        pools_ = new std::thread[pool_count_];
        for (size_t i = 0; i < poolSize; ++i) {
            pools_[i] = std::thread([this]() {
                while (true) {
                    std::unique_lock<std::mutex> lock(mutex_);
                    condition_.wait(lock, [this]() {
                        return !(active_ && tasks_.empty());
                    });
                    if (active_) {
                        if (tasks_.empty())
                            continue;
                        auto task = std::move(tasks_.front());
                        tasks_.pop();
                        lock.unlock();
                        task();
                    } else
                        return;
                }
            });
            pools_[i].detach();
        }
    }

    ~ThreadPool()
    {
        active_ = false;
        condition_.notify_all();
    }

    // pass arguments by value
    template<class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>
    {
        auto binded_func = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
        auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>(binded_func);
        std::unique_lock<std::mutex> lock(mutex_);
        tasks_.emplace([task]() { (*task)(); });
        condition_.notify_one();
        return task->get_future();
    }
};

#endif //MSU_CPP_SPRING_2020_THREADPOOL_HPP
