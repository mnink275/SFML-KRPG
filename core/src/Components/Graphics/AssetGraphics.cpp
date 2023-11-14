#include <Components/Graphics/AssetGraphics.hpp>

#include <Components/Combat/CombatComponent.hpp>

namespace ink::component {

namespace {

struct AttackInfoCommand final {
  AttackInfoCommand(sf::Time delay, sf::Time duration)
      : delay(delay), duration(duration) {}

  void operator()(component::CombatComponent& unit_combat, sf::Time) const {
    unit_combat.attack_started = true;
  }

  sf::Time delay;
  sf::Time duration;
};
}  // namespace

AssetGraphics::AssetGraphics(const TextureHolder& textures,
                             const sf::Vector2u sizes, bool is_centered)
    : GraphicsComponent(),
      animations_(),
      current_animation_(AnimationState::kIdle),
      prev_animation_(AnimationState::kNone) {
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
  animations_.emplace(
      std::piecewise_construct,
      std::forward_as_tuple(AnimationState::kAttacking),
      std::forward_as_tuple(textures.get(Textures::kPlayerSwordAttack), sizes,
                            is_centered, kSpriteChangeInterval,
                            sf::Vector2f{1.2f, 1.2f}));
}

void AssetGraphics::draw(sf::RenderTarget& target,
                         const sf::RenderStates states) const {
  target.draw(animations_.at(current_animation_).getCurrentSprite(), states);
}

void AssetGraphics::updateCurrent(sf::Time dt) {
  auto curr_state = getObjectState();

  switch (curr_state) {
    case ObjectState::kMoving:
      current_animation_ = AnimationState::kMoving;
      break;
    case ObjectState::kIdle:
      current_animation_ = AnimationState::kIdle;
      break;
    case ObjectState::kAttacking:
      current_animation_ = AnimationState::kAttacking;
      if (prev_animation_ != current_animation_) {
        animations_.at(current_animation_).start(freezing_time_ + dt);
      }
      if (animations_.at(current_animation_).getCurrentSpriteIndex() == 0) {
        attack_info_.action = SendTo<CombatComponent>(
            AttackInfoCommand{sf::Time::Zero, sf::Time::Zero});
        sendCommand(attack_info_);
      }
      break;
    default:
      break;
  }

  prev_animation_ = current_animation_;

  animations_.at(current_animation_).flitTo(eyes_direction);
  animations_.at(current_animation_).update(dt);
}

sf::FloatRect AssetGraphics::getGlobalBounds() const {
  return animations_.at(AnimationState::kIdle)
      .getCurrentSprite()
      .getGlobalBounds();
}

}  // namespace ink::component
