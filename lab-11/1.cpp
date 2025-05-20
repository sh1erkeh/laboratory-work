#include <iostream>
#include <vector>
#include <chrono>

template<typename Func, typename... Args>
auto measure_time(Func&& func, Args&&... args)
requires requires(Func function) { function(std::forward<Args>(args)...); }
{
    auto start = std::chrono::high_resolution_clock::now();
    auto result = std::forward<Func>(func)(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    return std::make_pair(result, duration.count());
}

long long recursive(int n) {
    switch (n) {
        case 0:
            return 0ll;
        case 1:
            return 1ll;
        default:
            long long result = 0;
            for (int i = 2; i <= n; i++) {
                result += recursive(n / i);
            }
            return result;
    }
}

long long iterative(int n) {
    std::vector<long long> cache(n + 1);
    cache[1] = 1;

    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= n; j++) {
            cache[i] += cache[i / j];
        }
    }

    return cache[n];
}

int main() {
    int n;
    std::cin >> n;

    auto [res_rec, time_rec] = measure_time(recursive, n);
    auto [res_it, time_it] = measure_time(iterative, n);

    std::cout << std::fixed << std::setprecision(8);
    std::cout << res_rec << ' ' << time_rec << '\n';
    std::cout << res_it << ' ' << time_it << '\n';
}
