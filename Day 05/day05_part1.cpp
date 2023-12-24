#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <vector>
#include <array>


int main() {

    const int CONDITIONS = 7;
    std::string word;
    std::array<long long, 3> arr;
    std::array<std::vector<std::array<long long, 3>>, CONDITIONS> data;
    std::vector<long long> seeds;
    long long word_l;

    std::ifstream file("input_day05.txt");
    
    if (!file.is_open()) {
        perror(NULL);
        //std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    //remove first text "seeds:"
    file >> word;

    //obtain seeds separately
    while (file >> word) {
        word_l = strtoll(word.c_str(), NULL, 10);
        if (word != "0" && !word_l) break;
        seeds.push_back(word_l);
    }


    //remove "map:" in first seed-to-soil line
    file >> word;

    int counter = 0;
    int data_counter = 0;

    while(file >> word) {
        word_l = strtoll(word.c_str(), NULL, 10);
        if (word != "0" && !word_l) {
            file >> word;
            data_counter++;
            continue;
        }
        
        arr[counter] = word_l;
        counter++;

        if (counter == 3) {
            counter = 0;
            data[data_counter].push_back(arr);
        }
        
    }

    long long min = -1;
    for(auto seed: seeds) {
        for(int i = 0; i < CONDITIONS; i++) {
            for(auto mapping: data[i]) {
                //std::cout << mapping[0] << " " << mapping[1] << " " << mapping[2] << '\n';
                if(mapping[1] <= seed && seed <= mapping[1] + mapping[2]) {
                    seed = seed - mapping[1] + mapping[0];
                    //std::cout << seed << '\n';
                    break;
                }
            }
        }

        //std::cout << seed << '\n';
        if (seed < min || min == - 1) {
            min = seed;
        }
    }

    std::cout << min << '\n';
}