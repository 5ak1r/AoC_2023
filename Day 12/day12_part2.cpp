#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

// https://old.reddit.com/r/adventofcode/comments/18ghux0/2023_day_12_no_idea_how_to_start_with_this_puzzle/kd0npmi/
// https://www.youtube.com/watch?v=oBt53YbR9Kk

struct memoPipes {
  std::string pipes;
  std::vector<size_t> groups;

  bool operator<(const memoPipes& other) const {
    if (pipes != other.pipes) {
      return pipes < other.pipes;
    }

    return groups < other.groups;
  }
  
  bool operator==(const memoPipes& other) const {
        return pipes == other.pipes && groups == other.groups;
  }

};

std::map<memoPipes, size_t> memo;

size_t count_recur(std::string pipes, std::vector<size_t> groups) {
  
  //create struct for memoisation; not needed to be used throughout
  memoPipes memoise = memoPipes{pipes, groups};

  //memoisation
  if(memo.find(memoise) != memo.end()) {
    return memo[memoise];
  }

  //if no pipes left, fail if there are still groups
  if(pipes.size() == 0) {
    return groups.empty() ? 1 : 0;
  }
  
  size_t count = 0;
  if(pipes[0] == '.') {
    //ignore undamaged pipe at front
    count = count_recur(pipes.substr(1), groups);
  } else if(pipes[0] == '?') {
    //test for both cases, if '.' then can be ignored as above
    count = count_recur(pipes.substr(1), groups) + count_recur('#' + pipes.substr(1), groups);
  } else {
    if (groups.size() == 0) {
      //fail; no groups left but there are still damaged pipes
      count = 0;
    } else {
      size_t group = groups[0];
      //size of group is greater than remaining pipes or the next group pipes are not all # or ?; fail
      if(group > pipes.size() || pipes.substr(0, group).find('.') != std::string::npos) {
        count = 0;
      } else {
        //remove the group of damaged pipes we just looked at
        std::vector<size_t> next_groups(groups.begin() + 1, groups.end());
        
        if(group == pipes.size()) {
          count = next_groups.empty() ? 1 : 0;
        } else if(pipes[group] != '#') {
          //group removed was all damaged, next pipe must not be damaged; change '?' to '.' (will be skipped)
          count = count_recur(pipes.substr(group + 1), next_groups);
        } else {
          //fail; next pipe is damaged
          count = 0;
        }
      }
    }
  }

  //add this pattern to the map
  memo[memoise] = count;
  return count;
}


int main() {
  std::ifstream file("input_day12.txt");

  if (!file.is_open()) {
    perror(NULL);
    return 1;
  }

  std::string line;
  std::string pipes;

  std::vector<size_t> groups;

  std::vector<size_t> five_groups;
  std::string five_pipes;

  size_t total = 0;

  while(std::getline(file, line)) {
    groups.clear();
    five_groups.clear();
    five_pipes.clear();
    pipes = line.substr(0, line.find(" "));
    line = line.substr(line.find(" ") + 1);

    while(line.find(",") != std::string::npos) {
      groups.push_back(std::stoi(line.substr(0, line.find(","))));
      line = line.substr(line.find(",") + 1);
    }
    
    groups.push_back(std::stoi(line));


    for(int i = 0; i < 5; i++) {
        for(auto g: groups) {
            five_groups.push_back(g);
        }

        for(auto p: pipes) {
            five_pipes += p;
        }
        five_pipes += i == 4 ? "" : "?";
    }
    
    total += count_recur(five_pipes, five_groups);
  }

  std::cout << total << std::endl;
}