#include <cstddef>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

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

std::vector<Pos> traverse(Pos pos, char dir) {
  std::vector<Pos> corners;

  while(pipes[pos.row][pos.col] != 'S'){

    if (pipes[pos.row][pos.col] == '.' ||
        pos.col < 0 || pos.col > pipes.size() - 1 || pos.row < 0 ||
        pos.row > pipes[0].size() - 1) {
          return {};
        }
    
    dir = OPP[char(std::stoi(std::to_string(PIPES[pipes[pos.row][pos.col]][1 - PIPES[pipes[pos.row][pos.col]].find(dir)])))];
    
    if(std::string("LJ7F").find(pipes[pos.row][pos.col]) != std::string::npos) {
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

/*int shoelace(std::vector<Pos> corners) {
    int answer = 0;

    if(corners.size() == 0) {
        return 0;
    }

    for(int i = 0; i < corners.size() - 1; i++) {
        answer += (corners[i].col * corners[i+1].row) - (corners[i+1].col * corners[i].row);
    }

    answer += (corners[corners.size() - 1].col * corners[0].row) - (corners[0].col * corners[corners.size() - 1].row);
    return answer;
}*/


int inside(std::vector<Pos> corners) {
  std::map<int, std::vector<int>> row_col;
  int answer = 0;

  for(auto corner: corners) {
    row_col[corner.row].push_back(corner.col);
  }

  for(std::map<int, std::vector<int>>::iterator it = row_col.begin(); it != row_col.end(); ++it) {
    std::sort(it->second.begin(), it->second.end());
    int counter = 0;
    for(int i = 0; i < row_col[it->first].size() - 1; i++) {
      if(counter % 2 == 0) answer += row_col[it->first][i+1] - row_col[it->first][i] - 1;
      counter++;
    }
  }

  return answer;
}


int main() {
  std::ifstream file("input_day10.txt");

  if (!file.is_open()) {
    perror(NULL);
    return 1;
  }

  for (std::string line; std::getline(file, line);) {
    pipes.push_back(line);
  }

  Pos start = find_start(pipes);


  std::vector<Pos> left = traverse(Pos{start.row, start.col - 1}, 'W');
  std::vector<Pos> up = traverse(Pos{start.row - 1, start.col}, 'N');
  std::vector<Pos> right = traverse(Pos{start.row, start.col + 1}, 'E');
  std::vector<Pos> down = traverse(Pos{start.row + 1, start.col}, 'S');

  std::cout << inside(left) << std::endl;

}