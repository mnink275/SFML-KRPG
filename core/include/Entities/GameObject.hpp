#pragma once

#include <memory>
#include <type_traits>

#include <SFML/System/Vector2.hpp>

#include <Components/ComponentManager.hpp>
#include <SceneNode.hpp>

namespace ink {

class GameObject : public SceneNode {
 public:
  explicit GameObject(ComponentManager manager,
                      NodeCategory category = NodeCategory::kNone);

  void handleCollisionWith(NodeCategory category, const SceneNode* node) final;
  sf::FloatRect getBoundingRect() const override;

 protected:
  ComponentManager manager_;

 private:
  void drawCurrent(sf::RenderTarget& target,
                   const sf::RenderStates states) const override;
};

}  // namespace ink
