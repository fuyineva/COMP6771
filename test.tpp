#include <iostream>
// #include "test.h"

template <typename T>
T& fin(T& a){
  a+=1 ;
  T& b = a;
  return b;
}

