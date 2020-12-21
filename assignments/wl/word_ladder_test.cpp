// "Copyright [2019] <Baixiang>"  [legal/copyright]
/*

  == Explanation and rational of testing ==
  In this assignment, at first , I have finished the test file
  before doing the main programming work of this assignment.
  The main reason for doing this at first is that I need predict
  the expected results by using a small dictionary, and make the enough considering
  of the test as possible. In here, I use auto small dictionary which just contain 8 words.
  But it can give the scenario like the words.txt,
  because there are 4 scenarios can basically include different scenarios.
  which are:
  first we consider no dict, then we will get empty result and then,
  1. When input just the return key, we need finished immediately, which means it is the same with
  that we need get the empty results if we use the word_ladder function.
  2. When input is valid,but there is no path between the start word and destination word,then
  we need get a empty results.
  3. When input is valid and there is auto just one path. So, we can check the results size at first
  and also can check the specific results.
  4. It is same with the third scenario, but in this scenario, we can get many path rather than one.
  Hence, we can check the size and compare each path order and correctness.

  In this test, it is not consider the invalid input word, because there is demonstration on the
  forums and also for the length of the word.

  This test is just a small test, but it works and useful to test the program. And because the build
  file is not contain the data, so I just make a dictionary which can satisfy the different
  scenarios as possible.

  If you want to use words.txt, just change the code sightly, most of the code does not require to
  be changed. Thank you very much!
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "assignments/wl/word_ladder.h"
#include "catch.h"

// TODO(students): Fill this in.

using Catch::Matchers::Equals;

SCENARIO("Test : check the results if there is no word_list", "[no dict]") {
  GIVEN("start word and end word(actually whatever they are)") {
    std::unordered_set<std::string> word_list{};
    std::string start = "hit";
    std::string destination = "cog";  // atctually it cannot show you enter destination word
    WHEN("You call the SearchWord function") {
      auto result = findLadders(start, destination, word_list);
      THEN("You should get a empty results") {
        REQUIRE(result.empty());
        result.clear();
      }
    }
  }
}

SCENARIO("Test 1: check the results if there is no input", "[no input]") {
  GIVEN("empty start word (return) and end word(actually whatever it is)") {
    std::unordered_set<std::string> word_list{"hit", "hot", "dot", "dog",
                                              "lot", "log", "cog", "car"};
    std::string start;
    std::string destination = "hiad";  // atctually it cannot show you enter destination word
    WHEN("You call the SearchWord function") {
      auto result1 = findLadders(start, destination, word_list);
      THEN("You should get a empty results") {
        REQUIRE(result1.empty());
        result1.clear();
      }
    }
  }
}

SCENARIO("Test 2: check the results if there is no ladder", "[no ladder]") {
  GIVEN("Input valid start word and end word") {
    std::unordered_set<std::string> word_list{"hit", "hot", "dot", "dog",
                                              "lot", "log", "cog", "car"};
    std::string start = "hit";
    std::string destination = "car";
    WHEN("You call the SearchWord function") {
      auto result2 = findLadders(start, destination, word_list);
      THEN("You will get a empty results") {
        REQUIRE(result2.empty());
        result2.clear();
      }
    }
  }
}

SCENARIO("Test 3: check the results if there is just one ladder", "[one ladder]") {
  GIVEN("Input valid start word and end word") {
    std::unordered_set<std::string> word_list{"hit", "hot", "dot", "dog",
                                              "lot", "log", "cog", "car"};
    std::string start = "hit";
    std::string destination = "dot";
    const std::vector<std::string> compare_result{"hit", "hot", "dot"};
    WHEN("Call the SearchWord function") {
      auto result3 = findLadders(start, destination, word_list);
      THEN("You will get just one results") {
        REQUIRE(result3.size() == 1);
        REQUIRE_THAT(result3.back(), Catch::Matchers::Equals(compare_result));
        result3.clear();
      }
    }
  }
}

SCENARIO("Test4: check the results if there are many ladders", "[ladders]") {
  GIVEN("Input valid start word and end word") {
    std::unordered_set<std::string> word_list{"hit", "hot", "dot", "dog",
                                              "lot", "log", "cog", "car"};
    std::string start = "hit";
    std::string destination = "cog";
    const std::vector<std::vector<std::string>> compare_result{{"hit", "hot", "dot", "dog", "cog"},
                                                               {"hit", "hot", "lot", "log", "cog"}};
    WHEN("Call the SearchWord function") {
      auto result4 = findLadders(start, destination, word_list);
      std::cout << result4.size() << std::endl;

      THEN("You will get a empty results") {
        REQUIRE(result4.size() == 2);
        REQUIRE_THAT(result4[0], Catch::Matchers::Equals(compare_result[0]));
        REQUIRE_THAT(result4[1], Catch::Matchers::Equals(compare_result[1]));
        result4.clear();
      }
    }
  }
}
