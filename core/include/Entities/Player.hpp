#pragma once

#include <Entities/GameObject.hpp>
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
         std::unique_ptr<component::InputComponent> inputs,
         std::unique_ptr<component::CombatComponent> combat,
         const TextureHolder& texture_holder)
      : GameObject(std::move(physics), std::move(graphics), std::move(inputs),
                   std::move(combat)),
        texture_holder_(texture_holder) {}

  ~Player() override = default;

  void handlePlayerInput(const sf::Keyboard::Key key, const bool is_pressed);

 private:
  const TextureHolder& texture_holder_;  // TODO: remove candidate
};

}  // namespace ink
