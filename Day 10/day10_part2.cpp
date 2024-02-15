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

//add answer to part 1 here
const int PART_ONE = 7012;

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

std::vector<Pos> traverse(Pos pos, char dir) {
  std::vector<Pos> corners;
  
  while(pipes[pos.row][pos.col] != 'S'){

    if (pipes[pos.row][pos.col] == '.' ||
        pos.col < 0 || pos.col > pipes.size() || pos.row < 0 ||
        pos.row > pipes[0].size()) {
          return {};
        }
    
    dir = OPP[char(std::stoi(std::to_string(PIPES[pipes[pos.row][pos.col]][1 - PIPES[pipes[pos.row][pos.col]].find(dir)])))];
    
    if(std::string("LF7J").find(pipes[pos.row][pos.col]) != std::string::npos) {
      corners.push_back(pos);
    }

    if(PIPES[pipes[pos.row][pos.col]].find(OPP[dir]) == std::string::npos) {
      return {};
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
  }

  return corners;


}

int shoelace(std::vector<Pos> corners) {
    int answer = 0;

    if(corners.size() == 0) {
        return 0;
    }

    for(int i = 0; i < corners.size() - 1; i++) {
        answer += (corners[i].col * corners[i+1].row) - (corners[i+1].col * corners[i].row);
    }

    answer += (corners.back().col * corners[0].row) - (corners[0].col * corners.back().row);
    return std::abs(answer)/2;
}

int picks(int shoelace, int partone) {
  //A = I + B/2 - 1
  //A - B/2 + 1 = I
  return shoelace - partone + 1;
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

  //use whichever two are correct for your input
  std::vector<Pos> left = traverse(Pos{start.row, start.col - 1}, 'W');
  std::vector<Pos> up = traverse(Pos{start.row - 1, start.col}, 'N');
  std::vector<Pos> right = traverse(Pos{start.row, start.col + 1}, 'E');
  std::vector<Pos> down = traverse(Pos{start.row + 1, start.col}, 'S');

  //if S is a vertex
  /*if((left.size() != 0 && right.size() == 0) || (up.size() != 0 && down.size() == 0)) {
    corners.push_back(start);
  }*/

  //use whichever one is correct for your input
  //add this if start is a corner vertex (check values, if L and R both non zero or U and D both nonzero, then S is not a vertex)
  //right.push_back(start);
  std::cout << picks(shoelace(left), PART_ONE) << std::endl; // IT FINALLY WORKED!!

}