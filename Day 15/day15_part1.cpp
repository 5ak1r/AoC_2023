#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

int main() {
    std::ifstream file("input_day14.txt");

    if (!file.is_open()) {
        perror(NULL);
        return 1;
    }

}