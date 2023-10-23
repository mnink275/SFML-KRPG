#pragma once

#include <cstdint>

#include <SFML/System/Vector2.hpp>
#include "SFML/Graphics/Rect.hpp"

#include <Entities/Entity.hpp>

namespace ink {

class HitBox {
 public:
  HitBox(sf::FloatRect float_rect);

  bool IsHitted(sf::Vector2f point) const noexcept;

 private:
  sf::Vector2f position;
  sf::Vector2f size;
};

class Killable {
 public:
  Killable(std::int32_t init_health, HitBox hitbox);

  virtual ~Killable();

  Killable(const Killable&) = delete;
  Killable& operator=(const Killable&) = delete;

  Killable(Killable&&) noexcept = default;
  Killable& operator=(Killable&&) noexcept = default;

  void DoHeal(std::int32_t value) noexcept;
  void DoDamage(std::int32_t value) noexcept;

  void SetHitbox(HitBox hitbox) noexcept;

 private:
  std::int32_t health_;
  HitBox hitbox_;
};

}  // namespace ink
