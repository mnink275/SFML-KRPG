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
  Unit(ComponentManager manager, const FontHolder& fonts, NodeCategory category,
       OwnerType owner);

  ~Unit() override = default;

  void handleInput(CommandQueue<NodeCommand>& commands,
                   const sf::Keyboard::Key key, const bool is_pressed);
  void updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands) override;
  OwnerType GetOwnerType() const noexcept;

  void selfDamage(int value);
  void selfHeal(int value);

 private:
  void handleRealtimeInput(sf::Time dt, CommandQueue<NodeCommand>& commands);
  void drawCurrent(sf::RenderTarget& target,
                   const sf::RenderStates states) const override;

 private:
  const FontHolder& fonts_;
  NodeCommand fire_command_;
  CommandQueue<ComponentCommand> command_queue_;
  OwnerType owner_;
};

}  // namespace ink
