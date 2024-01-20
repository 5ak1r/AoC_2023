#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <map>
#include <algorithm>

typedef struct {
    std::string left;
    std::string right;
} Node;

std::string path;
std::string name;
std::string discardEquals;
Node node;

std::map<std::string, Node> nodes;

int navigate() {
    int counter = 0;
    std::string position = "AAA";

    //assume the path will eventually reach ZZZ
    while(true) {
        for(char c: path) {
            if(position == "ZZZ") {
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

        nodes[name] = node;
    }

    std::cout << navigate() << '\n';
    
}