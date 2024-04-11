#include <iostream>
#include <fstream>
#include <vector>


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
  
  for(auto c: cols) {
    std::cout << c << std::endl;
  }
}