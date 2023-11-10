#pragma once

#include <Commands/Command.hpp>
#include <Commands/CommandQueue.hpp>
#include <Entities/GameObject.hpp>
#include <Entities/UnitContext.hpp>
#include <Resource/ResourceIdentifiers.hpp>

namespace ink {

class Unit final : public GameObject {
 public:
  using GameObject::GameObject;
  Unit(ComponentManager manager, const TextureHolder& texture_holder,
       NodeCategory category, OwnerType owner);

  ~Unit() override = default;

  void handleInput(CommandQueue<NodeCommand>& commands,
                   const sf::Keyboard::Key key, const bool is_pressed);
  void updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands) override;
  OwnerType GetOwnerType() const noexcept;

 private:
  void handleRealtimeInput(sf::Time dt, CommandQueue<NodeCommand>& commands);

 private:
  const TextureHolder& texture_holder_;  // TODO: remove candidate
  NodeCommand fire_command_;
  CommandQueue<ComponentCommand> command_queue_;
  OwnerType owner_;
};

}  // namespace ink
