#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "tutorials/week3/dictionary_library.h"

int main() {
  std::ifstream word_list_file = std::ifstream{"data/words.txt"};
  std::vector<std::string> aa = ToWordList(word_list_file);
  std::cout<< aa.size()<<std::endl;
  PrintValidWords(ToWordList(word_list_file), std::cin, std::cout);
  return 0;
}
