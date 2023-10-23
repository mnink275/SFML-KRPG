#pragma once

#include <Entities/Killable.hpp>
#include <Entities/PlayerContext.hpp>
#include <Resource/ResourceHolder.hpp>
#include <Resource/ResourceIdentifiers.hpp>

namespace ink {

class Player final : public Killable {
 public:
  enum Type {
    Peepo,
  };

 public:
  Player(Type type, const TextureHolder& textures);

  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;

  Player(Player&&) = delete;
  Player& operator=(Player&&) = delete;

  ~Player() = default;

  void drawCurrent(sf::RenderTarget& target,
                   sf::RenderStates states) const override;

  void setPlayerVelocity(float velocity, Direction direction) noexcept;

 private:
  void updatePlayerVelocity() noexcept;
  Textures::ID toTextureID(const Player::Type type) const;

 private:
  Type type_;
  sf::Sprite sprite_;

  float to_left_vel_{0};
  float to_right_vel_{0};
  float to_up_vel_{0};
  float to_down_vel_{0};
};

}  // namespace ink
