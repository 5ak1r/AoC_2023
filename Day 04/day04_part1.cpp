#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

std::vector<std::string> games;
std::vector<std::string> nums;
int grand_total = 0;

int main() {
    std::ifstream file("input_day04.txt");
    
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;

    while(std::getline(file, line)) {
        line = line.substr(line.find(":")+2, line.length()-line.find(":")-2);
        games.push_back(line);
    }

    for (auto game : games) {
        nums.clear();
        while(game.find(" ") != std::string::npos) {
            nums.push_back(game.substr(0, game.find(" ")));
            game = game.substr(game.find(" ")+1, game.length() - game.find(" ") - 1);
        }
        nums.push_back(game);

        int plays = 10;
        int matches = 0;

        for (int i=0; i<plays; i++) {
            if (nums[i] == "|" || nums[i] == "") {
                plays++;
                continue;
            }

            if (std::count(nums.begin(), nums.end(), nums[i]) == 2) {
                matches++;
            }
            
        }

        grand_total += pow(2, matches-1);
        
    }

    std::cout << grand_total << '\n';
}