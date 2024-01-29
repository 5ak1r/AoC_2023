#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

/*static const std::map<char, char> DIRECTIONS = {
    {'N', 'S'},
    {'E', 'W'},
    {'S', 'N'},
    {'W', 'E'},
};*/

static const std::map<char, std::string> PIPES = {
    {'L', "NE"},
    {'|', "NS"},
    {'J', "NW"},
    {'-', "EW"},
    {'F', "SE"},
    {'7', "SW"},
};


int main() {
    std::ifstream file("input_day09.txt");
    std::vector<std::vector<char>> pipes;

    if (!file.is_open()) {
        perror(NULL);
        return 1;
    }

    int counter = 0;
    for(std::string line; std::getline(file, line);) {
        char p;
        file >> p;
        pipes[counter].push_back(p);
    }
}