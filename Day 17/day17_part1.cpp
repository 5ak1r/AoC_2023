#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>

#define graph std::vector<std::vector<int>>

void dijkstra(graph weights) {
    graph dist;
    std::vector<int> visited;
    
    for(int i = 0; i < weights.size(); i++) {
        for(int j = 0; j < weights[0].size(); j++) {
            dist[i][j] = 999999;
            visited.push_back(0);
        }
    }
    dist[0][0] = 0;

    while(std::find(visited.begin(), visited.end(), 0) != visited.end()) {
    }
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
        for(char i: line) {
            weights[count].push_back(i - '0');
            std::cout << weights[count][0];
        }

        count++;
    }

    dijkstra(weights);

}