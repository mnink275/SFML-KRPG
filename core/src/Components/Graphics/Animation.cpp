#include <Components/Graphics/Animation.hpp>

#include <algorithm>

#include <Components/Graphics/Utils.hpp>

namespace ink {

Animation::Animation(const sf::Texture& texture, const sf::Vector2u& sizes,
                     bool is_centered, const sf::Time sprite_change_interval)
    : timer_(sf::Time::Zero),
      kSpriteChangeInterval(sprite_change_interval),
      animation_(),
      curr_sprite_(0) {
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
                  [](sf::Sprite& sprite) { utils::doSpriteCentering(sprite); });
  }
}

const sf::Sprite& Animation::getCurrentSprite() const {
  return animation_[curr_sprite_];
}

void Animation::update(sf::Time dt) {
  timer_ += dt;
  if (timer_ >= kSpriteChangeInterval) {
    timer_ -= kSpriteChangeInterval;
    curr_sprite_++;
    if (curr_sprite_ == animation_.size()) curr_sprite_ = 0;
  }
}

}  // namespace ink
