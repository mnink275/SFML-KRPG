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
                     const sf::Vector2f scale)
    : timer_(sf::Time::Zero),
      sprite_change_interval(sprite_change_interval),
      animation_(),
      curr_sprite_(0),
      scale_(scale),
      eyes_direction_(EyesDirection::kRight) {
  ASSERT(texture.getSize().y == sizes.y);
  ASSERT(texture.getSize().x % sizes.x == 0);

  auto sprites_amount = texture.getSize().x / sizes.x;
  // TODO: tmp rect shifts due to bad asset sizes
  const int shift = 14;
  sf::Vector2i pos_shift{shift, shift};
  sf::Vector2i sizes_shift{2 * shift, 2 * shift};

  sf::IntRect rect{pos_shift, sf::Vector2i{sizes} - sizes_shift};
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

sf::Time Animation::getAnimationDuration() const noexcept {
  return static_cast<float>(animation_.size()) * sprite_change_interval;
}

void Animation::update(sf::Time dt) {
  timer_ += dt;
  if (timer_ >= sprite_change_interval) {
    timer_ -= sprite_change_interval;
    curr_sprite_++;
    if (curr_sprite_ == animation_.size()) curr_sprite_ = 0;
  }
}

std::size_t Animation::getCurrentSpriteIndex() const noexcept {
  return curr_sprite_;
}

void Animation::start(sf::Time duration) noexcept {
  curr_sprite_ = 0;
  sprite_change_interval = duration / static_cast<float>(animation_.size() - 1);
}

void Animation::flipTo(EyesDirection direction) {
  if (eyes_direction_ == direction) return;

  eyes_direction_ = direction;
  flipVertically();
}

void Animation::flipVertically() {
  const auto sign = eyes_direction_ == EyesDirection::kLeft ? -1 : +1;
  auto scale = scale_;
  scale.x *= sign;
  std::for_each(animation_.begin(), animation_.end(),
                [scale](sf::Sprite& sprite) { sprite.setScale(scale); });
}

}  // namespace ink
