#pragma once

#include <cstdint>

#include <SFML/System/Vector2.hpp>

#include <Entities/Entity.hpp>

namespace ink {

class Killable : public Entity {
 private:
  struct HitBox {
    bool IsHitted(sf::Vector2f point) const noexcept;

    sf::Vector2f position;
    sf::Vector2f size;
  };

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
