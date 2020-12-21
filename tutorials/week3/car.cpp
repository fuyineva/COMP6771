#include "tutorials/week3/car.h"
#include <iostream>
// TODO(tutorial): fill me in
int Car::n_objects = 0;

Car::Car(const std::string& manufacturer, int n_seats): manufacturer_{manufacturer}, num_seats_{n_seats} {
  ++n_objects;
}

Car::Car(const Car& other):manufacturer_{other.manufacturer_},num_seats_{other.num_seats_} {n_objects++;}
Car::Car(Car&& other) noexcept :manufacturer_{std::move(other.manufacturer_)},num_seats_{std::move(other.num_seats_)}{
  n_objects++;
  std::cout<<"copy rvalue"<<std::endl;}

Car::~Car() noexcept {
  --n_objects;
}

const std::string& Car::GetManufacturer() const { return manufacturer_;}

int Car::GetNumSeats() const { return num_seats_;}
int Car::GetNumCars() { return n_objects;}

