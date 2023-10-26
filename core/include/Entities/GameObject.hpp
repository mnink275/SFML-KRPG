#pragma once

#include <memory>
#include <type_traits>

#include <SFML/System/Vector2.hpp>

#include <Commands/Command.hpp>
#include <Commands/GraphicsCommand.hpp>
#include <Commands/PhysicsCommand.hpp>
#include <Components/GraphicsComponent.hpp>
#include <Components/InputComponent.hpp>
#include <Components/PhysicsComponent.hpp>
#include <Entities/VelocityModule.hpp>
#include <Resource/ResourceIdentifiers.hpp>
#include <SceneNode.hpp>

namespace ink {

class GameObject : public SceneNode {
 public:
  using SceneNode::SceneNode;
  GameObject(std::unique_ptr<component::PhysicsComponent> physics,
             std::unique_ptr<component::GraphicsComponent> graphics,
             std::unique_ptr<component::InputComponent> inputs);

  virtual ~GameObject() = default;

  template <class CommandType>
  void send(std::unique_ptr<Command> command) {
    if constexpr (std::is_base_of_v<PhysicsCommand, CommandType>) {
      static_cast<PhysicsCommand*>(command.get())->execute(physics_impl_.get());
    } else if (std::is_base_of_v<GraphicsCommand, CommandType>) {
      static_cast<GraphicsCommand*>(command.get())
          ->execute(graphics_impl_.get());
    }
  }

 protected:
  std::unique_ptr<component::PhysicsComponent> physics_impl_;
  std::unique_ptr<component::GraphicsComponent> graphics_impl_;
  std::unique_ptr<component::InputComponent> inputs_impl_;

 private:
  void drawCurrent(sf::RenderTarget& target,
                   const sf::RenderStates states) const override;

  void updateCurrent(sf::Time dt) override;
};

}  // namespace ink
