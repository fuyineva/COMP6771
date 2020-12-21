#include "lectures/week3/intarray.h"
#include <iostream>

IntArray::IntArray(int size) : values_{new int[size]}, size_{size} {
  for (auto i = 0; i < size; ++i) {
    values_[i] = 0;
  }
}

IntArray::~IntArray() noexcept {
  delete[] values_;
}

int& IntArray::At(int i){
  return values_[i];
}

const int& IntArray::At(int i) const {
  return values_[i];
}
int IntArray::size() const {
  // size_ is shorthand for this->size_.
  return size_;
}

IntArray::IntArray(const IntArray& org):values_{new int[org.size_]},size_{org.size_} {
  for (int i =0 ; i<size_; ++i){
    values_[i]=org.values_[i];
  }
}

IntArray::IntArray(IntArray&& orig) noexcept: values_{orig.values_},size_{orig.size_} {
  orig.values_= nullptr;
  orig.size_=0;
}




IntArray& IntArray::operator=(const IntArray& orig) {
  std::cout<<"="<<std::endl;
  IntArray tem{orig};
  std::swap(tem,*this);
  return *this;
}





IntArray& IntArray::operator=(IntArray&& orig) noexcept {
  std::cout<<"=="<<std::endl;
  delete [] values_;
  values_ = orig.values_;
  size_ = orig.size_;
  orig.values_= nullptr;
  orig.size_=0;
  return *this;
}

