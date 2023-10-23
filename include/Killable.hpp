#pragma once

#include <cstdint>

#include <SFML/System/Vector2.hpp>

#include "Entity.hpp"

namespace ink {

struct HitBox {
  sf::Vector2f position;
  sf::Vector2f size;
};

class Killable : public Entity {
 public:
  Killable();

  virtual ~Killable();

  void DoHeal(std::int32_t value) noexcept;
  void DoDamage(std::int32_t value) noexcept;

  void SetHitbox(HitBox hitbox) noexcept;

 private:
  std::int32_t health_{0};
  HitBox hitbox_{};
};

}  // namespace ink