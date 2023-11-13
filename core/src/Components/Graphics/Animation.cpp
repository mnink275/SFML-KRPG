#include <Components/Graphics/Animation.hpp>

#include <algorithm>

#include <Components/Graphics/Utils.hpp>
#include <Utils/Assert.hpp>

namespace ink {

Animation::Animation(const sf::Texture& texture, const sf::Vector2u sizes,
                     bool is_centered, const sf::Time sprite_change_interval)
    : Animation(texture, sizes, is_centered, sprite_change_interval,
                sf::Vector2f{1.0f, 1.0f}) {}

Animation::Animation(const sf::Texture& texture, const sf::Vector2u sizes,
                     bool is_centered, const sf::Time sprite_change_interval,
                     sf::Vector2f scale)
    : timer_(sf::Time::Zero),
      kSpriteChangeInterval(sprite_change_interval),
      animation_(),
      curr_sprite_(0) {
  ASSERT(texture.getSize().y == sizes.y);
  ASSERT(texture.getSize().x % sizes.x == 0);

  auto sprites_amount = texture.getSize().x / sizes.x;
  sf::IntRect rect{{0, 0}, sf::Vector2i{sizes}};
  for (std::size_t i = 0; i < sprites_amount; ++i) {
    animation_.emplace_back(texture, rect);
    rect.left += sizes.x;
  }

  std::for_each(animation_.begin(), animation_.end(),
                [is_centered, scale](sf::Sprite& sprite) {
                  sprite.setScale(scale);
                  if (is_centered) utils::doSpriteCentering(sprite);
                });
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

void Animation::start() noexcept { curr_sprite_ = 0; }

}  // namespace ink
