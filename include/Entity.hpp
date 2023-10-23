#pragma once

#include "SceneNode.hpp"

namespace ink {

class Entity : public SceneNode {
 public:
  Entity() = default;

  virtual ~Entity() = default;

  sf::Vector2f getVelocity() const;

 protected:
  void setVelocity(sf::Vector2f velocity) noexcept;
  void setVelocityX(float vx) noexcept;
  void setVelocityY(float vy) noexcept;
  
 private:
  void updateCurrent(sf::Time dt) override;
  sf::Vector2f updatedVelocity() const;

  sf::Vector2f velocity_{0, 0};
};

}  // namespace ink
