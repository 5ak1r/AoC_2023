#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <array>

std::vector<std::array<int, 3>> index_num;
std::vector<std::array<int, 2>> index_spc;

int first_index;
int last_index;

int main() {
    std::ifstream file("input_day03.txt");
    
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    int counter = 1;
	while(std::getline(file, line)) {
        for(int i = 0; i < line.length(); i++) {
            if (isdigit(line[i])) {
                first_index = i;
                last_index = i+1;

                while(isdigit(line[last_index])) {
                    last_index++;
                }
                
                i = last_index;
                index_num.push_back({counter, first_index, last_index});

            } else if (line[i] != '.') {
                index_spc.push_back({counter, i});
            }
        }
        counter++;
	}

    for(const auto& current_array : index_num) {
        for(int current_num : current_array) {
            std::cout << current_num << " ";
        }

        std::cout << "\n";
    }



}