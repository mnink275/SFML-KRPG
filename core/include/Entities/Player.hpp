#pragma once

#include <Category.hpp>
#include <Commands/Command.hpp>
#include <Commands/CommandQueue.hpp>
#include <Commands/ComponentCommand.hpp>
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
         const TextureHolder& texture_holder, Category category);

  ~Player() override = default;

  void handlePlayerInput(CommandQueue<Command>& commands,
                         const sf::Keyboard::Key key, const bool is_pressed);
  void updateCurrent(sf::Time dt, CommandQueue<Command>& commands) override;

 private:
  const TextureHolder& texture_holder_;  // TODO: remove candidate
  Command fire_command_;
  CommandQueue<ComponentCommand> command_queue_;
};

}  // namespace ink
