#include <Components/Graphics/AssetGraphics.hpp>

#include <Components/Combat/CombatComponent.hpp>

namespace ink::component {

namespace {

struct AttackInfoCommand final {
  void operator()(component::CombatComponent& unit_combat,
                  sf::Time /*dt*/) const {
    unit_combat.attack_started = true;
  }
};

}  // namespace

AssetGraphics::AssetGraphics(const TextureHolder& textures,
                             const sf::Vector2u sizes, bool is_centered)
    : current_animation_(AnimationState::kIdle) {
  attack_info_.category = ComponentCategory::kCombat;

  const auto kSpriteChangeInterval = sf::seconds(0.1f);
  animations_.emplace(
      std::piecewise_construct, std::forward_as_tuple(AnimationState::kIdle),
      std::forward_as_tuple(textures.get(Textures::kPlayerIdle), sizes,
                            is_centered, kSpriteChangeInterval));

  animations_.emplace(
      std::piecewise_construct, std::forward_as_tuple(AnimationState::kMoving),
      std::forward_as_tuple(textures.get(Textures::kPlayerRun), sizes,
                            is_centered, kSpriteChangeInterval));

  // Attacking scale is greater than other due to bad asset sizes
  static constexpr auto kAttackAnimationScale = 1.2f;
  animations_.emplace(
      std::piecewise_construct,
      std::forward_as_tuple(AnimationState::kAttacking),
      std::forward_as_tuple(
          textures.get(Textures::kPlayerSwordAttack), sizes, is_centered,
          kSpriteChangeInterval,
          sf::Vector2f{kAttackAnimationScale, kAttackAnimationScale}));
}

void AssetGraphics::draw(sf::RenderTarget& target,
                         const sf::RenderStates states) const {
  target.draw(animations_.at(current_animation_).getCurrentSprite(), states);
}

void AssetGraphics::updateCurrent(sf::Time dt) {
  switch (getObjectState()) {
    case ObjectState::kMoving:
      current_animation_ = AnimationState::kMoving;
      break;
    case ObjectState::kIdle:
      current_animation_ = AnimationState::kIdle;
      break;
    case ObjectState::kAttacking:
      current_animation_ = AnimationState::kAttacking;
      if (state_changed_) {
        auto& animation = animations_.at(current_animation_);
        animation.start(freezing_time_ + dt);

        attack_info_.action = SendTo<CombatComponent>(AttackInfoCommand{});
        auto full_duration = animation.getAnimationDuration();
        static constexpr auto kAttackDelayAfterAnimationStarts = 0.4f;
        attack_info_.delay = full_duration * kAttackDelayAfterAnimationStarts;

        sendCommand(attack_info_);
      }
      break;
    default:
      break;
  }

  state_changed_ = false;

  auto& animation = animations_.at(current_animation_);
  animation.flipTo(eyes_direction);
  animation.update(dt);
}

sf::FloatRect AssetGraphics::getGlobalBounds() const {
  return animations_.at(AnimationState::kIdle)
      .getCurrentSprite()
      .getGlobalBounds();
}

}  // namespace ink::component
