#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>


int main() {
    std::ifstream file("input_day16.txt");

    if (!file.is_open()) {
        perror(NULL);
        return 1;
    }

    std::string line;

    while(std::getline(file, line)) {
    }

    
}