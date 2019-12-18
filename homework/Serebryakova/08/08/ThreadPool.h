#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <functional>
#include <vector>
#include <queue>


class ThreadPool {
    std::vector<std::thread> pool;
    std::mutex mtx;
    std::queue<std::function<void()> > queueProblems;
    size_t size;
    std::atomic<bool> done;
    std::condition_variable new_;

    void work() {
        while(!done) {
            std::unique_lock<std::mutex> lock(mtx);
            if (queueProblems.empty()) {
                new_.wait(lock);
            } else {
                auto problem(std::move(queueProblems.front()));
                queueProblems.pop();
                lock.unlock();
                problem();
            }
        }
    }

public:
    explicit ThreadPool(size_t poolSize) :size(poolSize), done(false) {
        for(int i = 0; i < poolSize; ++i) {
            pool.emplace_back(std::thread([this]() {
                this->work();
            }));
        }
    }
    
    ~ThreadPool() {
        done = true;
        new_.notify_all();
        for(int i = 0; i < size; i++) {
            pool[i].join();
        }
    }
    
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
        auto problem = std::make_shared<std::packaged_task<decltype(func(args...))()> >([func, args...](){
            return func(args...);
        });
        auto res = problem->get_future();
        std::unique_lock<std::mutex> lock(mtx);
        queueProblems.push([problem]() {(*problem)();});
        new_.notify_one();
        return res;
    }
};



