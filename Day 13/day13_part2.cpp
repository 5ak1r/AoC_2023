#include <iostream>
#include <fstream>
#include <vector>

typedef struct {
    std::vector<std::string> rows;
    std::vector<std::string> cols;
} Pattern;

std::vector<Pattern> patterns;

int difference(std::string left, std::string right) {

    bool done = false;

    if(left == right) {
        return false;
    }

    for(int i = 0; i < left.size(); i++) {
        if(left[i] != right[i]) {
            if(done) {
                return false;
            }
            done = true;
        }
    }

    return true;
}

int mirrors(std::vector<std::string> contents) {

    int left = 0;
    int right = 1;

    bool first = true;
    int first_left = 0;
    int answer;

    bool smudge = false;

    while(left > -1 && right < contents.size()) {
        if(contents[left] == contents[right]) {
            if(first) {
                answer = right;
                first_left = left;
                first = false;
            }
            left--;
            right++;
            if ((left < 0 || right >= contents.size()) && !smudge) {
                left = answer;
                right = left + 1;
                answer = -1;
                first = true;
            }

        } else if(difference(contents[left], contents[right]) && !smudge){
            smudge = true;
            if(first) {
                answer = right;
                first_left = left;
                first = false;
            }

            left--;
            right++;
        } else {
            answer = -1;
            left = first ? left + 1: first_left + 1;
            smudge = false;
            right = left + 1;
            first = true;
        }
    }
    return answer;
}

int main() {
  std::ifstream file("input_day13.txt");

  if (!file.is_open()) {
    perror(NULL);
    return 1;
  }

  int i = 0;
  std::string line;

  std::vector<std::string> rows;
  std::vector<std::string> cols;
  bool first = true;

  while(std::getline(file, line)) {
    if(line.empty()) {
        patterns.push_back(Pattern{rows, cols});
        rows.clear();
        cols.clear();
        first = true;
        i++;
    } else {
        rows.push_back(line);
        for(int i = 0; i < line.size(); i++) {
            if(first) {
                cols.push_back("");
            }
            cols[i] += line[i];
        }
        first = false;
    }
  }
  patterns.push_back(Pattern{rows, cols});

  int total = 0;

  for(auto p: patterns) {
    int row_calc = mirrors(p.rows);
    int col_calc = mirrors(p.cols);
    
    total += row_calc > 0 ? row_calc * 100: 0;
    total += col_calc > 0 ? col_calc: 0;

    std::cout << row_calc << " " << col_calc << std::endl;
  }

  std::cout << total << std::endl;
}