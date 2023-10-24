#pragma once

#include <Entities/GameObject.hpp>
#include <Entities/PlayerContext.hpp>
#include <Resource/ResourceIdentifiers.hpp>
#include <Room/Node.hpp>

namespace ink {

class Player final : public GameObject {
 public:
  enum Type {
    Peepo,
  };

 public:
  using GameObject::GameObject;
  Player(std::unique_ptr<component::PhysicsComponent> physics,
         std::unique_ptr<component::GraphicsComponent> graphics,
         const TextureHolder& texture_holder)
      : GameObject(std::move(physics), std::move(graphics)),
        texture_holder_(texture_holder) {}

  ~Player() override = default;

  void setPlayerVelocity(float velocity, Direction direction) noexcept;
  void setParentRoom(room::RoomNode* parent) noexcept;

  void OnAttack();

 private:
  void updatePlayerVelocity() noexcept;

 private:
  const TextureHolder& texture_holder_;
  room::RoomNode* parent_{nullptr};

  float to_left_vel_{0};
  float to_right_vel_{0};
  float to_up_vel_{0};
  float to_down_vel_{0};
};

}  // namespace ink
