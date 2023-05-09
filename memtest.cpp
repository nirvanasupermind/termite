#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>

int main() {
    using namespace std::chrono;
    
    uint64_t time1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();;
    std::vector<int> vec(1000000000);
    uint64_t time2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();;
    std::cout << time2 - time1 << '\n';
}