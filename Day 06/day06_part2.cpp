#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <cmath>
#include <algorithm>
#include <sstream>

int main() {
    std::ifstream file("input_day06.txt");

    const int RACES = 4;
    std::string word;
    std::array<int, RACES> time, distance;

    int grand_total = 1;

    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    file >> word;
    int counter = 0;
    for (int i=0; i<(2*RACES - 1); i++) {
        file >> time[counter];
        if (time[counter] != 0) {
            counter++;
        } 
        i++;
    }

    file >> word;
    counter = 0;
    for (int i=0; i<(2*RACES - 1); i++) {
        file >> distance[counter];
        if (distance[counter] != 0) {
            counter++;
        } 
        i++;
    }

    std::stringstream ss_time, ss_distance;


    for (int i=0; i<RACES; i++) {
        ss_time << time[i];
        ss_distance << distance[i];
    }

    long l_time = strtol(ss_time.str().c_str(), NULL, 10);
    long l_distance = strtol(ss_distance.str().c_str(), NULL, 10);
    
    float disc = pow(l_time, 2) - 4 * l_distance;

    if (disc <= 0) {
        return 1;
    }

    float sol_1 = (l_time + sqrt(disc))/2;
    float sol_2 = (l_time - sqrt(disc))/2;
    grand_total *= floor(sol_1) - ceil(sol_2);

    sol_1 > sol_2 ? grand_total++: grand_total--;

    std::cout << grand_total << '\n';

}