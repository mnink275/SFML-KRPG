#pragma once

#include <memory>

#include <SceneNode.hpp>
#include <Components/PhysicsComponent.hpp>
#include <Components/GraphicsComponent.hpp>
#include <Resource/ResourceIdentifiers.hpp>
#include "SFML/System/Vector2.hpp"

namespace ink {

class GameObject : public SceneNode {
 public:
  using SceneNode::SceneNode;
  GameObject(std::unique_ptr<component::PhysicsComponent> physics,
             std::unique_ptr<component::GraphicsComponent> graphics)
      : physics_impl_(std::move(physics)), graphics_impl_(std::move(graphics)) {}

  void drawCurrent(sf::RenderTarget& target,
                           const sf::RenderStates states) const override {
    graphics_impl_->draw(target, states);
  }

  void updateCurrent(sf::Time dt) override {
    sf::Vector2f transforms;
    physics_impl_->update(dt, transforms);
    Transformable::move(transforms);
  };

  virtual ~GameObject() = default;

 private:
  std::unique_ptr<component::PhysicsComponent> physics_impl_;
  std::unique_ptr<component::GraphicsComponent> graphics_impl_;
};

}  // namespace ink
