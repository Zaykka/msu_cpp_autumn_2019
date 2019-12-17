#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <future>


class ThreadPool
{
    std::vector<std::thread> pool;
    std::mutex mtx;
    std::queue<std::function<void()> > queueProblems;
    int size;
    bool done;
    std::condition_variable new_;
    
    template <class T, class S, class... Args>
    void work(T pr, S func, Args... args) {
        pr->set_value(func(args...));
        delete pr;
    }
    
    template<class T, class... Args>
    void work(std::promise<void> *pr, T func, Args... args) {
        pr->set_value();
        delete pr;
        func(args...);
    }
    
public:
    explicit ThreadPool(size_t poolSize):size(poolSize), done(false) {
        for (int i = 0; i < size; ++i) {
            pool.emplace_back([this]()
            {
                while(!done) {
                    std::unique_lock<std::mutex> lock(mtx);
                    if (queueProblems.empty()) {
                        while (!done) {
                            new_.wait(lock);
                            if (!queueProblems.empty()) {
                                break;
                            }
                        }
                    } else {
                        auto problem(std::move(queueProblems.front()));
                          queueProblems.pop();
                          lock.unlock();
                        problem();
                    }
                }
            });
        }
    }

     // pass arguments by value
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
        auto pr = new std::promise<decltype(func(args...))>();
        auto res = pr->get_future();
        auto task = [this](std::promise<decltype(func(args...)) > *pr, Func func, Args... args) {
            work(pr, func, args...);
        };
    
        std::function<void()> t = std::bind(task, pr, func, args...);
        mtx.lock();
        queueProblems.push(t);
        mtx.unlock();
        new_.notify_one();
        return res;
    }
    
    ~ThreadPool() {
        done = true;
        new_.notify_all();
        for(int i = 0; i < size; ++i) {
            pool[i].join();
        }
    }
};
