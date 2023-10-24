#pragma once

#include <SFML/System/Vector2.hpp>

#include <Components/PhysicsComponent.hpp>

namespace ink::component {

class AntonPhysics: public PhysicsComponent {
 public:
  virtual ~AntonPhysics() = default;

  void update(sf::Time dt, sf::Vector2f& transform) override {
    elapsed_ += dt;
    if (elapsed_.asSeconds() > 1.0f) {
      velocity_.x *= -1; 
      elapsed_ -= sf::seconds(1.0f);
    }

    transform = velocity_ * dt.asSeconds();
  }

 private:
  sf::Time elapsed_{};
  sf::Vector2f velocity_{20, 0};
};

}  // namespace ink::component