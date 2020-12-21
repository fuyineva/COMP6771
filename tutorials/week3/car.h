#ifndef TUTORIALS_WEEK3_CAR_H_
#define TUTORIALS_WEEK3_CAR_H_

#include <string>

class Car {
 public:
  // TODO(tutorial): fill me in
  Car(): manufacturer_{"unknown"},num_seats_{4} {++n_objects;}
  Car(const std::string& manufacturer, int n_seats);

  Car(const Car&other);
  Car(Car&& other) noexcept;
  Car& operator=(const Car&) = default;
  Car& operator=(Car&&) = default;
  ~Car() noexcept;

  const std::string& GetManufacturer() const;
  int GetNumSeats() const;
  static int GetNumCars();


 private:
  std::string manufacturer_;
  int num_seats_;
  static int n_objects;

};

#endif  // TUTORIALS_WEEK3_CAR_H_
