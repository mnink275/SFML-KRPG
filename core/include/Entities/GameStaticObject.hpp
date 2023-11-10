#pragma once

#include <memory>

#include <SFML/System/Vector2.hpp>

#include <Components/Graphics/GraphicsComponent.hpp>
#include <SceneNode.hpp>

namespace ink {

class GameStaticObject : public SceneNode {
 public:
  using SceneNode::SceneNode;
  GameStaticObject(std::unique_ptr<component::GraphicsComponent> graphics,
                   NodeCategory category = NodeCategory::kNone);

  virtual ~GameStaticObject() = default;

  sf::FloatRect getBoundingRect() const override;

 protected:
  std::unique_ptr<component::GraphicsComponent> graphics_impl_;

 private:
  void drawCurrent(sf::RenderTarget& target,
                   const sf::RenderStates states) const override;
};

}  // namespace ink
