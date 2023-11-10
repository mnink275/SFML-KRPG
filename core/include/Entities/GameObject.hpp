#pragma once

#include <memory>
#include <type_traits>

#include <SFML/System/Vector2.hpp>

#include <SceneNode.hpp>

#include <Components/ComponentManager.hpp>

namespace ink {

class GameObject : public SceneNode {
 public:
  using SceneNode::SceneNode;
  GameObject(std::unique_ptr<component::PhysicsComponent> physics,
             std::unique_ptr<component::GraphicsComponent> graphics,
             std::unique_ptr<component::InputComponent> inputs,
             std::unique_ptr<component::CombatComponent> combat,
             std::unique_ptr<component::CollisionComponent> collision,
             NodeCategory category);

  virtual ~GameObject() = default;

  sf::FloatRect getBoundingRect() const override;

 protected:
  ComponentManager manager_;

 private:
  void drawCurrent(sf::RenderTarget& target,
                   const sf::RenderStates states) const override;

  void updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands) override;
};

}  // namespace ink
