// "Copyright [2019] <Baixiang(Seele)>"  [legal/copyright]
#ifndef ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
#define ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_

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

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept { return what_.c_str(); }

 private:
  std::string what_;
};

class EuclideanVector {
 public:
  // Constructors
  explicit EuclideanVector(int i);
  EuclideanVector();
  EuclideanVector(int i, double value);
  EuclideanVector(std::vector<double>::iterator begin, std::vector<double>::iterator end);
  EuclideanVector(std::vector<double>::const_iterator begin,
                  std::vector<double>::const_iterator end);
  EuclideanVector(const EuclideanVector&);
  EuclideanVector(EuclideanVector&&) noexcept;

  // Destructor
  ~EuclideanVector() = default;

  // Operations
  EuclideanVector& operator=(const EuclideanVector&);
  EuclideanVector& operator=(EuclideanVector&&) noexcept;
  double& operator[](int index);
  double operator[](int index) const;
  EuclideanVector& operator+=(const EuclideanVector& ev);
  EuclideanVector& operator-=(const EuclideanVector& ev);
  EuclideanVector& operator*=(const double& v) noexcept;
  EuclideanVector& operator/=(const double& v);
  explicit operator std::vector<double>() const noexcept;
  explicit operator std::list<double>() const noexcept;

  // Methods
  double at(int index) const;
  double& at(int index);
  int GetNumDimensions() const noexcept;
  double GetEuclideanNorm() const;
  EuclideanVector CreateUnitVector() const;

  // Friends
  friend bool operator==(const EuclideanVector& lhs, const EuclideanVector& rhs) noexcept;
  friend bool operator!=(const EuclideanVector& lhs, const EuclideanVector& rhs) noexcept;
  friend EuclideanVector operator+(const EuclideanVector& lhs, const EuclideanVector& rhs);
  friend EuclideanVector operator-(const EuclideanVector& lhs, const EuclideanVector& rhs);
  friend double operator*(const EuclideanVector& lhs, const EuclideanVector& rhs);
  friend EuclideanVector operator*(const EuclideanVector& lhs, const double& rhs) noexcept;
  friend EuclideanVector operator*(const double& lhs, const EuclideanVector& rhs) noexcept;
  friend EuclideanVector operator/(const EuclideanVector& lhs, const double& rhs);
  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v);

 private:
  std::unique_ptr<double[]> magnitudes_;
  int num_dim;
};

// declare nonmember functions outside of class
bool operator==(const EuclideanVector& lhs, const EuclideanVector& rhs) noexcept;
bool operator!=(const EuclideanVector& lhs, const EuclideanVector& rhs) noexcept;
EuclideanVector operator+(const EuclideanVector& lhs, const EuclideanVector& rhs);
EuclideanVector operator-(const EuclideanVector& lhs, const EuclideanVector& rhs);
double operator*(const EuclideanVector& lhs, const EuclideanVector& rhs);
EuclideanVector operator*(const EuclideanVector& lhs, const double& rhs) noexcept;
EuclideanVector operator*(const double& lhs, const EuclideanVector& rhs) noexcept;
EuclideanVector operator/(const EuclideanVector& lhs, const double& rhs);
std::ostream& operator<<(std::ostream& os, const EuclideanVector& v);

#endif  // ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
