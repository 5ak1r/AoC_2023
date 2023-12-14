#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>


const std::map<std::string, int> MAX_CUBES = {
    {"red", 12}, 
    {"green", 13}, 
    {"blue", 14}
};

std::vector<std::string> games;
std::vector<std::string> rounds;
std::vector<std::string> balls;
int grand_total = 0;


int main() {
    std::ifstream file("input_day02.txt");
    
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;

    while(std::getline(file, line)) {
        line = line.substr(line.find(":")+2, line.length()-line.find(":")-2);
        games.push_back(line);
    }

    int counter = 0;
    while (counter < games.size()) {
        rounds.clear();
        while(games[counter].find(";") != std::string::npos) {
            rounds.push_back(games[counter].substr(0, games[counter].find(";")));
            games[counter] = games[counter].substr(games[counter].find(";")+2, games[counter].length()-games[counter].find(";")-2);
        }
        rounds.push_back(games[counter]);

        balls.clear();
        for(auto ball: rounds) {
            while(ball.find(",") != std::string::npos) {
                balls.push_back(ball.substr(0, ball.find(",")));
                ball = ball.substr(ball.find(",")+2, ball.length()-ball.find(",")-2);
            }
            balls.push_back(ball);
        }

        bool success = true;
        for(auto b: balls) {
            int num = strtol(b.substr(0, b.find(" ")).c_str(), NULL, 10);
            std::string colour = b.substr(b.find(" ")+1, b.length()-b.find(" ")-1);
            if(num > MAX_CUBES.at(colour)) {
                success = false;
            }
        }

        if (success) {
            grand_total += (counter + 1);
        }

        counter++;
    }

    std::cout << grand_total << '\n';

    return 0;
}