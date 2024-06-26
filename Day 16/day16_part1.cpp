#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>


using Pos = std::pair<std::pair<int, int>, char>;

std::set<Pos> seen;
std::vector<std::string> rows;

void path(Pos pos) {
    switch(pos.second) {
        case 'N':
            pos.first.second -= 1;
            break;
        case 'E':
            pos.first.first += 1;
            break;
        case 'S':
            pos.first.second += 1;
            break;
        case 'W':
            pos.first.first -= 1;
            break;
    }

    if(pos.first.first < 0 || pos.first.first > rows[0].size() - 1
    || pos.first.second < 0 || pos.first.second > rows.size() - 1
    || seen.find(pos) != seen.end()) {
        return;
    }

    seen.insert(pos);

    std::string next;

    switch(rows[pos.first.second][pos.first.first]) {
        case '.':
            next = pos.second;
            break;
        case '|':
            (pos.second == 'E' || pos.second == 'W') ? next = "NS": next = pos.second;
            break;
        case '-':
            (pos.second == 'N' || pos.second == 'S') ? next = "EW": next = pos.second;
            break;
        case '/':
            switch(pos.second) {
                case 'N':
                    next = 'E';
                    break;
                case 'E':
                    next = 'N';
                    break;
                case 'S':
                    next = 'W';
                    break;
                case 'W':
                    next = 'S';
                    break;
            }
            break;
        case '\\':
            switch(pos.second) {
                case 'N':
                    next = 'W';
                    break;
                case 'E':
                    next = 'S';
                    break;
                case 'S':
                    next = 'E';
                    break;
                case 'W':
                    next = 'N';
                    break;
            }
            break;

    }

    for(char c: next) {
        path({{pos.first.first, pos.first.second}, c});
    }
}

int main() {
    std::ifstream file("input_day16.txt");

    if (!file.is_open()) {
        perror(NULL);
        return 1;
    }

    std::string line;

    while(std::getline(file, line)) {
        rows.push_back(line);
    }

    path({{-1,0},'E'});

    //remove duplicate x,y pairs (directions can cause repeats)
    std::set<std::pair<int,int>> fin;

    for(auto p: seen) {
        fin.insert(p.first);
    }

    std::cout << fin.size() << std::endl;
}