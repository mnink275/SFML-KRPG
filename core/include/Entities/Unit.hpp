#pragma once

#include <Commands/Command.hpp>
#include <Commands/CommandQueue.hpp>
#include <Entities/GameObject.hpp>
#include <Resource/ResourceIdentifiers.hpp>
#include <Room/Node.hpp>

namespace ink {

class Unit final : public GameObject {
 public:
  enum class OwnerType {
    kPlayer,
    kEnemy,
    kAlly,
  };

 public:
  using GameObject::GameObject;
  Unit(std::unique_ptr<component::PhysicsComponent> physics,
       std::unique_ptr<component::GraphicsComponent> graphics,
       std::unique_ptr<component::InputComponent> inputs,
       std::unique_ptr<component::CombatComponent> combat,
       const TextureHolder& texture_holder, NodeCategory category);

  ~Unit() override = default;

  void handleInput(CommandQueue<NodeCommand>& commands,
                   const sf::Keyboard::Key key, const bool is_pressed);
  void handleRealtimeInput(CommandQueue<NodeCommand>& commands);
  void updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands) override;

 private:
  const TextureHolder& texture_holder_;  // TODO: remove candidate
  NodeCommand fire_command_;
  CommandQueue<ComponentCommand> command_queue_;
};

}  // namespace ink
