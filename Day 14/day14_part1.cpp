#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>


int main() {
  std::ifstream file("input_day14.txt");

  if (!file.is_open()) {
    perror(NULL);
    return 1;
  }

  std::string line;
  std::vector<std::string> cols;

  //separate the lines into columns to move the rocks easier
  while(std::getline(file, line)) {
    for(int i = 0; i < line.size(); i++) {
        if(i == cols.size()) {
            std::string insert;
            insert += line[i];
            cols.push_back(insert);
        } else {
            cols[i] += line[i];
        }
    }
  }
  
  size_t cube_rock_index;
  size_t smooth_index;
  size_t next_free;

  size_t total = 0;

  for(auto c: cols) {
    next_free = 0;
    cube_rock_index = c.find('#');
    smooth_index = c.find('O');

    while(smooth_index != std::string::npos) {
      smooth_index = c.find('O');

      while(smooth_index < cube_rock_index) {
        c[next_free] = 'S';

        if(next_free != smooth_index) {
          c[smooth_index] = '.';
        }

        smooth_index = c.find('O');
        next_free++;
      }

      if(cube_rock_index != std::string::npos) {
        next_free = cube_rock_index + 1;
        c[cube_rock_index] = 'R';
        cube_rock_index = c.find('#');
      }
      
    }

    std::replace(c.begin(), c.end(), 'R', '#');

    for(int i = 0; i < c.size(); i++) {
      if(c[i] == 'S') {
        total += c.size() - i;
      }
    }

  }

  std::cout << total << std::endl;
}