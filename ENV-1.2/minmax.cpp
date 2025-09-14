#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cctype>

int main(int argc, char* argv[]){
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " num1 num2 num3\n";
        return 1; 
    }

    char* s1 = argv[1];
    while (*s1) {
        if (!std::isdigit(static_cast<unsigned char>(*s1))) {
           std::cerr << "Error: " << argv[1] << " is not a number\n";
           return 1;
         }
         s1++;
    }

    char* s2 = argv[2];
    while (*s2) {
        if (!std::isdigit(static_cast<unsigned char>(*s2))) {
           std::cerr << "Error: " << argv[2] << " is not a number\n";
           return 1;
        }
        s2++;
    }

    char* s3 = argv[3];
    while (*s3) {
        if (!std::isdigit(static_cast<unsigned char>(*s3))) {
           std::cerr << "Error: " << argv[3] << " is not a number\n";
           return 1;
        }
        s3++;
    }

    int a = std::atoi(argv[1]);
    int b = std::atoi(argv[2]);
    int c = std::atoi(argv[3]);

    int min_val = std::min({a, b, c});
    int max_val = std::max({a, b, c});

    std::cout << "min " << min_val << ", max " << max_val << "\n";
    return 0; 
}
