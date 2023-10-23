#include <Entities/Killable.hpp>

namespace ink {

HitBox::HitBox(sf::FloatRect float_rect)
    : position({float_rect.left, float_rect.top}),
      size({float_rect.width, float_rect.height}) {}

bool HitBox::IsHitted(sf::Vector2f point) const noexcept {
  return point.x >= position.x && point.x <= position.x + size.x &&
         point.y <= position.y + size.y && point.y >= position.y;
}

Killable::Killable(std::int32_t init_health, HitBox hitbox)
    : health_(init_health), hitbox_(std::move(hitbox)) {}

Killable::~Killable() = default;

void Killable::DoHeal(std::int32_t value) noexcept { health_ += value; }

void Killable::DoDamage(std::int32_t value) noexcept { health_ -= value; }

void Killable::SetHitbox(HitBox new_hitbox) noexcept {
  hitbox_ = std::move(new_hitbox);
}

}  // namespace ink
