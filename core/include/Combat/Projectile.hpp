#pragma once

#include <Entities/Entity.hpp>

namespace ink::combat {

class Projectile : public Entity {
 public:
  Projectile(const sf::Texture& texture);
};

}  // namespace ink::combat
