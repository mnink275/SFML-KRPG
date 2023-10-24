#pragma once

#include <Entities/Killable.hpp>
#include <Entities/PlayerContext.hpp>
#include <Resource/ResourceHolder.hpp>
#include <Resource/ResourceIdentifiers.hpp>
#include <Room/Node.hpp>

namespace ink {

class Player final : public Entity, public Killable {
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

  void setPlayerVelocity(float velocity, Direction direction) noexcept;
  void setParentRoom(room::RoomNode* parent) noexcept;

  void OnAttack();

 private:
  void updatePlayerVelocity() noexcept;
  Textures::ID toTextureID(const Player::Type type) const;

 private:
  Type type_;
  const TextureHolder& texture_holder_;
  room::RoomNode* parent_{nullptr};

  float to_left_vel_{0};
  float to_right_vel_{0};
  float to_up_vel_{0};
  float to_down_vel_{0};
};

}  // namespace ink
