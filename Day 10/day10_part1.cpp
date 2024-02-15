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
  int counter = 0;

  for (auto row : pipes) {
    if (row.find('S') != std::string::npos) {
      return Pos{counter, (int)row.find('S')};
    }
    counter++;
  }

  return Pos{0, 0};
}

int traverse(Pos pos, char dir) {
  int counter = 1;

  while(pipes[pos.row][pos.col] != 'S'){

    if (pipes[pos.row][pos.col] == '.' ||
        pos.col < 0 || pos.col > pipes.size() || pos.row < 0 ||
        pos.row > pipes[0].size()) {
          return -1;
        }
    
    dir = OPP[char(std::stoi(std::to_string(PIPES[pipes[pos.row][pos.col]][1 - PIPES[pipes[pos.row][pos.col]].find(dir)])))];
    counter++;

    if(PIPES[pipes[pos.row][pos.col]].find(OPP[dir]) == std::string::npos) {
      return -1;
    }

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
    // pipes[pos.row][pos.col] == 'S' ? 1: -999999: NULL;

    /*recursion causes stack overflow :(
    if (std::string("S.").find(pipes[pos.row][pos.col]) != std::string::npos ||
        pos.col < 0 || pos.col > pipes.size() - 1 || pos.row < 0 ||
        pos.row > pipes[0].size() - 1) {
        return pipes[pos.row][pos.col] == 'S' ? counter + 1 : -999999;
    }


    
    return (PIPES[pipes[pos.row][pos.col]].find(dir) !=
            std::string::npos)
                ? 1 + traverse(pos, OPP[char(std::stoi(std::to_string(PIPES[pipes[pos.row][pos.col]][1 - PIPES[pipes[pos.row][pos.col]].find(dir)])))])
                : -999999;
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

  int left = traverse(Pos{start.row, start.col - 1}, 'W');
  std::cout << "left: " << left/2 << std::endl;
  int up = traverse(Pos{start.row - 1, start.col}, 'N');
  std::cout << "up: " << up/2 << std::endl;
  int right = traverse(Pos{start.row, start.col + 1}, 'E');
  std::cout << "right: " << right/2 << std::endl;
  int down = traverse(Pos{start.row + 1, start.col}, 'S');
  std::cout << "down: " << down/2 << std::endl;

}