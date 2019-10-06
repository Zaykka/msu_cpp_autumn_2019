#include <iostream>

enum {
    MAX_SIZE = 10000
};
class Timer
{
    using clock_t = std::chrono::high_resolution_clock;
    using microseconds = std::chrono::microseconds;
public:
    Timer()
            : start_(clock_t::now())
    {
    }

    ~Timer()
    {
        const auto finish = clock_t::now();
        const auto us =
                std::chrono::duration_cast<microseconds>
                        (finish - start_).count();
        std::cout << us << " us" << std::endl;
    }

private:
    const clock_t::time_point start_;
};

int main() {
    int **array = new int *[MAX_SIZE]; // сто миллионов элтов  настроить мкольео промахов по кешу захожу в вашу директроию птишу мейк получаю исп файл пишу мейк ран запуск код
    for (int i = 0; i < MAX_SIZE; ++i) {
        array[i] = new int[MAX_SIZE];
    }
    for (int i = 0; i < MAX_SIZE; ++i) {
        for (int j = 0; j < MAX_SIZE; ++j) {
            array[i][j] = i + j;
        }
    }
    volatile int sum = 0;
    Timer t;
    for (int j = 0; j < MAX_SIZE; ++j) {
        for (int i = 0; i < MAX_SIZE; ++i) {
            sum += array[i][j];
        }
    }
    return 0;
}
