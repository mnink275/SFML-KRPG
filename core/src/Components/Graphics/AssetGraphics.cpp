#include <Components/Graphics/AssetGraphics.hpp>

namespace ink::component {

AssetGraphics::AssetGraphics(const sf::Texture& texture,
                             const sf::Vector2u& sizes, bool is_centered)
    : GraphicsComponent(EyesDirection::kLeft),
      is_idle(true),
      timer_(sf::Time::Zero),
      kSpriteChangeInterval(sf::seconds(0.1f)),
      animation_(),
      curr_sprite_(0) {
  // TODO: move logic to Animation class
  assert(texture.getSize().y == sizes.y);
  assert(texture.getSize().x % sizes.x == 0);

  auto sprites_amount = texture.getSize().x / sizes.x;
  sf::IntRect rect{{0, 0}, sf::Vector2i{sizes}};
  for (std::size_t i = 0; i < sprites_amount; ++i) {
    animation_.emplace_back(texture, rect);
    rect.left += sizes.x;
  }

  if (is_centered) {
    std::for_each(animation_.begin(), animation_.end(),
                  [this](sf::Sprite& sprite) { doSpriteCentering(sprite); });
  }
}

void AssetGraphics::draw(sf::RenderTarget& target,
                         const sf::RenderStates states) const {
  if (is_idle) {
    target.draw(animation_[curr_sprite_], states);
  }
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
  timer_ += dt;
  if (timer_ >= kSpriteChangeInterval) {
    timer_ -= kSpriteChangeInterval;
    curr_sprite_++;
    if (curr_sprite_ == animation_.size()) curr_sprite_ = 0;
  }
}

sf::FloatRect AssetGraphics::getGlobalBounds() const {
  return animation_.back().getGlobalBounds();
}

}  // namespace ink::component
