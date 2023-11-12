#pragma once

#include <Commands/Command.hpp>
#include <Commands/CommandQueue.hpp>
#include <Entities/GameObject.hpp>
#include <Entities/Types/UnitContext.hpp>
#include <Resource/ResourceIdentifiers.hpp>

namespace ink {

class Unit final : public GameObject {
 public:
  Unit(ComponentManager manager, const FontHolder& fonts, NodeCategory category,
       Owner owner);

  void handleInput(CommandQueue<NodeCommand>& commands,
                   const sf::Keyboard::Key key, const bool is_pressed);
  Owner GetOwnerType() const noexcept;

  void selfDamage(int value);
  void selfHeal(int value);
  void enableDoorInteraction(bool interact_with) noexcept;

 private:
  void handleRealtimeInput(sf::Time dt, CommandQueue<NodeCommand>& commands);
  void drawCurrent(sf::RenderTarget& target,
                   const sf::RenderStates states) const override;
  void updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands) override;

 private:
  const FontHolder& fonts_;
  NodeCommand fire_command_;
  NodeCommand door_interaction_command_;
  CommandQueue<ComponentCommand> command_queue_;
  Owner owner_;
  bool interacted_with_door_;
};

}  // namespace ink
