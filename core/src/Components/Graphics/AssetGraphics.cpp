#include <Components/Graphics/AssetGraphics.hpp>
#include <iostream>
namespace ink::component {

AssetGraphics::AssetGraphics(const TextureHolder& textures,
                             const sf::Vector2u sizes, bool is_centered)
    : GraphicsComponent(),
      animations_(),
      current_animation_(AnimationState::kIdleRight) {
  const auto kSpriteChangeInterval = sf::seconds(0.1f);
  animations_.emplace(
      std::piecewise_construct,
      std::forward_as_tuple(AnimationState::kIdleLeft),
      std::forward_as_tuple(textures.get(Textures::kPlayerIdle), sizes,
                            is_centered, kSpriteChangeInterval,
                            sf::Vector2f{-1.0f, 1.0f}));
  animations_.emplace(
      std::piecewise_construct,
      std::forward_as_tuple(AnimationState::kIdleRight),
      std::forward_as_tuple(textures.get(Textures::kPlayerIdle), sizes,
                            is_centered, kSpriteChangeInterval));
  animations_.emplace(
      std::piecewise_construct,
      std::forward_as_tuple(AnimationState::kMovingLeft),
      std::forward_as_tuple(textures.get(Textures::kPlayerRun), sizes,
                            is_centered, kSpriteChangeInterval,
                            sf::Vector2f{-1.0f, 1.0f}));
  animations_.emplace(
      std::piecewise_construct,
      std::forward_as_tuple(AnimationState::kMovingRight),
      std::forward_as_tuple(textures.get(Textures::kPlayerRun), sizes,
                            is_centered, kSpriteChangeInterval));
}

void AssetGraphics::draw(sf::RenderTarget& target,
                         const sf::RenderStates states) const {
  target.draw(animations_.at(current_animation_).getCurrentSprite(), states);
#if 0
    switch (eyes_direction) {
      case EyesDirection::kLeft:
        target.draw(animation_[curr_sprite_], states);
        break;
      case EyesDirection::kRight:
        target.draw(animation_[curr_sprite_], states);
        break;
      default:
        std::cout << "Warning in PlayerGraphics: eye direction is kNone\n";
        break;
    }
#endif
}

void AssetGraphics::update(sf::Time dt) {
  switch (object_state) {
    case ObjectState::kMoving:
      if (eyes_direction == EyesDirection::kLeft)
        current_animation_ = AnimationState::kMovingLeft;
      else
        current_animation_ = AnimationState::kMovingRight;
      break;
    case ObjectState::kIdle:
      if (eyes_direction == EyesDirection::kLeft)
        current_animation_ = AnimationState::kIdleLeft;
      else
        current_animation_ = AnimationState::kIdleRight;
      break;
    default:
      break;
  }

  animations_.at(current_animation_).update(dt);
}

sf::FloatRect AssetGraphics::getGlobalBounds() const {
  return animations_.at(current_animation_)
      .getCurrentSprite()
      .getGlobalBounds();
}

}  // namespace ink::component
