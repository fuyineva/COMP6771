// "Copyright [2019] <Baixiang>"  [legal/copyright]

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"


int main() {
  std::vector<std::vector<std::string>> results;
  auto lexicon = GetLexicon("assignments/wl/words.txt");

  // TODO(students): Replace this with your code
  std::string begin;
  std::string end;
  std::cout << "Enter start word (RETURN to quit): ";
  std::getline(std::cin, begin);

  if (begin.empty()) {
    return EXIT_SUCCESS;
  }
  std::cout << "Enter destination word: ";
  std::getline(std::cin, end);

  if (begin == end) {
    std::cout << "No ladder found." << std::endl;
    return EXIT_SUCCESS;
  }

  transform(begin.begin(), begin.end(), begin.begin(), ::tolower);
  transform(end.begin(), end.end(), end.begin(), ::tolower);

  auto check_begin = lexicon.find(begin);
  auto check_end = lexicon.find(end);

  if (check_begin == lexicon.end() || check_end == lexicon.end()) {
    std::cout << "No ladder found." << std::endl;
    return EXIT_SUCCESS;
  }

  results = findLadders(begin, end, lexicon);
  //  std::cout << results.size() << std::endl;
  //  std::cout << results.front().size() << std::endl;

  if (results.empty()) {
    std::cout << "No ladder found." << std::endl;
    return EXIT_SUCCESS;
  } else {
    std::cout << "Found ladder: " << std::ends;
    for (const auto& level1 : results) {
      for (const auto& level2 : level1) {
        std::cout << level2 << " " << std::ends;
      }
      std::cout << std::endl;
    }
  }
//    for (int i = 0; i < static_cast<int>(results.size()); ++i) {
//      for (int j = 0; j < static_cast<int>(results[i].size()); ++j) {
//        if (i < static_cast<int>(results.size()) - 1) {
//          if (results[i][j] != results[i + 1][j]) {
//            if (results[i][j] <= results[i + 1][j]) {
//              //            std::cout<<"right"<<std::endl;
//              break;
//            } else {
//              std::cout << "erro" << std::endl;
//              std::cout << i << ":" << results[i][j] << std::endl;
//              std::cout << i + 1 << ":" << results[i + 1][j] << std::endl;
//            }
//          }
//
//        } else {
//          break;
//        }
//      }
//    }
  return EXIT_SUCCESS;
}
