#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>

#define graph std::vector<std::vector<int>>

void dijkstra(graph weights) {
}

int main() {
    std::ifstream file("input_day17.txt");

    if (!file.is_open()) {
        perror(NULL);
        return 1;
    }

    std::string line;
    graph weights;

    int count = 0;

    while(std::getline(file, line)) {

        weights.push_back({});

        for(char i: line) {
            weights[count].push_back(i - '0');
        }
        count++;
    }

    dijkstra(weights);

}