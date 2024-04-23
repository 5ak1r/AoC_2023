#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

std::vector<std::string> push(std::vector<std::string> cols) {
    size_t cube_rock_index;
    size_t smooth_index;
    size_t next_free;

    size_t total = 0;

    std::vector<std::string> new_cols;

    for(auto c: cols) {
        next_free = 0;
        cube_rock_index = c.find('#');
        smooth_index = c.find('O');

        while(smooth_index != std::string::npos) {
            smooth_index = c.find('O');

            while(smooth_index < cube_rock_index) {
                c[next_free] = 'S';

                if(next_free != smooth_index) {
                c[smooth_index] = '.';
                }

                smooth_index = c.find('O');
                next_free++;
            }

            if(cube_rock_index != std::string::npos) {
                next_free = cube_rock_index + 1;
                c[cube_rock_index] = 'R';
                cube_rock_index = c.find('#');
            }
        
        }

        std::replace(c.begin(), c.end(), 'R', '#');
        std::replace(c.begin(), c.end(), 'S', 'O');

        new_cols.push_back(c);
    }

    return new_cols;
}

std::vector<std::string> get_other(std::vector<std::string> arr) {
    std::vector<std::string> other;

    for(auto line: arr) {
        for(int i = 0; i < line.size(); i++) {
            if(i == other.size()) {
                std::string insert;
                insert += line[i];
                other.push_back(insert);
            } else {
                other[i] += line[i];
            }
        }
    }

    return other;
}

std::vector<std::string> rotate(std::vector<std::string> rows) {
    std::vector<std::string> cols;

    //North
    cols = get_other(rows);
    cols = push(cols);

    rows = get_other(cols);

    //West
    rows = push(rows);

    cols = get_other(rows);
    
    //South
    std::vector<std::string> reversed;
    std::string reversed_str;

    for(auto col: cols) {
        for(int i = col.size() - 1; i >= 0; i--) {
            reversed_str += col[i];
        }
        reversed.push_back(reversed_str);
        reversed_str.clear();
    }

    cols = push(reversed);

    reversed.clear();
    for(auto col: cols) {
        for(int i = col.size() - 1; i >= 0; i--) {
            reversed_str += col[i];
        }
        reversed.push_back(reversed_str);
        reversed_str.clear();
    }

    rows = get_other(reversed);

    //East
    reversed.clear();
    for(auto row: rows) {
        for(int i = row.size() - 1; i >= 0; i--) {
            reversed_str += row[i];
        }
        reversed.push_back(reversed_str);
        reversed_str.clear();
    }

    rows = push(reversed);

    reversed.clear();
    for(auto row: rows) {
        for(int i = row.size() - 1; i >= 0; i--) {
            reversed_str += row[i];
        }
        reversed.push_back(reversed_str);
        reversed_str.clear();
    }

    return reversed;
}

int main() {
    std::ifstream file("input_day14.txt");

    if (!file.is_open()) {
        perror(NULL);
        return 1;
    }

    std::string line;
    std::vector<std::string> rows;

    //separate the lines into columns to move the rocks easier
    while(std::getline(file, line)) {
        rows.push_back(line);
    }

    for(int i = 0; i < 1000000000; i++) {
        rows = rotate(rows);
    }

    size_t total = 0;

    for(auto r: rows) {
        for(int i = 0; i < r.size(); i++) {
            if(r[i] == 'O') {
                total += r.size() - i;
            }
        }
    }

    std::cout << total << std::endl;
}