// "Copyright [2019] <Baixiang>"  [legal/copyright]
#ifndef ASSIGNMENTS_WL_WORD_LADDER_H_
#define ASSIGNMENTS_WL_WORD_LADDER_H_
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "assignments/wl/lexicon.h"

// TODO(students): Add some stuff here
std::vector<std::vector<std::string>> findLadders(const std::string& start,
                                                  const std::string& end,
                                                  const std::unordered_set<std::string>& dict);
void findPath(std::unordered_map<std::string, std::set<std::string>>& back_trace,
              const std::string& cur,
              const std::string& end,
              std::vector<std::vector<std::string>>& result,
              std::vector<std::string>& single_result);
#endif  // ASSIGNMENTS_WL_WORD_LADDER_H_
