// "Copyright [2019] <Baixiang>"  [legal/copyright]
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "assignments/wl/word_ladder.h"

std::vector<std::vector<std::string>> findLadders(const std::string& start,
                                                  const std::string& end,
                                                  const std::unordered_set<std::string>& dict) {
  std::vector<std::vector<std::string>> result;
  std::vector<std::string> single_result;

  std::unordered_map<std::string, std::set<std::string>> back_trace;
  std::unordered_set<std::string> dict1 = dict;
  std::unordered_set<std::string> dict2 = dict;

  std::vector<std::set<std::string>> level(2);
  std::vector<std::set<std::string>> level2(2);
  std::set<std::string> connection;

  int flag, nflag;
  flag = 0;
  nflag = !flag;
  int flag1, nflag1;
  flag1 = 0;
  nflag1 = !flag1;

  bool find = false;

  level[flag].insert(start);
  level2[flag1].insert(end);

  char ch, ch1;
  std::string word;
  std::string word1;

  while (!dict1.empty() && !dict2.empty()) {
    flag = !flag;
    nflag = !nflag;
    level[flag].clear();
    for (const auto& item : level[nflag]) {
      dict1.erase(item);
    }
    for (const auto& item : level[nflag]) {
      word = item;
      for (int i = 0; i < static_cast<int>(word.length()); ++i) {
        for (ch = 'a'; ch <= 'z'; ++ch) {
          std::string word_change1 = word.substr(0, i) + ch + word.substr(i + 1);
          if (dict1.find(word_change1) != dict1.end()) {
            // check the value in the level
            if (level2[flag1].find(word_change1) != level2[flag1].end()) {
              back_trace[item].insert(word_change1);
              find = true;
            } else {
              back_trace[item].insert(word_change1);
              level[flag].insert(word_change1);
            }
          }
        }
      }
    }
    if (level[flag].empty() || level[flag].count(end) > 0) {
      //  not found or found
      break;
    }

    //    std::set_intersection(level[flag].begin(), level[flag].end(), level2[flag1].begin(),
    //                          level2[flag1].end(), inserter(connection, connection.begin()));
    //    if (!connection.empty()) {
    //      break;
    //    }
    if (find) {
      break;
    }
    // end to start

    flag1 = !flag1;
    nflag1 = !nflag1;
    level2[flag1].clear();
    for (const auto& item : level2[nflag1]) {
      dict2.erase(item);
    }
    for (const auto& item : level2[nflag1]) {
      word1 = item;
      for (int i = 0; i < static_cast<int>(word.length()); ++i) {
        for (ch1 = 'a'; ch1 <= 'z'; ++ch1) {
          std::string word_change2 = word1.substr(0, i) + ch1 + word1.substr(i + 1);
          if (dict2.find(word_change2) != dict2.end()) {
            // check the value in the level
            if (level[flag].find(word_change2) != level[flag].end()) {
              back_trace[word_change2].insert(item);
              find = true;
            } else {
              back_trace[word_change2].insert(item);
              level2[flag1].insert(word_change2);
            }
          }
        }
      }
    }
    if (level2[flag1].empty() || level2[flag1].count(start) > 0) {
      //  not found or found
      break;
    }
    if (find) {
      break;
    }
  }

  if (!back_trace.empty()) {
    findPath(back_trace, start, end, result, single_result);
  }

  return result;
}

void findPath(std::unordered_map<std::string, std::set<std::string>>& back_trace,
              const std::string& cur,
              const std::string& end,
              std::vector<std::vector<std::string>>& result,
              std::vector<std::string>& single_result) {
  if (back_trace.count(cur) == 0 && cur == end) {
    // this word has no trace, it is the result.
    std::vector<std::string> single_path(single_result);

    single_path.push_back(cur);
    result.push_back(single_path);
    return;
  } else {
    // this is not the path
    if (back_trace.count(cur) == 0 && cur != end) {
      return;
    }
  }

  const std::set<std::string>& v = back_trace[cur];
  std::set<std::string>::const_iterator usit;

  single_result.push_back(cur);
  for (usit = v.begin(); usit != v.end(); ++usit) {
    findPath(back_trace, *usit, end, result, single_result);
  }
  single_result.pop_back();
}
