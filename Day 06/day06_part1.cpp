#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <cmath>

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

    for (int i=0; i<RACES; i++) {
        float disc = pow(time[i], 2) - 4 * distance[i];

        if (disc <= 0) {
            return 1;
        }

        float sol_1 = (time[i] + sqrt(disc))/2;
        float sol_2 = (time[i] - sqrt(disc))/2;
        grand_total *= floor(sol_1) - ceil(sol_2) + ((sol_1 > sol_2) ? 1: -1); 

    }

    std::cout << grand_total << '\n';

}