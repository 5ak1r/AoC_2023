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

std::vector<std::string> rotate(std::vector<std::string> cols) {
    std::vector<std::string> new_cols;

    //North
    for(auto line: cols) {
        for(int i = 0; i < line.size(); i++) {
            if(i == new_cols.size()) {
                std::string insert;
                insert += line[i];
                new_cols.push_back(insert);
            } else {
                new_cols[i] += line[i];
            }
        }
    }

    new_cols = push(new_cols);

    //West
    cols.clear();
    for(auto line: new_cols) {
        for(int i = 0; i < line.size(); i++) {
            if(i == cols.size()) {
                std::string insert;
                insert += line[i];
                cols.push_back(insert);
            } else {
                cols[i] += line[i];
            }
        }
    }
    
    cols = push(cols);


    //South
    new_cols.clear();
    for(int i = cols.size() - 1; i > 0; i--) {
        for(int j = 0; j < cols[i].size(); j++) {
            if(j == new_cols.size()) {
                std::string insert;
                insert += cols[i][j];
                new_cols.push_back(insert);
            } else {
                new_cols[j] += cols[i][j];
            }
        }
    }

    new_cols = push(new_cols);

    for(auto c: new_cols) {
        std::cout << c <<std::endl;
    }
    std::cout << std::endl << std::endl;

    //East
    cols.clear();
    for(int i = new_cols.size() - 1; i > 0; i--) {
        for(int j = new_cols[i].size() - 1; j > 0; j--) {
            if(j == cols.size()) {
                std::string insert;
                insert += new_cols[i][j];
                cols.push_back(insert);
            } else {
                cols[j] += new_cols[i][j];
            }
        }
    }

    for(auto c: cols) {
        std::cout << c <<std::endl;
    }
    return new_cols;
}

int main() {
    std::ifstream file("input_day14.txt");

    if (!file.is_open()) {
        perror(NULL);
        return 1;
    }

    std::string line;
    std::vector<std::string> cols;
    std::vector<std::string> pushed_cols;


    //separate the lines into columns to move the rocks easier
    while(std::getline(file, line)) {
        cols.push_back(line);
    }

    cols = rotate(cols);

    size_t total = 0;

    for(auto c: cols) {
        for(int i = 0; i < c.size(); i++) {
            if(c[i] == 'O') {
                total += c.size() - i;
            }
        }
    }

    std::cout << total << std::endl;
}