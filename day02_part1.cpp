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


int main() {

    int grand_total = 0;
    std::ifstream file("input_day02.txt");
    
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::string> games;


    while(std::getline(file, line)) {
        long game_id = strtol(line.substr(4, line.find(":")).c_str(), NULL, 10);
        line = line.substr(line.find(":")+2, line.length()-line.find(":")-2);

        size_t current_pos = line.find(";");
        while(current_pos != std::string::npos) {
            //std::cout << line.substr(0, current_pos) << std::endl;
            games.push_back(line.substr(0, current_pos));
            line = line.substr(current_pos+2, line.length() - current_pos - 2);
            current_pos = line.find(";");
            
        }
        games.push_back(line.substr(0, line.length()));
    }

    //make the game ids match
    int counter = 0;
    for(auto game: games) {
        bool success = true;
        int num;
        std::string colour;

        while(game.find(",") != std::string::npos) {
            std::string ball = game.substr(0, game.find(","));
            //std::cout << ball << std::endl;

            game = game.substr(game.find(",")+2, game.length()-game.find(",")-2);
            //std::cout << game << std::endl;

            num = strtol(ball.substr(0, ball.find(" ")).c_str(), NULL, 10);
            colour = ball.substr(ball.find(" ")+1, ball.length() - ball.find(" "));
            //std::cout << num << '\n';
            //std::cout << colour << std::endl;

            if(MAX_CUBES.at(colour) < num) {
                success = false;
            }
        }

        num = strtol(game.substr(0, game.find(" ")).c_str(), NULL, 10);
        colour = game.substr(game.find(" ")+1, game.length() - game.find(" "));
        //std::cout << num << '\n';
        //std::cout << colour << std::endl;

        if(MAX_CUBES.at(colour) < num) {
            success = false;
        }

        if(success) {
            grand_total += counter;
        }


    }

    file.close();
    std::cout << grand_total << '\n';
}