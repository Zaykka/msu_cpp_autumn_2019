#include <iostream>
#include <iterator>


template <class T>
class Allocator
{
public:
    T* allocate(size_t cnt) {
        return static_cast<T*>(operator new(cnt * sizeof(T)));
    }
    
    void deallocate(T* ptr, size_t cnt) {
        operator delete (ptr, cnt * sizeof(T));
    }
    
    template<class... Args>
    void construct(T* p, Args&&... args) {
        new(p) T(std::forward<Args>(args)...);
    }
    
    void destroy(T* p) {
        p->~T();
    }
};

template <class T>
class Iterator :public std::iterator<std::random_access_iterator_tag,T>
{
    T*  ptr;
public:
    explicit Iterator(T* ptr_) : ptr(ptr_){}
    
    bool operator==(const Iterator<T>& other) const {
        return ptr == other.ptr;
    }
    
    bool operator!=(const Iterator<T>& other) const {
        return !(ptr == other.ptr);
    }
    
    T& operator*() const {
        return *ptr;
    }
    
    Iterator& operator++() {
        ++ptr;
        return *this;
    }
    Iterator& operator--() {
        --ptr;
        return *this;
    }
    
};

template <class T>
class Vector
{
    Allocator<T> alloc_;
    T* data_;
    size_t cur_size;
    size_t size_;
    T* ptr;
public:
    explicit Vector(size_t cnt = 0): ptr(alloc_.allocate(cnt)), cur_size(cnt), size_(cnt) {
        for (size_t i = 0; i < cur_size; ++i) {
            alloc_.construct(ptr + i);
        }
    }
    
    ~Vector() {
        while (cur_size > 0) {
            alloc_.destroy(ptr + cur_size);
            --cur_size;
        }
        alloc_.deallocate(ptr, size_);
    }
    
     Iterator<T> begin() const {
        return Iterator<T>(ptr);
    }
   
    Iterator<T> end() const {
        return Iterator<T>(ptr + cur_size);
    }

    std::reverse_iterator<Iterator<T>> rbegin(){
        return std::reverse_iterator<Iterator<T>>(end());
    }

    std::reverse_iterator<Iterator<T>> rend(){
        return std::reverse_iterator<Iterator<T>>(begin());
    }
    
    T& operator[](size_t ind) {
        return ptr[ind];
    }
    
    const T& operator[](size_t ind) const {
        return ptr[ind];
    }
    
    void pop_back(T &&value) {
        --cur_size;
        alloc_.destroy(ptr + cur_size);
    }
    
    void add(size_t capacity) {
        if (capacity <= cur_size) {
            return;
        }
        T* tmp = alloc_.allocate(capacity);
        
        for (int i = 0; i < cur_size; ++i) {
            alloc_.construct(tmp + i, ptr[i]);
            alloc_.destroy(ptr + i);
        }
        alloc_.deallocate(ptr, size_);
        ptr = tmp;
        size_ = capacity;
    }
    
    void push_back(const T& val) {
        if (cur_size >= size_) {
            add(2 * size_ + 1);
        }
        alloc_.construct(ptr + cur_size, val);
        ++cur_size;
    }
    
    void resize(size_t n) {
        if (n < cur_size) {
            for (T* p = ptr + n; ptr != ptr + size_; ++p) {
                alloc_.destroy(p);
            }
            cur_size = n;
            return;
        }
        if (n >= size_) {
            this->add(n);
        }
        for (T* p = ptr + cur_size; p != ptr + n; ++p) {
            alloc_.construct(p);
        }
        cur_size = n;
        return;
    }
    
    size_t size() const {
        return cur_size;
    }

    size_t capacity(){
        return size;
    }

    bool empty() const {
        return cur_size == 0;
    }
    
    void clear() {
        while (cur_size > 0){
            alloc_.destroy(data_ + cur_size);
            --cur_size;
        }
    }
};



