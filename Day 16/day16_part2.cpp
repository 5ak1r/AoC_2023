#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>


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


    std::vector<char> options = {'N', 'E', 'S', 'W'};
    std::vector<int> totals;
    std::set<std::pair<int,int>> fin;
    std::set<std::pair<int, int>> check;
    for(int i = 0; i < rows[0].size(); i++) {
        if(i == 0 || i == rows[0].size() - 1) {
            for(int j = 0; j < rows.size(); j++) {
                check.insert({i, j});
            }           
        } else {
            check.insert({i, 0});
            check.insert({i, rows.size() - 1});
        }
    }

    for(auto p: check) {
        for(char o: options) {
            path({{p.first,p.second},o});

            for(auto s: seen) {
                fin.insert(s.first);
            }

            totals.push_back(fin.size());
            seen.clear();
            fin.clear();
        }
    }

    int max = *std::max_element(totals.begin(), totals.end());

    std::cout << max + 1 << std::endl; //current solution does not count first space
}
