#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

int hash(std::string label) {
    int current;

    for(auto l: label) {
        current += int(l);
        current *= 17;
        current %= 256;
    }

    return current;
}

std::map<int, std::vector<std::pair<std::string, int>>> boxes;

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


    for(int i = 0; i < 256; i++) {
        boxes[i] = {};
    }

    int current_box;

    for(auto p: pieces) {
        if(p.find('=') != std::string::npos) {
            std::string label = p.substr(0, p.find('='));
            current_box = hash(label);
            int focal = std::stoi(p.substr(p.find('=') + 1, p.size()));

            auto it = std::find_if(boxes[current_box].begin(), boxes[current_box].end(), [label](const auto& pair) {
                return pair.first == label;
            });

            if(it != boxes[current_box].end()) {
                it->second = focal;
            } else {
                boxes[current_box].push_back(std::make_pair(label, focal));
            }

        } else {
            std::string label = p.substr(0, p.size() - 1);
            current_box = hash(label);

            auto it = std::find_if(boxes[current_box].begin(), boxes[current_box].end(), [label](const auto& pair) {
                return pair.first == label;
            });

            if(it != boxes[current_box].end()) {
                boxes[current_box].erase(it);
            }
        }
    }

    int total = 0;
    int current = 0;
    
    for(auto it = boxes.begin(); it != boxes.end(); it++) {
        int counter = 1;
        for(auto itt: it->second) {

            current = (it->first + 1) * counter * itt.second;
            total += current;
            //std::cout << current << std::endl;
            counter++;
        }
    }

    std::cout << total << std::endl;
}