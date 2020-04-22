#ifndef MSU_CPP_SPRING_2020_VECTOR_HPP
#define MSU_CPP_SPRING_2020_VECTOR_HPP

#include <iostream>

template<class T>
class Allocator
{
public:
    [[nodiscard]] T *allocate(size_t count)
    {
        return static_cast<T *>(operator new[](sizeof(T) * count));
    }

    void deallocate(T *ptr, size_t count)
    {
        operator delete[](ptr, sizeof(T) * count);
    }

    template<class... Args>
    static void construct(T *ptr, Args &&... args)
    {
        new(ptr) T(std::forward<Args>(args)...);
    }

    void destroy(T *ptr)
    {
        ptr->~T();
    }
};

template<class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
    T *ptr_;
public:
    using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;

    explicit Iterator(T *ptr) : ptr_(ptr)
    {}

    T &operator*() const
    {
        return *ptr_;
    }

    Iterator &operator++()
    {
        ++ptr_;
        return *this;
    }

    Iterator &operator--()
    {
        --ptr_;
        return *this;
    }

    Iterator &operator+=(difference_type n)
    {
        ptr_ += n;
        return *this;
    }

    Iterator &operator-=(difference_type n)
    {
        ptr_ -= n;
        return *this;
    }

    Iterator operator+(difference_type n) const
    {
        return Iterator(ptr_ + n);
    }

    Iterator operator-(difference_type n) const
    {
        return Iterator(ptr_ - n);
    }

    friend Iterator operator+(difference_type left, const Iterator &right)
    { return Iterator(left + right.ptr_); }

    friend Iterator operator-(difference_type left, const Iterator &right)
    { return Iterator(left - right.ptr_); }

    Iterator &operator[](int n)
    {
        return ptr_[n];
    }

    bool operator==(const Iterator<T> &other) const
    {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator<T> &other) const
    {
        return !(*this == other);
    }

    bool operator<(const Iterator<T> &other) const
    {
        return (this->ptr_ - other.ptr_ < 0);
    }

    bool operator>(const Iterator<T> &other) const
    {
        return other < *this;
    }

    bool operator>=(const Iterator<T> &other) const
    {
        return !(*this < other);
    }

    bool operator<=(const Iterator<T> &other) const
    {
        return !(*this > other);
    }
};

template<class T>
class Vector
{
private:
    Allocator<T> alloc_;
    T *data_;
    size_t size_;
    size_t max_size_;
public:

    explicit Vector(size_t size = 0) : size_(size), max_size_(size * 2)
    {
        data_ = alloc_.allocate(max_size_);
        for (size_t i = 0; i < size; ++i)
            alloc_.construct(data_ + i);
    }

    ~Vector()
    {
        for (size_t i = 0; i < size_; ++i)
            alloc_.destroy(data_ + i);
        alloc_.deallocate(data_, max_size_);
    }

    T &operator[](size_t pos)
    {
        if (pos < size_)
            return data_[pos];
        else
            throw std::out_of_range("out of range");
    }

    void push_back(const T &elem)
    {
        if (size_ >= max_size_)
            reserve(max_size_ + max_size_);
        new(data_ + size_++) T(elem);
    }

    void pop_back()
    {
        if (size_)
            alloc_.destroy(data_ + --size_);
    }

    bool empty() const
    {
        return !size_;
    }

    size_t size() const
    {
        return size_;
    }

    void clear()
    {
        for (size_t i = 0; i < size_; ++i)
            alloc_.destroy(data_ + i);
        size_ = 0;
    }

    Iterator<T> begin()
    {
        return Iterator<T>(data_);
    }

    Iterator<T> end()
    {
        return Iterator<T>(data_ + size_);
    }

    std::reverse_iterator<Iterator<T>> rbegin()
    {
        return std::reverse_iterator<Iterator<T>>(Iterator<T>(data_ + size_));
    }

    std::reverse_iterator<Iterator<T>> rend()
    {
        return std::reverse_iterator<Iterator<T>>(Iterator<T>(data_));
    }

    size_t capacity() const
    {
        return max_size_;
    }

    void resize(size_t new_size)
    {
        if (new_size < size_) {
            for (size_t i = new_size; i < size_; ++i)
                alloc_.destroy(data_ + i);
        } else {
            if (new_size > max_size_)
                reserve(new_size);
            for (size_t i = size_; i < new_size; ++i)
                alloc_.construct(data_ + i);
        }
        size_ = new_size;
    }

    void reserve(size_t new_size)
    {
        if (new_size > max_size_) {
            T *tmp = alloc_.allocate(new_size);
            for (size_t i = 0; i < size_; ++i) {
                new(tmp + i) T(data_[i]);
                alloc_.destroy(data_ + i);
            }
            alloc_.deallocate(data_, max_size_);
            max_size_ = new_size;
            data_ = tmp;
        }
    }
};

#endif //MSU_CPP_SPRING_2020_VECTOR_HPP
