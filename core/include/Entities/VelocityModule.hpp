#pragma once

#include <SFML/System/Vector2.hpp>

namespace ink {

struct VelocityModule final {
  sf::Vector2f toVector() const {
    return sf::Vector2f{to_left_ + to_right_, to_down_ + to_up_};
  }

  float to_left_{0};
  float to_right_{0};
  float to_up_{0};
  float to_down_{0};
};

}  // namespace ink
