#include <iostream>
#include <fstream>
#include <thread>
#include <queue>
#include <sstream>

class ThreadPool
{
    std::vector<std::thread> pools_;
    std::vector<bool> busy_;
    std::mutex mutex_;
    std::condition_variable condition_;
    std::condition_variable finished_;
    std::queue<std::string> lines_;
    size_t pool_count_;
    bool active_ = true;
    int result_ = 0;
public:
    explicit ThreadPool(size_t poolSize)
    {
        pool_count_ = poolSize;
        for (size_t i = 0; i < pool_count_; ++i) {
            busy_.push_back(false);
            pools_.emplace_back(std::thread([this, i]() {
                while (true) {
                    std::unique_lock<std::mutex> lock(mutex_);
                    condition_.wait(lock, [this]() {
                        return !(active_ && lines_.empty());
                    });
                    if (active_) {
                        if (lines_.empty())
                            continue;
                        auto line = std::move(lines_.front());
                        lines_.pop();
                        busy_[i] = true;
                        lock.unlock();
                        // Считаем сумму строки
                        int sum = 0;
                        int buf;
                        std::istringstream iss(line);
                        while (iss >> buf) {
                            sum += buf;
                        }
                        // Пишем результат
                        lock.lock();
                        result_ += sum;
                        busy_[i] = false;
                        finished_.notify_all();
                    } else
                        return;
                }
            }));
        }
    }

    ~ThreadPool()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        active_ = false;
        lock.unlock();
        condition_.notify_all();
        for (auto &pool: pools_)
            pool.join();
    }

    void sum_string(std::string &str)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        lines_.emplace(str);
        condition_.notify_one();
    }

    int get_sum()
    {
        // Ждем пока все досчитают
        std::unique_lock<std::mutex> lock(mutex_);
        finished_.wait(lock, [this]() {
            return (lines_.empty() && std::none_of(busy_.begin(), busy_.end(), [](bool b) { return b; }));
        });
        return result_;
    }
};

int main()
{
    std::string str_buf;
    std::filebuf fb;
    ThreadPool pool(2);
    if (fb.open("input.txt", std::ios::in)) {
        std::istream is(&fb);
        while (std::getline(is, str_buf)) {
            pool.sum_string(str_buf);
        }
        std::cout << pool.get_sum() << std::endl;
        fb.close();
    }
    return 0;
}