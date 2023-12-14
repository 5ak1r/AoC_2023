#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

std::vector<int> index_num;
std::vector<int> index_spc;

int main() {
    std::ifstream file("input_day03.txt");
    
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
	while(std::getline(file, line)) {
		
	}
}