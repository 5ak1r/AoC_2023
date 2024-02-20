#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>



std::vector<std::string> expansion(std::vector<std::string> space) {
  int max_rows = space.size();
  int max_cols = space[0].size();

  std::set<int> planet_row;
  std::set<int> planet_col;

  for(int i = 0; i < max_rows; i++) {
    for(int j = 0; j < max_cols; j++) {
      if(space[i][j] == '#') {
        planet_row.insert(i);
        planet_col.insert(j);
      }
    }
  }

  
  for(auto row: planet_row) {
    std::cout << "row: " << row << std::endl;
  }

  for(auto col: planet_col) {
    std::cout << "col: " << col << std::endl;
  }

}

int main() {
  std::ifstream file("input_day11.txt");
  std::vector<std::string> space;

  if (!file.is_open()) {
    perror(NULL);
    return 1;
  }

  for (std::string line; std::getline(file, line);) {
    space.push_back(line);
  }

  space = expansion(space);

}