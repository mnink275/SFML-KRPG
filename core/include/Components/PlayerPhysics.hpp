#pragma once

#include <SFML/System/Vector2.hpp>

#include <Components/PhysicsComponent.hpp>

namespace ink::component {

class PlayerPhysics : public PhysicsComponent {
 public:
  virtual ~PlayerPhysics() = default;

  void update(sf::Time dt, sf::Vector2f& transform) override;

  sf::Vector2f getVelocity() const noexcept override;
  void setVelocity(sf::Vector2f velocity) noexcept override;

 private:
  sf::Vector2f updatedVelocity() const;

 private:
  sf::Vector2f velocity_{0.0f, 0.0f};
};

}  // namespace ink::component
