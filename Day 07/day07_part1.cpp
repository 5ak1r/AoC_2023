#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

int calc_kind(std::string);

//finally using structs sorry about previous solutions
typedef struct {
    std::string hand;
    int bid;
    int kind;
} Cards;

std::vector<Cards> cards;

std::string hand;
int bid;

int calc_kind(std::string hand) {
    std::map<char, int> dupes;

    for(auto card: hand) {
        dupes[card] += 1;
    }

    return std::max_element(dupes.begin(), dupes.end(),
    [](const auto& val1, const auto& val2) { return val1.second < val2.second; })->second;
}


int main() {
    std::ifstream file("input_day07.txt");
        
    if (!file.is_open()) {
        perror(NULL);
        return 1;
    }

    while(file >> hand >> bid) {
        cards.push_back(Cards{hand, bid, calc_kind(hand)});
    }

    for (auto card: cards) {
        std::cout << card.bid << " " << card.hand << " " << card.kind << '\n';
    }
}