#include <iostream>
#include <string>
#include <fstream>

int main() {

    std::ifstream file("input_day01.txt");
    
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    long grand_total = 0;
    while(std::getline(file, line)) {
        int n = line.length();
        long total = 0;

        for (int i=0; i < n; i++) {
            if (isdigit(line[i])) {
                total += (line[i] - '0')*10;
                break;
            } 
        }

        for (int i=n-1; i >= 0; i--) {
            if (isdigit(line[i])) {
                total += line[i] - '0';
                break;
            } 
        }
        grand_total += total;

    }

    std::cout << grand_total << '\n';
}