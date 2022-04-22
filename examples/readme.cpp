#include <palimpsest/Dictionary.h>

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iostream>

int main() {
  using palimpsest::Dictionary;

  Dictionary world;
  world("name") = "example";
  world("temperature") = 28.0;

  auto& bodies = world("bodies");
  bodies("plane")("orientation") = Eigen::Quaterniond{0.9239, 0.3827, 0., 0.};
  bodies("plane")("position") = Eigen::Vector3d{0.0, 0.0, 100.0};
  bodies("truck")("orientation") = Eigen::Quaterniond::Identity();
  bodies("truck")("position") = Eigen::Vector3d{42.0, 0.0, 0.0};

  std::cout << "world = " << world << std::endl;
  return EXIT_SUCCESS;
}
