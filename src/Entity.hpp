#pragma once

#include "SceneNode.hpp"

class Entity : public SceneNode {
 public:
  Entity() = default;
  virtual ~Entity() = default;

  void setVelocity(sf::Vector2f velocity);
  void setVelocityX(float vx);
  void setVelocityY(float vy);
  sf::Vector2f getVelocity() const;

 private:
  virtual void updateCurrent(sf::Time dt);
  sf::Vector2f updatedVelocity() const;

  sf::Vector2f velocity_{0, 0};
};