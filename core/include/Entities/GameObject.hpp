#pragma once

#include <memory>
#include <type_traits>

#include <SFML/System/Vector2.hpp>

#include <Commands/Category/NodeCategory.hpp>
#include <SceneNode.hpp>

#include <Components/CombatComponent.hpp>
#include <Components/GraphicsComponent.hpp>
#include <Components/InputComponent.hpp>
#include <Components/PhysicsComponent.hpp>

namespace ink {

class GameObject : public SceneNode {
 public:
  using SceneNode::SceneNode;
  GameObject(std::unique_ptr<component::PhysicsComponent> physics,
             std::unique_ptr<component::GraphicsComponent> graphics,
             std::unique_ptr<component::InputComponent> inputs,
             std::unique_ptr<component::CombatComponent> combat,
             NodeCategory category = NodeCategory::kNone);

  virtual ~GameObject() = default;

  sf::FloatRect getBoundingRect() const override;

 protected:
  std::unique_ptr<component::PhysicsComponent> physics_impl_;
  std::unique_ptr<component::GraphicsComponent> graphics_impl_;
  std::unique_ptr<component::InputComponent> inputs_impl_;
  std::unique_ptr<component::CombatComponent> combat_impl_;

 private:
  void drawCurrent(sf::RenderTarget& target,
                   const sf::RenderStates states) const override;

  void updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands) override;
};

}  // namespace ink
