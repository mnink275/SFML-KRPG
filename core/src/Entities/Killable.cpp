#include <Entities/Killable.hpp>

namespace ink {

bool Killable::HitBox::IsHitted(sf::Vector2f point) const noexcept {
  return point.x >= position.x && point.x <= position.x + size.x &&
         point.y <= position.y + size.y && point.y >= position.y;
}

Killable::Killable() = default;

Killable::~Killable() = default;

void Killable::DoHeal(std::int32_t value) noexcept { health_ += value; }

void Killable::DoDamage(std::int32_t value) noexcept { health_ -= value; }

void Killable::SetHitbox(HitBox new_hitbox) noexcept {
  hitbox_ = std::move(new_hitbox);
}

}  // namespace ink
