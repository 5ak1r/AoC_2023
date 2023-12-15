#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <fstream>

int main() {

    std::ifstream file("input_day01.txt");
    
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }


    std::map<std::string, std::string> word_to_number = {
        {"one","o1e"},
        {"two","t2o"},
        {"three","t3e"},
        {"four","f4r"},
        {"five","f5e"},
        {"six","s6x"},
        {"seven","s7n"},
        {"eight","e8t"},
        {"nine","n9e"},
    };

    std::string line;
    long grand_total = 0;
    while(std::getline(file, line)) {
        int n = line.length();
        long total = 0;

        std::map<std::string, std::string>::iterator it = word_to_number.begin();
        while (it != word_to_number.end()) {
            size_t pos = line.find(it->first);
            while(pos != std::string::npos) {
                line.replace(pos, it->first.length(), it->second);
                pos = line.find(it->first);
                
            }

            ++it;
        }
        
        std::cout << line << std::endl;

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