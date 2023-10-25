#pragma once

#include <memory>

#include <SFML/System/Vector2.hpp>

#include <Components/GraphicsComponent.hpp>
#include <SceneNode.hpp>

namespace ink {

class GameStaticObject : public SceneNode {
 public:
  using SceneNode::SceneNode;
  GameStaticObject(std::unique_ptr<component::GraphicsComponent> graphics);

  virtual ~GameStaticObject() = default;

 protected:
  std::unique_ptr<component::GraphicsComponent> graphics_impl_;

 private:
  void drawCurrent(sf::RenderTarget& target,
                   const sf::RenderStates states) const override;
};

}  // namespace ink
