#include <cstddef>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

enum DIRS {
    W,
    N,
    E,
    S,
};

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

std::vector<std::string> pipes;

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

int traverse(Pos pos, DIRS dir) {
    char current_pipe = pipes[pos.row][pos.col];

    if (current_pipe == 'S') {
        return 0;
    }

    switch(dir) {
        case W: 
            pos.row -= 1;
            break;
        case N:
            pos.col += 1;
            break;
        case E:
            pos.row += 1;
            break;
        case S:
            pos.col -= 1;
            break;
    }

    if (pos.row < 0 || pos.row > std::strlen(pipes[0].c_str()) ||
        pos.col < 0 || pos.col > sizeof(pipes)) {
        
        return -INT_MAX;

    } else {
        switch(current_pipe) {
            case 'L':
                
        }
    }
}


int main() {
    std::ifstream file("input_day10.txt");

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
    int left = traverse(start, W);
    int up = traverse(start, N);
    int right = traverse(start, E);
    int down = traverse(start, S);
    
    
    
}