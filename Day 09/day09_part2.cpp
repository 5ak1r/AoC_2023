#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>


//for other data types use a template; dont need to for this one
bool all_zero(const std::vector<int> &sq) {
  return all_of(sq.begin(), sq.end(), [](int x) { return x == 0; });
}

static std::vector<int> diff(const std::vector<int> &sq) {
    std::vector<int> diffs;

    for(auto it = next(sq.begin()); it != sq.end(); it++) {
        diffs.push_back(*it - *(prev(it)));
    }

    return diffs;
} 


static int prev_diff(std::vector<int> sq) {
    std::vector<int> diffs = diff(sq);
    return (all_zero(diffs)) ? sq.front() - diffs.front() : sq.front() - prev_diff(diffs);

}

int main() {
    std::ifstream file("input_day09.txt");
    

    if (!file.is_open()) {
        perror(NULL);
        return 1;
    }

    int total = 0;
    for(std::string line; std::getline(file, line);) {
        
        std::istringstream iss(line);
        std::vector<int> sq(std::istream_iterator<int>(iss), {});
        
        total += prev_diff(sq);

    }
    
    std::cout << total << '\n';
}   