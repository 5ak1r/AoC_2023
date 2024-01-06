#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>


//finally using structs sorry about previous solutions
typedef struct {
    std::string hand;
    int bid;
    int kind;
} Cards;

std::vector<Cards> cards;

std::string hand;
int bid;
int grand_total = 0;

void swap(Cards *a, Cards *b) {
    Cards t = *a;
    *a = *b;
    *b = t;
}

int partition(std::vector<Cards>& cards, int low, int high) {
    Cards pivot = cards[high];
    int i = low - 1;

    for(int j = low; j < high; j++) {
        if (cards[j].kind <= pivot.kind) {
            i++;
            swap(&cards[i], &cards[j]);
        }
    }

    swap(&cards[i+1], &cards[high]);
    return (i+1);
}

void quick_sort(std::vector<Cards>& cards, int low, int high) {
    if (low < high) {
        int part = partition(cards, low, high);
        quick_sort(cards, low, part-1);
        quick_sort(cards, part+1, high);
    }
}

void sort_same(std::vector<Cards>& cards) {
    std::string priority = "AKQJT98765432";

    int n = cards.size();
    
    //why did I think bubble sort would be fun
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            for(int k = 0; k < 5; k++) {
                if(cards[j].kind == cards[j+1].kind) {
                    if (priority.find(cards[j].hand[k]) < priority.find(cards[j+1].hand[k])) {
                        swap(&cards[j], &cards[j+1]);
                        break;
                    } else if(priority.find(cards[j].hand[k]) > priority.find(cards[j+1].hand[k])) {
                        break;
                    }
                }
            }
        }
    }
}

int calc_kind(std::string hand) {
    std::map<char, int> dupes;

    for(auto card: hand) {
        dupes[card] += 1;
    }

    int kind = std::max_element(dupes.begin(), dupes.end(),
    [](const auto& val1, const auto& val2) { return val1.second < val2.second; })->second;

    //two pair
    if (kind == 2) {
        int twos = 0;
        for(auto key: dupes) {
            if(key.second == 2) {
                twos++;
            }
        }

        if(twos == 2) {
            return 3;
        }
        return 2;
    }

    //full house
    if(kind == 3) {
        for(auto key: dupes) {
            if(key.second == 2) {
                return 5;
            }
        }
        return 4;
    }

    return kind > 3 ? kind + 2: kind;
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

    quick_sort(cards, 0, cards.size()-1);
    sort_same(cards);

    int counter = 1;
    for(auto card: cards) {
        grand_total += card.bid * counter;
        //std::cout << grand_total << '\n';
        std::cout << card.hand << " " << card.kind << " " << counter << '\n';
        counter++;
    }

    std::cout << grand_total << '\n';
}