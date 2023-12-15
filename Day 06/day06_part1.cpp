#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <cmath>
#include <algorithm>

int main() {
    std::ifstream file("input_day06.txt");

    const int RACES = 4;
    std::string word;
    std::array<int, RACES> time;
    std::array<int, RACES> distance;

    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    file >> word;
    int counter = 0;
    for (int i=0; i<(2*RACES - 1); i++) {
        file >> time[counter];
        if (time[counter] != 0) {
            counter++;
        } 
        i++;
    }

    file >> word;
    counter = 0;
    for (int i=0; i<(2*RACES - 1); i++) {
        file >> distance[counter];
        if (distance[counter] != 0) {
            counter++;
        } 
        i++;
    }

    for (auto ti : time) {
        std::cout << ti << '\n';
    }

    for (auto di : distance) {
        std::cout << di << '\n';
    }
}