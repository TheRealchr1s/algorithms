#include "absl/strings/str_join.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

class Vec2
{
public:
  // Constructs a Vec2 object with given x and y coordinates.
  Vec2(int x, int y) : x_(x), y_(y) {}

  // Accessors for x and y coordinates.
  int x() const { return x_; }
  int y() const { return y_; }

  // Computes the L2 norm of the vector.
  double L2Norm() const { return std::sqrt(ComputeDotProduct(*this, *this)); }

  // Dot product operator.
  int operator*(const Vec2 &other) const
  {
    return ComputeDotProduct(*this, other);
  }

  // Scalar multiplication operator.
  Vec2 operator*(int multiplier) const
  {
    return Vec2(multiplier * x_, multiplier * y_);
  }

  // Addition operator.
  Vec2 operator+(const Vec2 &other) const
  {
    return Vec2(x_ + other.x_, y_ + other.y_);
  }

  // Subtraction operator.
  Vec2 operator-(const Vec2 &other) const
  {
    return Vec2(x_ - other.x_, y_ - other.y_);
  }

  // Outputs the vector in a readable format.
  friend std::ostream &operator<<(std::ostream &stream, const Vec2 &vec)
  {
    return stream << "<vector x:" << vec.x_ << " y:" << vec.y_ << ">";
  }

  // Copy constructor.
  Vec2(const Vec2 &other) : x_(other.x_), y_(other.y_) {}

  // Move constructor.
  Vec2(Vec2 &&other) : x_(other.x_), y_(other.y_)
  {
    other.x_ = 0;
    other.y_ = 0;
  }

private:
  // Computes the dot product of two vectors.
  int ComputeDotProduct(const Vec2 &v, const Vec2 &o) const
  {
    return v.x_ * o.x_ + v.y_ * o.y_;
  }

  // Private data members.
  int x_;
  int y_;
};

int main()
{
  std::vector<std::string> v = {"foo", "bar", "baz"};

  std::string s = absl::StrJoin(v, "-");

  std::cout << "Joined string: " << s << "\n";

  Vec2 myVec{1, 5};
  std::cout << myVec << std::endl;

  return 0;
}