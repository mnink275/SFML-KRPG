#pragma once

#include <memory>

#include <SFML/System/Vector2.hpp>

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

  void drawCurrent(sf::RenderTarget& target,
                   const sf::RenderStates states) const override;

  void updateCurrent(sf::Time dt) override;

  virtual ~GameObject() = default;

 protected:
  std::unique_ptr<component::PhysicsComponent> physics_impl_;
  std::unique_ptr<component::GraphicsComponent> graphics_impl_;
  std::unique_ptr<component::InputComponent> inputs_impl_;
  VelocityModule velocity_{};
};

}  // namespace ink
