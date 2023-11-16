#pragma once

#include <unordered_map>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <Commands/Command.hpp>
#include <Components/Graphics/Animation.hpp>
#include <Components/Graphics/GraphicsComponent.hpp>
#include <Resource/ResourceHolder.hpp>
#include <Resource/ResourceIdentifiers.hpp>

namespace ink::component {

class AssetGraphics final : public GraphicsComponent {
 public:
  AssetGraphics(const TextureHolder& textures, const sf::Vector2u sizes,
                bool is_centered);

  void draw(sf::RenderTarget& target,
            const sf::RenderStates states) const override;

  sf::FloatRect getGlobalBounds() const override;

 private:
  void updateCurrent(sf::Time dt) override;

 private:
  // perhaps it can be replaced with ObjectState
  enum class AnimationState {
    kNone,
    kIdle,
    kMoving,
    kAttacking,
  };

  // TODO: change to std::array or AnimationHolder class
  std::unordered_map<AnimationState, Animation> animations_;
  AnimationState current_animation_;
  ComponentCommand attack_info_;
};

}  // namespace ink::component
