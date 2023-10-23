#include <Entities/Killable.hpp>

namespace ink {

Killable::Killable() = default;

Killable::~Killable() = default;

void Killable::DoHeal(std::int32_t value) noexcept {
  health_ += value;
}

void Killable::DoDamage(std::int32_t value) noexcept {
  health_ -= value;
}

void Killable::SetHitbox(HitBox new_hitbox) noexcept{
  hitbox_ = std::move(new_hitbox);
}

}  // namespace ink