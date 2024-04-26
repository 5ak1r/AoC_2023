#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
    std::ifstream file("input_day16.txt");

    if (!file.is_open()) {
        perror(NULL);
        return 1;
    }

    std::string line;

    while(std::getline(file, line)) {
        std::cout << "only one line this time :)" << std::endl;
    }

}