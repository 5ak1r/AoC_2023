#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <map>
#include <algorithm>
#include <regex>
#include <cmath>

typedef struct {
    std::string left;
    std::string right;
} Node;

std::string path;
std::string name;
std::string discardEquals;
std::vector<std::string> positions;
std::vector<int> counters;
Node node;

std::map<std::string, Node> nodes;

int navigate(std::string position) {
    int counter = 0;
    std::regex end_z(".*Z$");

    //assume the path will eventually reach **Z
    while(true) {
        for(char c: path) {
            if(std::regex_match(position, end_z)) {
                return counter;
            }
            
            //assume the path only contains L and R as the given input does; no need for extra checks
            if(c == 'L') {
                position = nodes[position].left;
            } else {
                position = nodes[position].right;
            }

            counter++;
        }
    }
}

size_t gcd(size_t a, size_t b) {
    while(b) {
        size_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}


int main() {
    std::ifstream file("input_day08.txt");

    if (!file.is_open()) {
        perror(NULL);
        return 1;
    }

    //obtain path from the top of the file
    file >> path;

    while(file >> name >> discardEquals >> node.left >> node.right) {
        //erase punctutation; method found on https://stackoverflow.com/questions/19138983/c-remove-punctuation-from-string by user180247
        node.left.erase(std::remove_if(node.left.begin(), node.left.end(), ispunct), node.left.end());
        node.right.erase(std::remove_if(node.right.begin(), node.right.end(), ispunct), node.right.end());

        std::regex end_a(".*A$");

        if(std::regex_match(name, end_a)) {
            positions.push_back(name);
        }

        nodes[name] = node;
    }

    for(auto pos: positions) {
        counters.push_back(navigate(pos));
    }
    
    long long answer = 1;

    for(auto counter: counters) {
        answer = std::floor((answer * counter) / gcd(answer, counter));
    }

    std::cout << answer << '\n';
}
