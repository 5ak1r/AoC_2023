#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

int num;
std::string line;
std::vector<int> next_in_sq;

std::vector<std::vector<int>> sq;


int main() {
    std::ifstream file("input_day09.txt");
    

    if (!file.is_open()) {
        perror(NULL);
        return 1;
    }

    while(std::getline(file, line)) {

        std::istringstream iss(line);
        std::vector<int> current_sq;

        while(iss >> num) {
            std::cout << num << ' ';
            current_sq.push_back(num);
        }
        
        std::cout << '\n';

        sq.push_back(current_sq);
        while(!std::all_of(sq[sq.size() - 1].begin(), sq[sq.size() - 1].end(), [](int x){ return x == 0; })) {
            current_sq.clear();

            for(int i = 0; i < sq[sq.size() - 1].size() - 1; i++) {
                current_sq.push_back(sq[sq.size() - 1][i+1] - sq[sq.size() - 1][i]);
            }

            sq.push_back(current_sq);
        }

        for(int i = sq.size() - 1; i >= 0; i--) {
            for(auto s: sq[i]) {
                std::cout << s << " ";
            }
            std::cout << '\n';
        }
        
        

    }
}