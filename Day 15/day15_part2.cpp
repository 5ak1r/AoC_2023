#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream file("input_day15.txt");

    if (!file.is_open()) {
        perror(NULL);
        return 1;
    }

    std::string line;

    while(std::getline(file, line)) {
        std::cout << "only one line this time :)" << std::endl;
    }

    std::vector<std::string> pieces;

    while(line.find(',') != std::string::npos) {
        pieces.push_back(line.substr(0, line.find(',')));
        line = line.substr(line.find(',')+1, line.size());
    }
    pieces.push_back(line);

    size_t current = 0;
    size_t total = 0;

    for(auto p: pieces) {
        for(auto l: p) {
            current += int(l);
            current *= 17;
            current %= 256;
        }
        total += current;
        current = 0;
    }

    std::cout << total << std::endl;
}