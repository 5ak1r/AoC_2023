#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <cmath>

std::vector<std::array<int, 3>> index_num;
std::vector<std::array<int, 2>> index_spc;
std::vector<std::string> line_vec;

int first_index;
int last_index;
int grand_total = 0;

int main() {
    std::ifstream file("input_day03.txt");
    
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    int counter = 0;
	while(std::getline(file, line)) {
        line_vec.push_back(line);
        for(int i = 0; i < line.length(); i++) {
            if (isdigit(line[i])) {
                first_index = i;
                last_index = i+1;

                while(isdigit(line[last_index])) {
                    last_index++;
                }
                
                i = last_index - 1;
                index_num.push_back({counter, first_index, last_index});

            } else if (line[i] != '.') {
                index_spc.push_back({counter, i});
            }
        }
        counter++;
	}


    for(const auto& current_spc : index_spc) {
        for(const auto& current_num : index_num) {
            if ((std::abs(current_num[0] - current_spc[0]) <= 1) && (current_num[1] - 1 <= current_spc[1]) && (current_spc[1] <= current_num[2])) {
                grand_total += strtol(line_vec[current_num[0]].substr(current_num[1], current_num[2]-current_num[1]).c_str(), NULL, 10);
            }
        }
    }

    std::cout << grand_total << '\n';

}