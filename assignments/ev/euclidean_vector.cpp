// "Copyright [2019] <Baixiang(Seele)>"  [legal/copyright]

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

// Constructors
// constructor that takes the number of dimensions but no magnitudes
// set dimension as argument 'n
EuclideanVector::EuclideanVector(int i) : magnitudes_{std::make_unique<double[]>(i)}, num_dim{i} {
  for (int index = 0; index < i; ++index) {
    magnitudes_[index] = 0.0;
  }
}

// This is default constructor, set dimension as 1 and
// magnitude in each dimension as as 0.0
// by using constructor EuclideanVector(1)
EuclideanVector::EuclideanVector() : EuclideanVector(1) {}

// constructor that takes the number of dimensions i and
// initialises the magnitude in each dimension set dimension as value
EuclideanVector::EuclideanVector(int i, double value)
  : magnitudes_{std::make_unique<double[]>(i)}, num_dim{i} {
  for (int index = 0; index < i; ++index) {
    magnitudes_[index] = value;
  }
}

// constructor that takes the begin and end of an std::vector<double> iterator
EuclideanVector::EuclideanVector(std::vector<double>::iterator begin,
                                 std::vector<double>::iterator end)
  : magnitudes_{std::make_unique<double[]>(static_cast<int>(std::distance(begin, end)))},
    num_dim{static_cast<int>(std::distance(begin, end))} {
  for (auto iter = begin; iter != end; ++iter) {
    magnitudes_[static_cast<int>(std::distance(begin, iter))] = *iter;
  }
}

// constructor that takes the begin and end of an std::vector<double> const_iterator
EuclideanVector::EuclideanVector(std::vector<double>::const_iterator begin,
                                 std::vector<double>::const_iterator end)
  : magnitudes_{std::make_unique<double[]>(static_cast<int>(std::distance(begin, end)))},
    num_dim{static_cast<int>(std::distance(begin, end))} {
  for (auto iter = begin; iter != end; ++iter) {
    magnitudes_[static_cast<int>(std::distance(begin, iter))] = *iter;
  }
}

// copy constructor
EuclideanVector::EuclideanVector(const EuclideanVector& orig)
  : magnitudes_{std::make_unique<double[]>(orig.num_dim)}, num_dim{orig.num_dim} {
  for (int index = 0; index < num_dim; ++index) {
    magnitudes_[index] = orig.magnitudes_[index];
  }
}

// move constructor
EuclideanVector::EuclideanVector(EuclideanVector&& orig) noexcept
  : magnitudes_{std::move(orig.magnitudes_)}, num_dim{orig.num_dim} {
  orig.num_dim = 0;
}

// Operations
// copy assignment
EuclideanVector& EuclideanVector::operator=(const EuclideanVector& orig) {
  if (this != &orig) {
    EuclideanVector tmp{orig};
    std::swap(tmp, *this);
  }
  return *this;
}

// move assignment
EuclideanVector& EuclideanVector::operator=(EuclideanVector&& orig) noexcept {
  // because the pointer is unique pointer, so we just change the pointing position
  // and the memory which the unique pointer pointed will be destructed automatically
  if (this != &orig) {
    magnitudes_ = std::move(orig.magnitudes_);
    num_dim = orig.num_dim;
    orig.num_dim = 0;
  }
  return *this;
}

// set the value in a given dimension
double& EuclideanVector::operator[](int index) {
  assert(index >= 0 && index < num_dim);
  return magnitudes_[index];
}

// get the value in a given dimension
double EuclideanVector::operator[](int index) const {
  assert(index >= 0 && index < num_dim);
  return magnitudes_[index];
}

// For adding vectors of the same dimension.
EuclideanVector& EuclideanVector::operator+=(const EuclideanVector& ev) {
  if (num_dim != ev.num_dim) {
    throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
  }
  for (int index = 0; index < num_dim; ++index) {
    magnitudes_[index] += ev.magnitudes_[index];
  }
  return *this;
}

// For subtracting vectors of the same dimension.
EuclideanVector& EuclideanVector::operator-=(const EuclideanVector& ev) {
  if (num_dim != ev.num_dim) {
    throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
  }
  for (int index = 0; index < num_dim; ++index) {
    magnitudes_[index] -= ev.magnitudes_[index];
  }
  return *this;
}

// For scalar multiplication, e.g. [1 2] * 3 = [3 6]
EuclideanVector& EuclideanVector::operator*=(const double& v) noexcept {
  for (int index = 0; index < num_dim; ++index) {
    magnitudes_[index] *= v;
  }
  return *this;
}

// For scalar division, e.g. [3 6] / 2 = [1.5 3]
EuclideanVector& EuclideanVector::operator/=(const double& v) {
  if (v == 0) {
    throw EuclideanVectorError("Invalid vector division by 0");
  }
  for (int index = 0; index < num_dim; ++index) {
    magnitudes_[index] /= v;
  }
  return *this;
}

// Operators for type casting to a std::vector
EuclideanVector::operator std::vector<double>() const noexcept {
  std::vector<double> v(num_dim);
  for (int index = 0; index < num_dim; ++index) {
    v[index] = magnitudes_[index];
  }
  return v;
}

// Operators for type casting to a std::list
EuclideanVector::operator std::list<double>() const noexcept {
  std::list<double> l;
  for (int index = 0; index < num_dim; ++index) {
    l.push_back(magnitudes_[index]);
  }
  return l;
}

// Methods
// Returns the value of the magnitude in the dimension given as the function parameter
double EuclideanVector::at(int index) const {
  if (index < 0 || index >= num_dim) {
    throw EuclideanVectorError("Index X is not valid for this EuclideanVector object");
  }
  return magnitudes_[index];
}

// Returns the reference of the magnitude in the dimension given as the function parameter
double& EuclideanVector::at(int index) {
  if (index < 0 || index >= num_dim) {
    throw EuclideanVectorError("Index X is not valid for this EuclideanVector object");
  }
  return magnitudes_[index];
}

// Return the number of dimensions in a particular EuclideanVector
int EuclideanVector::GetNumDimensions() const noexcept {
  return num_dim;
}

// Returns the Euclidean norm of the vector as a double.
double EuclideanVector::GetEuclideanNorm() const {
  if (this->GetNumDimensions() == 0) {
    throw EuclideanVectorError("EuclideanVector with no dimensions does not have a norm");
  }
  double norm = 0;
  for (int index = 0; index < num_dim; ++index) {
    norm += pow(magnitudes_[index], 2);
  }
  return sqrt(norm);
}

// Returns a Euclidean vector that is the unit vector of *this vector.
EuclideanVector EuclideanVector::CreateUnitVector() const {
  if (this->GetNumDimensions() == 0) {
    throw EuclideanVectorError("EuclideanVector with no dimensions does not have a unit vector");
  }
  if (this->GetEuclideanNorm() == 0) {
    throw EuclideanVectorError(
        "EuclideanVector with euclidean normal of 0 does not have a unit vector");
  }
  EuclideanVector result(num_dim);
  const double norm_value = this->GetEuclideanNorm();
  for (int index = 0; index < num_dim; ++index) {
    result.magnitudes_[index] = magnitudes_[index] / norm_value;
  }
  return result;
}

// Friends
// overload of operator '==' for checking if two Euclidean vectors are equal
bool operator==(const EuclideanVector& lhs, const EuclideanVector& rhs) noexcept {
  if (lhs.num_dim != rhs.num_dim) {
    return false;
  }
  for (int index = 0; index < lhs.num_dim; ++index) {
    if (lhs.magnitudes_[index] != rhs.magnitudes_[index]) {
      return false;
    }
  }
  return true;
}

// overload of operator '!=' for checking if two Euclidean vectors are not equal
bool operator!=(const EuclideanVector& lhs, const EuclideanVector& rhs) noexcept {
  return !(lhs == rhs);
}

// For adding vectors of the same dimension
EuclideanVector operator+(const EuclideanVector& lhs, const EuclideanVector& rhs) {
  if (lhs.GetNumDimensions() != rhs.GetNumDimensions()) {
    throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
  }
  EuclideanVector result(lhs);
  result += rhs;
  return result;
}

// For subtracting vectors of the same dimension.
EuclideanVector operator-(const EuclideanVector& lhs, const EuclideanVector& rhs) {
  if (lhs.GetNumDimensions() != rhs.GetNumDimensions()) {
    throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
  }
  EuclideanVector result(lhs);
  result -= rhs;
  return result;
}

// For dot-product multiplication, returns a double.
double operator*(const EuclideanVector& lhs, const EuclideanVector& rhs) {
  if (lhs.GetNumDimensions() != rhs.GetNumDimensions()) {
    throw EuclideanVectorError("Dimensions of LHS(X) and RHS(Y) do not match");
  }
  double result = 0;
  for (int index = 0; index < lhs.num_dim; ++index) {
    result += lhs.magnitudes_[index] * rhs.magnitudes_[index];
  }
  return result;
}

// Overload of operator '*' for scalar multiplication, the vector is at left side
EuclideanVector operator*(const EuclideanVector& lhs, const double& rhs) noexcept {
  EuclideanVector result(lhs);
  result *= rhs;
  return result;
}

// Overload of operator '*' for scalar multiplication, the vector is at right side
EuclideanVector operator*(const double& lhs, const EuclideanVector& rhs) noexcept {
  return rhs * lhs;
}

// For scalar division
EuclideanVector operator/(const EuclideanVector& lhs, const double& rhs) {
  if (rhs == 0) {
    throw EuclideanVectorError("Invalid vector division by 0");
  }
  EuclideanVector result(lhs);
  result /= rhs;
  return result;
}

// Prints out the magnitude in each dimension of the Euclidean Vector
std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) {
  os << "[";
  for (int index = 0; index < v.num_dim; ++index) {
    os << v.magnitudes_[index];
    if (index != v.num_dim - 1) {
      os << " ";
    }
  }
  os << "]";
  return os;
}
