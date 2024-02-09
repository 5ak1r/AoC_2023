#include <climits>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

static std::map<char, char> OPP = {
    {'N', 'S'},
    {'E', 'W'},
    {'S', 'N'},
    {'W', 'E'},
};

static std::map<char, std::string> PIPES = {
    {'L', "SW"}, {'|', "NS"}, {'J', "SE"},
    {'-', "EW"}, {'F', "NW"}, {'7', "NE"},
};

typedef struct {
  int row;
  int col;
} Pos;

std::vector<std::string> pipes;

Pos find_start(std::vector<std::string> pipes) {
  size_t counter = 0;

  for (auto row : pipes) {
    if (row.find('S') != std::string::npos) {
      return Pos{(int)counter, (int)row.find('S')};
    }
    counter++;
  }

  return Pos{0, 0};
}

int traverse(Pos pos, char dir) {
  int counter = 1;

  switch (dir) {
    case 'N':
        pos.row -= 1;
        break;
    case 'E':
        pos.col += 1;
        break;
    case 'S':
        pos.row += 1;
        break;
    case 'W':
        pos.col -= 1;
        break;
    }

  while(pipes[pos.row][pos.col] != 'S'){

    if (pipes[pos.row][pos.col] == '.' ||
        pos.col < 0 || pos.col > pipes.size() - 1 || pos.row < 0 ||
        pos.row > pipes[0].size() - 1) {
            return 0;
        }
    
    dir = OPP[char(std::stoi(std::to_string(PIPES[pipes[pos.row][pos.col]][1 - PIPES[pipes[pos.row][pos.col]].find(dir)])))];
    counter++;

    switch (dir) {
    case 'N':
        pos.row -= 1;
        break;
    case 'E':
        pos.col += 1;
        break;
    case 'S':
        pos.row += 1;
        break;
    case 'W':
        pos.col -= 1;
        break;
    }

    // one liner embedded ternaries hehe haha
    // std::string("S.").find(pipes[pos.row][pos.col]) != std::string::npos ?
    // pipes[pos.row][pos.col] == 'S' ? 1: -INT_MAX: NULL;

    /*recursion causes stack overflow :(
    if (std::string("S.").find(pipes[pos.row][pos.col]) != std::string::npos ||
        pos.col < 0 || pos.col > pipes.size() - 1 || pos.row < 0 ||
        pos.row > pipes[0].size() - 1) {
        return pipes[pos.row][pos.col] == 'S' ? counter + 1 : -INT_MAX;
    }


    
    return (PIPES[pipes[pos.row][pos.col]].find(dir) !=
            std::string::npos)
                ? 1 + traverse(pos, OPP[char(std::stoi(std::to_string(PIPES[pipes[pos.row][pos.col]][1 - PIPES[pipes[pos.row][pos.col]].find(dir)])))])
                : -INT_MAX;
                */
  }

  return counter;


}

int main() {
  std::ifstream file("input_day10.txt");

  if (!file.is_open()) {
    perror(NULL);
    return 1;
  }

  int counter = 0;
  for (std::string line; std::getline(file, line);) {
    pipes.push_back(line);
    counter++;
  }

  Pos start = find_start(pipes);

  int left = traverse(start, 'W');
  int up = traverse(start, 'N');
  int right = traverse(start, 'E');
  int down = traverse(start, 'S');

  std::cout << "left: " << left << std::endl;
  std::cout << "up: " << up << std::endl;
  std::cout << "down: " << down << std::endl;
  std::cout << "right: " << right << std::endl;

}