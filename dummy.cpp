#include <iostream>
#include <future>
#include <vector>
#include <numeric>
#include <thread>

auto fact(size_t n) ->size_t
{
    size_t f = 0;
    std::cout << "id: "<< std::this_thread::get_id() << '\n';
    for (int64_t i = 0; i < 10000'0000; ++i)
    {
        f = 1;
        for ([[maybe_unused]]size_t j = n; j >= 1; --j)
            f *= j;
    }
    return f;
}

auto sum(const std::vector<size_t>& arr) ->size_t
{
    std::cout << "id: "<< std::this_thread::get_id() << '\n';
    size_t sum = 0;
    for (int i = 0; i < 100'000; ++i)
        sum += std::accumulate(arr.begin(), arr.end(), 0ull);

    return sum;
}

auto main() ->int
{
    auto handle1 = std::async(std::launch::async, fact, 45); 
    
    std::vector<size_t> arr(10000, 3);
    auto handle2 = std::async(std::launch::async, sum, arr);
    
    std::cout << handle1.get() << '\n';
    std::cout << handle2.get() << '\n';

    //std::cout << fact(45) << '\n';
    //std::cout << sum(arr) << '\n';
}
