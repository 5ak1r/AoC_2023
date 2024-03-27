#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>


typedef struct {
  int row;
  int col;
} Planet;

size_t solution(std::vector<std::string> space) {
  int max_rows = space.size();
  int max_cols = space[0].size();

  std::vector<Planet> planets;

  std::set<int> rows;
  std::set<int> cols;

  for(int i = 0; i < max_rows; i++) {
    for(int j = 0; j < max_cols; j++) {
      if(space[i][j] == '#') {
        planets.push_back(Planet{i, j});
        rows.insert(i);
        cols.insert(j);
      }
    }
  }

  size_t total_distance = 0;
  int manhattan_distance = 0;
  int difference = 0;

  for(int i = 0; i < planets.size() - 1; i++) {
    for(int j = i + 1; j < planets.size(); j++) {

      manhattan_distance = std::abs(planets[j].row - planets[i].row);
      difference = 0;

      for(auto r: rows) {
        if(r > planets[i].row && r < planets[j].row || r < planets[i].row && r > planets[j].row) {
          difference++;
        }
      }

      total_distance += manhattan_distance;

      if(manhattan_distance != 0) {
        total_distance += (manhattan_distance - 1 - difference)*999999;
      }

      manhattan_distance = std::abs(planets[j].col - planets[i].col);
      difference = 0;

      for(auto c: cols) {
        if(c > planets[i].col && c < planets[j].col || c < planets[i].col && c > planets[j].col) {
          difference++;
        }
      }

      total_distance += manhattan_distance;

      if(manhattan_distance != 0) {
        total_distance += (manhattan_distance - 1 - difference)*999999;
      }
    }
  }

  return total_distance;

}

int main() {
  std::ifstream file("input_day11.txt");
  std::vector<std::string> space;
  size_t answer;

  if (!file.is_open()) {
    perror(NULL);
    return 1;
  }

  for (std::string line; std::getline(file, line);) {
    space.push_back(line);
  }

  answer = solution(space);
  std::cout << answer << std::endl;

}