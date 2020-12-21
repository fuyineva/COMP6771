// "Copyright [2019] <Baixiang(Seele)>"  [legal/copyright]

/*

  == Explanation and rational of testing ==

  In this Assignment, at first, we create a class which is EuclideanVector. And it mainly consists
  of four parts. They are constructors, operations, methods and friends. Hence, this test will test
  the accuracy of each of the four parts in different situations.Such as I will build both non-const
  and const EuclideanVector and parameters and variables to test the correctness of Class on
  different scenarios.

  There are four test part and another one for test correctness by using pointer and reference
  method to create EuclideanVector type variables. And because the whole test is used GetNumDimens
  methods. So, I did not test this method alone.

  There are also some attentions. Firstly, because sometime the const variables can not change.
  Hence. I just ignore the const test on some operations ,such as +=, -=, *= and so forth. In
  addition, this test might be very large. The main reason is that I tried to test and validate all
  the scenarios which I could imagine. It just want to ensure the code can run on different
  scenarios. And there are also test the throw exception of the table given by using the
  REQUIRE_THROWS_WITH method.

  The last thing that I want to mention is that the test of << operation is already in the == and !=
  because you can check the expression, you will found that [1 1] == [1 1] or [1 1] 1= [1 1] which
  means that the expression of using << operation. And also this is a relatively simple test. So, if
  the code change, it will slightly influence the test.

  Thanks for your patient and your work!
  Best regards!
a
*/

#include <algorithm>  // Look at these - they are helpful https://en.cppreference.com/w/cpp/algorithm
#include <cassert>
#include <cmath>
#include <exception>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "assignments/ev/euclidean_vector.h"
#include "catch.h"
SCENARIO(
    "Test_1 :check that using different methods to build constructors and they should be worked",
    "[Constructors]") {
  GIVEN("create a EuclideanVector and const EuclideanVector by  giving a parameter int and const "
        "int as "
        "dimensions") {
    EuclideanVector test_1(2);
    const int i{2};
    const EuclideanVector test_1_1(i);
    THEN("The size should be correct") {
      REQUIRE(test_1.GetNumDimensions() == 2);
      REQUIRE(test_1_1.GetNumDimensions() == 2);
    }
    AND_THEN("Check the value should be working and the initial values should be 0") {
      REQUIRE(test_1.at(0) == 0.0);
      REQUIRE(test_1.at(1) == 0.0);
      REQUIRE(test_1_1.at(0) == 0.0);
      REQUIRE(test_1_1.at(1) == 0.0);
    }
  }

  GIVEN("create a EuclideanVector and a const EuclideanVector by default EuclideanVector") {
    EuclideanVector test_1_2 = EuclideanVector();
    const EuclideanVector test_1_3 = EuclideanVector();
    THEN("The size should be correct") {
      REQUIRE(test_1_2.GetNumDimensions() == 1);
      REQUIRE(test_1_3.GetNumDimensions() == 1);
    }
    AND_THEN("Check the value should also work and the initial values should be 0") {
      REQUIRE(test_1_2.at(0) == 0.0);
      REQUIRE(test_1_3.at(0) == 0.0);
    }
  }

  GIVEN("create a EuclideanVector and const EuclideanVector by A constructor that takes the number "
        "of dimensions (as a int) "
        "and initialises values") {
    EuclideanVector test_1_4{2, 1};       // explicit construct
    EuclideanVector test_1_4_1 = {2, 2};  // implicit construct
    const EuclideanVector test_1_5{2, 1};
    const EuclideanVector test_1_5_1 = {2, 2};
    THEN("The size should be correct") {
      REQUIRE(test_1_4.GetNumDimensions() == 2);
      REQUIRE(test_1_4_1.GetNumDimensions() == 2);
      REQUIRE(test_1_5.GetNumDimensions() == 2);
      REQUIRE(test_1_5_1.GetNumDimensions() == 2);
    }
    AND_THEN("Check the value should also work and the initial values are correct") {
      REQUIRE(test_1_4.at(0) == 1.0);
      REQUIRE(test_1_4.at(1) == 1.0);
      REQUIRE(test_1_4_1.at(0) == 2.0);
      REQUIRE(test_1_4_1.at(1) == 2.0);
      REQUIRE(test_1_5.at(0) == 1.0);
      REQUIRE(test_1_5.at(1) == 1.0);
      REQUIRE(test_1_5_1.at(0) == 2.0);
      REQUIRE(test_1_5_1.at(1) == 2.0);
    }
  }

  GIVEN("create a EuclideanVector and const EuclideanVector by A constructor (or constructors) "
        "that takes the start and end of an iterator to a std:vector"
        "and initialises values") {
    // create two type vector
    std::vector<double> l;
    l.push_back(5.0);
    l.push_back(6.5);
    l.push_back(7.0);
    EuclideanVector test_1_l{l.begin(), l.end()};

    std::vector<double> v{1, 2};
    const std::vector<double> v1{4, 5, 6};
    // create const_iterator
    std::vector<double>::const_iterator begin{v.begin()};
    std::vector<double>::const_iterator end{v.end()};
    // use normal vector
    EuclideanVector test_1_6{v.begin(), v.end()};
    const EuclideanVector test_1_7{v.begin(), v.end()};
    // use const vector
    EuclideanVector test_1_8{v1.begin(), v1.end()};
    const EuclideanVector test_1_9{v1.begin(), v1.end()};
    // use const_iterator
    EuclideanVector test_1_10{begin, end};
    const EuclideanVector test_1_11{begin, end};

    THEN("The size should be correct") {
      REQUIRE(test_1_6.GetNumDimensions() == 2);
      REQUIRE(test_1_7.GetNumDimensions() == 2);
      REQUIRE(test_1_8.GetNumDimensions() == 3);
      REQUIRE(test_1_9.GetNumDimensions() == 3);
      REQUIRE(test_1_10.GetNumDimensions() == 2);
      REQUIRE(test_1_11.GetNumDimensions() == 2);
      REQUIRE(test_1_l.GetNumDimensions() == 3);
    }
    AND_THEN("Check the value should also work and the initial values are correct") {
      REQUIRE(test_1_6.at(0) == 1.0);
      REQUIRE(test_1_6.at(1) == 2.0);
      REQUIRE(test_1_7.at(0) == 1.0);
      REQUIRE(test_1_7.at(1) == 2.0);
      REQUIRE(test_1_8.at(0) == 4.0);
      REQUIRE(test_1_8.at(1) == 5.0);
      REQUIRE(test_1_9.at(2) == 6.0);
      REQUIRE(test_1_9.at(0) == 4.0);
      REQUIRE(test_1_9.at(1) == 5.0);
      REQUIRE(test_1_9.at(2) == 6.0);
      REQUIRE(test_1_10.at(0) == 1.0);
      REQUIRE(test_1_10.at(1) == 2.0);
      REQUIRE(test_1_11.at(0) == 1.0);
      REQUIRE(test_1_11.at(1) == 2.0);
      REQUIRE(test_1_l.at(0) == 5.0);
      REQUIRE(test_1_l.at(1) == 6.5);
      REQUIRE(test_1_l.at(2) == 7.0);
    }
  }

  GIVEN("create a EuclideanVector and const EuclideanVector, then use copy constructor copy these "
        "two EuclideanVector to a a EuclideanVector and const EuclideanVector ") {
    EuclideanVector test_1_12{2, 1};
    const EuclideanVector test_1_13{2, 2};

    EuclideanVector test_1_14{test_1_12};
    EuclideanVector test_1_15{test_1_13};

    const EuclideanVector test_1_16{test_1_12};
    const EuclideanVector test_1_17{test_1_13};
    THEN("The size should be correct") {
      REQUIRE(test_1_14.GetNumDimensions() == 2);
      REQUIRE(test_1_15.GetNumDimensions() == 2);
      REQUIRE(test_1_16.GetNumDimensions() == 2);
      REQUIRE(test_1_17.GetNumDimensions() == 2);
    }
    AND_THEN("Check the value should also work and the initial values are correct") {
      REQUIRE(test_1_14.at(0) == 1.0);
      REQUIRE(test_1_14.at(1) == 1.0);
      REQUIRE(test_1_15.at(0) == 2.0);
      REQUIRE(test_1_15.at(1) == 2.0);
      REQUIRE(test_1_16.at(0) == 1.0);
      REQUIRE(test_1_16.at(1) == 1.0);
      REQUIRE(test_1_17.at(0) == 2.0);
      REQUIRE(test_1_17.at(1) == 2.0);
    }
  }

  GIVEN("create two EuclideanVectors, then use move constructor to build "
        "these two EuclideanVector to a a EuclideanVector and const EuclideanVector ") {
    // and in here actually the const EuclideanVector also can be std::move(const EuclideanVector)
    // but the this behavior I did not write this code even though I test it because it is not a
    // good example which means the if const object change value type , it maybe not very well.
    // And it is also cannot change to the 0 dimension due to the const property.SO, I just use
    // normal EuclideanVector to do the test.
    EuclideanVector test_1_18{2, 2};
    EuclideanVector test_1_19{std::move(test_1_18)};

    EuclideanVector test_1_18_1{2, 3};
    const EuclideanVector test_1_20{std::move(test_1_18_1)};

    THEN("The size should be correct and the moved object should be 0 dimension") {
      REQUIRE(test_1_19.GetNumDimensions() == 2);
      REQUIRE(test_1_18.GetNumDimensions() == 0);
      REQUIRE(test_1_20.GetNumDimensions() == 2);
      REQUIRE(test_1_18_1.GetNumDimensions() == 0);
    }
    AND_THEN("Check the value should also work and the initial values are correct") {
      REQUIRE(test_1_19.at(0) == 2.0);
      REQUIRE(test_1_19.at(1) == 2.0);
      REQUIRE(test_1_20.at(0) == 3.0);
      REQUIRE(test_1_20.at(1) == 3.0);
    }
  }
}

SCENARIO("Test_2 : check the different operations of EuclideanVectors", "[Operations]") {
  GIVEN("create  EuclideanVectors by normal giving  two parameters") {
    EuclideanVector test_2(2, 1);
    const EuclideanVector test_2_1(2, 2);
    WHEN("You use copy assignment operator to assign a new EuclideanVectors by using both"
         "non-const and const value") {
      EuclideanVector test_2_2;
      test_2_2 = test_2;
      EuclideanVector test_2_3;
      test_2_3 = test_2_1;
      THEN("The size should be correct") {
        REQUIRE(test_2_2.GetNumDimensions() == 2);
        REQUIRE(test_2_3.GetNumDimensions() == 2);
      }
      AND_THEN("Check the value should also work and the initial values are correct") {
        REQUIRE(test_2_2.at(0) == 1.0);
        REQUIRE(test_2_2.at(1) == 1.0);
        REQUIRE(test_2_3.at(0) == 2.0);
        REQUIRE(test_2_3.at(1) == 2.0);
      }
    }
  }

  GIVEN("create a non-const EuclideanVector by normal giving  two parameters") {
    EuclideanVector test_2_4(2, 1);
    WHEN("You use move assignment operator to assign a new EuclideanVectors by using "
         "non-const EuclideanVectors") {
      EuclideanVector test_2_5;
      test_2_5 = std::move(test_2_4);

      THEN("The size should be correct the moved object should be 0 dimension") {
        REQUIRE(test_2_4.GetNumDimensions() == 0);
        REQUIRE(test_2_5.GetNumDimensions() == 2);
      }
      AND_THEN("Check the value should also work and the initial values are correct") {
        REQUIRE(test_2_5.at(0) == 1.0);
        REQUIRE(test_2_5.at(1) == 1.0);
      }
    }
  }

  GIVEN("create two EuclideanVectors by normal giving  two parameters") {
    EuclideanVector test_2_6(2, 1);
    const EuclideanVector test_2_7(2, 2);
    WHEN("You get and set values on given dimension of the EuclideanVector") {
      double test_2_8{test_2_6[0]};
      double test_2_9{test_2_7[0]};
      test_2_6[0] = 3;
      test_2_6[1] = 4;
      THEN("The size should be correct and value should be correct") {
        REQUIRE(test_2_6.GetNumDimensions() == 2);
        REQUIRE(test_2_7.GetNumDimensions() == 2);
        REQUIRE(test_2_8 == 1.0);
        REQUIRE(test_2_9 == 2.0);
      }
      AND_THEN("Check the value should also work and the value after changed should be correct") {
        REQUIRE(test_2_6.at(0) == 3.0);
        REQUIRE(test_2_6.at(1) == 4.0);
        REQUIRE(test_2_7.at(0) == 2.0);
        REQUIRE(test_2_7.at(1) == 2.0);
      }
    }
  }

  GIVEN("create two EuclideanVectors by normal giving  two parameters") {
    EuclideanVector test_2_10(2, 1);
    const EuclideanVector test_2_11(2, 2);
    WHEN("EuclideanVector itself adding another EuclideanVector by using += and both have same "
         "dimension") {
      EuclideanVector test_2_12(2, 3);
      test_2_10 += test_2_11;
      test_2_12 += test_2_10;
      THEN("The size should be correct") {
        REQUIRE(test_2_10.GetNumDimensions() == 2);
        REQUIRE(test_2_11.GetNumDimensions() == 2);
        REQUIRE(test_2_12.GetNumDimensions() == 2);
      }
      AND_THEN("Check the value should also work and the value after changed should be correct") {
        REQUIRE(test_2_10.at(0) == 3.0);
        REQUIRE(test_2_10.at(1) == 3.0);
        REQUIRE(test_2_11.at(0) == 2.0);
        REQUIRE(test_2_11.at(1) == 2.0);
        REQUIRE(test_2_12.at(0) == 6.0);
        REQUIRE(test_2_12.at(1) == 6.0);
      }
    }
    AND_WHEN("EuclideanVector itself adding another EuclideanVector by using +=,but they are "
             "different dimensions") {
      EuclideanVector test_2_13(3, 3);
      THEN("It should be throw a exception which is Dimensions of LHS(X) and RHS(Y) do not match") {
        REQUIRE_THROWS_WITH(test_2_13 += test_2_10, "Dimensions of LHS(X) and RHS(Y) do not match");
      }
    }
  }

  GIVEN("create two EuclideanVectors by normal giving  two parameters") {
    EuclideanVector test_2_14(2, 2);
    const EuclideanVector test_2_15(2, 1);
    WHEN("EuclideanVector itself subtracting another EuclideanVector by using -= and both have "
         "same dimension") {
      EuclideanVector test_2_16(2, 3);
      test_2_14 -= test_2_15;
      test_2_16 -= test_2_14;
      THEN("The size should be correct") {
        REQUIRE(test_2_14.GetNumDimensions() == 2);
        REQUIRE(test_2_15.GetNumDimensions() == 2);
        REQUIRE(test_2_16.GetNumDimensions() == 2);
      }
      AND_THEN("Check the value should also work and the value after changed should be correct") {
        REQUIRE(test_2_14.at(0) == 1.0);
        REQUIRE(test_2_14.at(1) == 1.0);
        REQUIRE(test_2_15.at(0) == 1.0);
        REQUIRE(test_2_15.at(1) == 1.0);
        REQUIRE(test_2_16.at(0) == 2.0);
        REQUIRE(test_2_16.at(1) == 2.0);
      }
    }
    AND_WHEN("EuclideanVector itself subtracting another EuclideanVector by using -=,but they are "
             "different dimensions") {
      EuclideanVector test_2_17(3, 3);
      THEN("It should be throw a exception which is Dimensions of LHS(X) and RHS(Y) do not match") {
        REQUIRE_THROWS_WITH(test_2_17 -= test_2_14, "Dimensions of LHS(X) and RHS(Y) do not match");
      }
    }
  }

  GIVEN("create two double variables and one EuclideanVector") {
    double test_2_18{2.0};
    const double test_2_19{3.0};
    EuclideanVector test_2_20(2, 2);
    WHEN("EuclideanVector itself multiplying a double value by using *= ") {
      test_2_20 *= test_2_18;
      test_2_20 *= test_2_19;

      THEN("The size should be correct") { REQUIRE(test_2_20.GetNumDimensions() == 2); }
      AND_THEN("Check the value should also work and the value after changed should be correct") {
        REQUIRE(test_2_20.at(0) == 12.0);
        REQUIRE(test_2_20.at(0) == 12.0);
      }
    }
  }

  GIVEN("create two double variables and one EuclideanVector") {
    double test_2_21{2.0};
    const double test_2_22{5.0};
    EuclideanVector test_2_23(2, 10);
    WHEN("EuclideanVector itself dividing a double value by using /= ") {
      test_2_23 /= test_2_21;
      test_2_23 /= test_2_22;

      THEN("The size should be correct") { REQUIRE(test_2_23.GetNumDimensions() == 2); }
      AND_THEN("Check the value should also work and the value after changed should be correct") {
        REQUIRE(test_2_23.at(0) == 1.0);
        REQUIRE(test_2_23.at(0) == 1.0);
      }
    }
    AND_WHEN(
        "EuclideanVector itself dividing a double value by using /=,but the double value is 0") {
      EuclideanVector test_2_24(3, 3);
      THEN("It should be throw a exception which is Invalid vector division by 0") {
        REQUIRE_THROWS_WITH(test_2_24 /= 0.0, "Invalid vector division by 0");
      }
    }
  }

  GIVEN("create two EuclideanVectors which are none-const and const") {
    EuclideanVector test_2_25(2, 1);
    const EuclideanVector test_2_26(2, 2);
    WHEN("Operators for type casting to a std::vector") {
      auto test_2_27 = std::vector<double>{test_2_25};
      auto test_2_28 = std::vector<double>{test_2_26};
      THEN("The size should be correct") {
        REQUIRE(test_2_27.size() == 2);
        REQUIRE(test_2_28.size() == 2);
      }
      AND_THEN("Check the value should also work and value should be correct") {
        REQUIRE(test_2_27[0] == 1.0);
        REQUIRE(test_2_27[1] == 1.0);
        REQUIRE(test_2_28[0] == 2.0);
        REQUIRE(test_2_28[1] == 2.0);
      }
    }
  }

  GIVEN("create two EuclideanVectors which are none-const and const") {
    EuclideanVector test_2_29(2, 1);
    const EuclideanVector test_2_30(2, 2);
    WHEN("Operators for type casting to a std::list") {
      auto test_2_31 = std::list<double>{test_2_29};
      auto test_2_32 = std::list<double>{test_2_30};
      THEN("The size should be correct") {
        REQUIRE(test_2_31.size() == 2);
        REQUIRE(test_2_32.size() == 2);
      }
      AND_THEN("Check the value should also work and value should be correct") {
        REQUIRE(*test_2_31.begin() == 1.0);
        REQUIRE(*(++test_2_31.begin()) == 1.0);
        REQUIRE(*test_2_32.begin() == 2.0);
        REQUIRE(*(++test_2_32.begin()) == 2.0);
      }
    }
  }
}

SCENARIO("Test_3 : check the different methods of EuclideanVectors", "[Methods]") {
  GIVEN("create two EuclideanVectors by normal giving  two parameters") {
    EuclideanVector test_3(2, 1);
    const EuclideanVector test_3_1(2, 2);
    WHEN("You returns the reference of the magnitude in the dimension and change the value which "
         "used on non-const EuclideanVector") {
      test_3.at(0) = 2.0;
      THEN("The size should be correct and value should be correct") {
        REQUIRE(test_3.GetNumDimensions() == 2);
        REQUIRE(test_3.at(0) == 2.0);
      }
    }
    AND_WHEN("You use at() function to return a value and use that value for other purpose instead "
             "of change the value which is always the const EuclideanVector does") {
      double test_3_2{test_3_1.at(0)};
      THEN("The value should be correct and const EuclideanVector can use .at methods") {
        REQUIRE(test_3_2 == 2.0);
        REQUIRE(test_3_1.at(0) == 2.0);
      }
    }
  }

  GIVEN("create two EuclideanVectors") {
    std::vector<double> test_3_3{2, 4, 4};
    EuclideanVector test_3_4{test_3_3.begin(), test_3_3.end()};
    const EuclideanVector test_3_5{test_3_3.begin(), test_3_3.end()};
    WHEN("You calculate the Euclidean norm of the vector as a double") {
      double test_3_6 = test_3_4.GetEuclideanNorm();
      double test_3_7 = test_3_5.GetEuclideanNorm();
      THEN("The size should be correct") {
        REQUIRE(test_3_4.GetNumDimensions() == 3);
        REQUIRE(test_3_5.GetNumDimensions() == 3);
      }
      AND_THEN("Check the value should be correct") {
        REQUIRE(test_3_6 == 6.0);
        REQUIRE(test_3_7 == 6.0);
      }
    }
    AND_WHEN("EuclideanVector dimension is 0") {
      EuclideanVector test_3_8(0);
      double test_3_9;
      THEN("It should be throw a exception which is EuclideanVector with no dimensions does not "
           "have a norm") {
        REQUIRE_THROWS_WITH(test_3_9 = test_3_8.GetEuclideanNorm(),
                            "EuclideanVector with no dimensions does not have a norm");
      }
    }
  }

  GIVEN("create two EuclideanVectors") {
    std::vector<double> test_3_10{2, 4, 4};
    EuclideanVector test_3_11{test_3_10.begin(), test_3_10.end()};
    double v1{1.0 / 3.0};
    double v2{2.0 / 3.0};
    const EuclideanVector test_3_12{test_3_10.begin(), test_3_10.end()};
    WHEN("You calculate the UnitEuclideanVector of a EuclideanVector") {
      auto test_3_13 = test_3_11.CreateUnitVector();
      auto test_3_14 = test_3_12.CreateUnitVector();
      THEN("The size should be correct") {
        REQUIRE(test_3_13.GetNumDimensions() == 3);
        REQUIRE(test_3_14.GetNumDimensions() == 3);
      }
      AND_THEN("Check the value should be correct") {
        REQUIRE(test_3_13.at(0) == v1);
        REQUIRE(test_3_13.at(1) == v2);
        REQUIRE(test_3_13.at(2) == v2);
        REQUIRE(test_3_14.at(0) == v1);
        REQUIRE(test_3_14.at(1) == v2);
        REQUIRE(test_3_14.at(2) == v2);
      }
    }
    AND_WHEN("EuclideanVector dimension is 0") {
      EuclideanVector test_3_15(0);
      EuclideanVector test_3_16;
      THEN("It should be throw a exception which is EuclideanVector with no dimensions does not "
           "have a unit vector have a norm") {
        REQUIRE_THROWS_WITH(test_3_16 = test_3_15.CreateUnitVector(),
                            "EuclideanVector with no dimensions does not have a unit vector");
      }
    }
    AND_WHEN("EuclideanVector norm is 0") {
      EuclideanVector test_3_17(3, 0);
      EuclideanVector test_3_18;
      THEN("It should be throw a exception which is EuclideanVector with euclidean normal of 0 "
           "does not have a unit vector") {
        REQUIRE_THROWS_WITH(
            test_3_18 = test_3_17.CreateUnitVector(),
            "EuclideanVector with euclidean normal of 0 does not have a unit vector");
      }
    }
  }
}
SCENARIO("Test_4 : check the different friends of EuclideanVectors", "[Friends]") {
  GIVEN("create EuclideanVectors by normal giving  two parameters") {
    EuclideanVector test_4(2, 1);
    EuclideanVector test_4_1(2, 1);
    const EuclideanVector test_4_2(2, 1);
    const EuclideanVector test_4_3(2, 1);
    WHEN("You check the two EuclideanVectors are equal") {
      THEN("The expression should be correct") {
        REQUIRE(test_4 == test_4_1);
        REQUIRE(test_4 == test_4_2);
        REQUIRE(test_4_2 == test_4_3);
      }
    }
    AND_WHEN("You check  the two EuclideanVectors are not equal") {
      EuclideanVector test_4_4(2, 2);
      const EuclideanVector test_4_5(2, 2);
      EuclideanVector test_4_6(3, 1);
      const EuclideanVector test_4_7(3, 1);
      THEN("The expression should be correct") {
        REQUIRE(test_4 != test_4_4);
        REQUIRE(test_4 != test_4_5);
        REQUIRE(test_4 != test_4_6);
        REQUIRE(test_4 != test_4_7);
        REQUIRE(test_4_2 != test_4_4);
        REQUIRE(test_4_2 != test_4_5);
        REQUIRE(test_4_2 != test_4_6);
        REQUIRE(test_4_2 != test_4_7);
      }
    }
  }

  GIVEN("create two EuclideanVectors") {
    std::vector<double> test_4_8{2, 3, 4};
    std::vector<double> test_4_9{6, 7, 8};
    EuclideanVector test_4_10{test_4_8.begin(), test_4_8.end()};
    const EuclideanVector test_4_11{test_4_9.begin(), test_4_9.end()};
    const EuclideanVector test_4_11_1{test_4_9.begin(), test_4_9.end()};
    WHEN("You are adding or subtracting vectors of the same dimension.") {
      auto test_4_12 = test_4_10 + test_4_10;
      auto test_4_13 = test_4_10 + test_4_11;
      EuclideanVector test_4_14(2);
      test_4_14 = test_4_11 + test_4_11;
      auto test_4_15 = test_4_11 - test_4_10;
      auto test_4_16 = test_4_11_1 - test_4_11;
      THEN("The size should be correct") {
        REQUIRE(test_4_12.GetNumDimensions() == 3);
        REQUIRE(test_4_13.GetNumDimensions() == 3);
        REQUIRE(test_4_14.GetNumDimensions() == 3);
        REQUIRE(test_4_15.GetNumDimensions() == 3);
        REQUIRE(test_4_16.GetNumDimensions() == 3);
      }
      AND_THEN("Check the value should be correct") {
        REQUIRE(test_4_12.at(0) == 4.0);
        REQUIRE(test_4_12.at(1) == 6.0);
        REQUIRE(test_4_12.at(2) == 8.0);
        REQUIRE(test_4_13.at(0) == 8.0);
        REQUIRE(test_4_13.at(1) == 10.0);
        REQUIRE(test_4_13.at(2) == 12.0);
        REQUIRE(test_4_14.at(0) == 12.0);
        REQUIRE(test_4_14.at(1) == 14.0);
        REQUIRE(test_4_14.at(2) == 16.0);
        REQUIRE(test_4_15.at(0) == 4.0);
        REQUIRE(test_4_15.at(1) == 4.0);
        REQUIRE(test_4_15.at(2) == 4.0);
        REQUIRE(test_4_16.at(0) == 0.0);
        REQUIRE(test_4_16.at(1) == 0.0);
        REQUIRE(test_4_16.at(2) == 0.0);
      }
    }
    AND_WHEN("two 0 dimension EuclideanVector adding or subtracting ") {
      EuclideanVector test_4_0_L(0);
      EuclideanVector test_4_0_R(0);
      EuclideanVector test_4_0 = test_4_0_L + test_4_0_R;
      EuclideanVector test_4_0_1 = test_4_0_L - test_4_0_R;
      THEN("The result should also a 0 dimension") {
        REQUIRE(test_4_0.GetNumDimensions() == 0);
        REQUIRE(test_4_0_1.GetNumDimensions() == 0);
      }
    }
    AND_WHEN("two EuclideanVectors have different dimensions") {
      EuclideanVector test_4_17(3, 1);
      EuclideanVector test_4_18(4, 1);
      EuclideanVector test_4_19;
      EuclideanVector test_4_20;
      THEN("It should be throw a exception which is Dimensions of LHS(X) and RHS(Y) do not match") {
        REQUIRE_THROWS_WITH(test_4_19 = test_4_17 + test_4_18,
                            "Dimensions of LHS(X) and RHS(Y) do not match");
        REQUIRE_THROWS_WITH(test_4_20 = test_4_17 - test_4_18,
                            "Dimensions of LHS(X) and RHS(Y) do not match");
      }
    }
  }

  GIVEN("create two EuclideanVectors") {
    std::vector<double> test_4_21{2, 3, 4};
    std::vector<double> test_4_22{6, 7, 8};
    EuclideanVector test_4_23{test_4_21.begin(), test_4_21.end()};
    const EuclideanVector test_4_24{test_4_22.begin(), test_4_22.end()};
    WHEN("You are dot-product multiplication of two EuclideanVectors with same dimension .") {
      double test_4_25{test_4_23 * test_4_23};
      double test_4_26{test_4_23 * test_4_24};
      double test_4_27{test_4_24 * test_4_24};

      THEN("Check the value should be correct") {
        REQUIRE(test_4_25 == 29.0);
        REQUIRE(test_4_26 == 65.0);
        REQUIRE(test_4_27 == 149.0);
      }
    }
    AND_WHEN("You do product by a EuclideanVector(left) and a double(right)") {
      const double test_4_28{2};
      auto test_4_29 = test_4_23 * test_4_28;
      THEN("The size and value should be correct") {
        REQUIRE(test_4_29.GetNumDimensions() == 3);
        REQUIRE(test_4_29.at(0) == 4.0);
        REQUIRE(test_4_29.at(1) == 6.0);
        REQUIRE(test_4_29.at(2) == 8.0);
      }
    }
    AND_WHEN("You do product by a EuclideanVector(right) and a double(left)") {
      double test_4_30{3};
      auto test_4_31 = test_4_30 * test_4_24;
      THEN("The size and value should be correct") {
        REQUIRE(test_4_31.GetNumDimensions() == 3);
        REQUIRE(test_4_31.at(0) == 18.0);
        REQUIRE(test_4_31.at(1) == 21.0);
        REQUIRE(test_4_31.at(2) == 24.0);
      }
    }
    AND_WHEN("You do product by a 0 dimension EuclideanVector and a double") {
      EuclideanVector test_4_32(0);
      auto test_4_33 = test_4_32 * 2;
      auto test_4_34 = 2 * test_4_32;
      THEN("The result should also a 0 dimension") {
        REQUIRE(test_4_33.GetNumDimensions() == 0);
        REQUIRE(test_4_34.GetNumDimensions() == 0);
      }
    }

    AND_WHEN("two EuclideanVectors have different dimensions") {
      EuclideanVector test_4_35(3, 1);
      EuclideanVector test_4_36(4, 1);
      double test_4_37;
      THEN("It should be throw a exception which is Dimensions of LHS(X) and RHS(Y) do not match") {
        REQUIRE_THROWS_WITH(test_4_37 = test_4_35 * test_4_36,
                            "Dimensions of LHS(X) and RHS(Y) do not match");
      }
    }
  }

  GIVEN("create two double variables and one EuclideanVector") {
    double test_4_38{2.0};
    const double test_4_39{5.0};
    EuclideanVector test_4_40(3, 5);
    const EuclideanVector test_4_41(2, 10);
    WHEN("You do division operations with a EuclideanVector and a double variable ") {
      auto test_4_42 = test_4_40 / test_4_38;
      auto test_4_43 = test_4_41 / test_4_38;
      auto test_4_44 = test_4_40 / test_4_39;
      auto test_4_45 = test_4_41 / test_4_39;
      THEN("The size should be correct") {
        REQUIRE(test_4_42.GetNumDimensions() == 3);
        REQUIRE(test_4_43.GetNumDimensions() == 2);
        REQUIRE(test_4_44.GetNumDimensions() == 3);
        REQUIRE(test_4_45.GetNumDimensions() == 2);
      }
      AND_THEN("Check the value should be correct") {
        REQUIRE(test_4_42.at(0) == 2.5);
        REQUIRE(test_4_42.at(1) == 2.5);
        REQUIRE(test_4_42.at(2) == 2.5);
        REQUIRE(test_4_43.at(0) == 5.0);
        REQUIRE(test_4_43.at(1) == 5.0);
        REQUIRE(test_4_44.at(0) == 1.0);
        REQUIRE(test_4_44.at(1) == 1.0);
        REQUIRE(test_4_44.at(2) == 1.0);
        REQUIRE(test_4_45.at(0) == 2.0);
        REQUIRE(test_4_45.at(1) == 2.0);
      }
    }
    AND_WHEN("0 dimension EuclideanVector divide a double") {
      EuclideanVector test_4_46(0);
      auto test_4_47 = test_4_46 / 2;
      THEN("The result should also a 0 dimension") { REQUIRE(test_4_47.GetNumDimensions() == 0); }
    }
    AND_WHEN("EuclideanVector divide a double value which is 0") {
      EuclideanVector test_4_48(3, 3);
      EuclideanVector test_4_49;
      THEN("It should be throw a exception which is Invalid vector division by 0") {
        REQUIRE_THROWS_WITH(test_4_49 = test_4_48 / 0.0, "Invalid vector division by 0");
      }
    }
  }
}

SCENARIO("Test_5 : check the the pointer and reference work", "[Pointer and reference]") {
  GIVEN("create EuclideanVectors type pointer and reference") {
    EuclideanVector test_5(2, 1);
    const EuclideanVector test_5_1(2, 2);
    EuclideanVector* test_5_2{&test_5};
    const EuclideanVector* test_5_3{&test_5};
    EuclideanVector& test_5_4{test_5};
    const EuclideanVector& test_5_5{test_5_1};

    WHEN("You check the two pointer and reference") {
      THEN("The dimensions and values should be correct") {
        REQUIRE(test_5_2->GetNumDimensions() == 2);
        REQUIRE(test_5_3->GetNumDimensions() == 2);
        REQUIRE(test_5_4.GetNumDimensions() == 2);
        REQUIRE(test_5_5.GetNumDimensions() == 2);
        REQUIRE(test_5_2->at(0) == 1.0);
        REQUIRE(test_5_2->at(1) == 1.0);
        REQUIRE(test_5_3->at(0) == 1.0);
        REQUIRE(test_5_3->at(1) == 1.0);
        REQUIRE(test_5_4.at(0) == 1.0);
        REQUIRE(test_5_4.at(1) == 1.0);
        REQUIRE(test_5_5.at(0) == 2.0);
        REQUIRE(test_5_5.at(1) == 2.0);
      }
    }
    AND_WHEN("You change the value and do some operations") {
      test_5_2->at(0) = 3;
      test_5_4.at(0) = 4;    // reference change to 4
      *test_5_2 += test_5;   // test_5[0] already change to 4
      test_5_4 += test_5_1;  // now test_5_4[0] == test_5[0] == test_5_2->at(0) is 10;
      *test_5_2 *= 2;
      test_5_4 *= 2;
      *test_5_2 /= 2;
      test_5_4 /= 2;
      auto test_5_6 = *test_5_2 + test_5_4;
      auto test_5_7 = std::vector<double>(*test_5_2);
      auto test_5_8 = std::vector<double>(test_5_4);
      auto test_5_9 = *test_5_2 * test_5_4;
      THEN("The values after changed should be correct") {
        REQUIRE(test_5_2->at(0) == 10.0);
        REQUIRE(test_5_2->at(1) == 4.0);
        REQUIRE(test_5_4.at(0) == 10.0);
        REQUIRE(test_5_4.at(1) == 4.0);
        REQUIRE(test_5_6.at(0) == 20.0);
        REQUIRE(test_5_6.at(1) == 8.0);
        REQUIRE(test_5_7.size() == 2);
        REQUIRE(test_5_8.size() == 2);
        REQUIRE(test_5_7[0] == 10.0);
        REQUIRE(test_5_8[0] == 10.0);
        REQUIRE(test_5_9 == 116.0);
      }
    }
  }
}
