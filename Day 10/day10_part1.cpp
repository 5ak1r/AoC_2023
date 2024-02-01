#include <cstddef>
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

typedef struct {
    size_t row;
    size_t col;
} Pos;

Pos find_start(std::vector<std::string> pipes) {
    size_t counter = 0;

    for(auto row: pipes) {
        if(row.find('S') != std::string::npos) {
            return Pos{row.find('S'), counter};
        }
        counter++;
    }

    return Pos{0,0};
}


int main() {
    std::ifstream file("input_day10.txt");
    std::vector<std::string> pipes;

    if (!file.is_open()) {
        perror(NULL);
        return 1;
    }

    int counter = 0;
    for(std::string line; std::getline(file, line);) {
        pipes.push_back(line);
        counter++;
    }

    Pos start = find_start(pipes);
    std::cout << start.col << " " << start.row << '\n';
    
    
    
}