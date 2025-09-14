#include <iostream>
#include <cstdlib>
#include <algorithm>

int main(int argc, char* argv[]) {
    int a = std::atoi(argv[1]);
    int b = std::atoi(argv[2]);
    int c = std::atoi(argv[3]);
    int min_val = std::min({a, b, c});
    int max_val = std::max({a, b, c});
    std::cout << "min " << min_val << ", max " << max_val << "\n";
    return 0;
}
