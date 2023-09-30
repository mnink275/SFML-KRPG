#pragma once

#include "SceneNode.hpp"

namespace ink {

class Entity : public SceneNode {
 public:
  Entity() = default;
  virtual ~Entity() = default;

  void setVelocity(sf::Vector2f velocity);
  void setVelocityX(float vx);
  void setVelocityY(float vy);
  sf::Vector2f getVelocity() const;

 private:
  void updateCurrent(sf::Time dt) override;
  sf::Vector2f updatedVelocity() const;

  sf::Vector2f velocity_{0, 0};
};

}  // namespace ink
