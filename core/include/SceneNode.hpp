#pragma once

#include <cassert>
#include <memory>
#include <utility>

#include <SFML/Graphics.hpp>

namespace ink {

class SceneNode : public sf::Transformable, public sf::Drawable {
 public:
  using Ptr = std::unique_ptr<SceneNode>;

  SceneNode() = default;
  virtual ~SceneNode() = default;

  SceneNode(const SceneNode&) = delete;
  SceneNode& operator=(const SceneNode&) = delete;

  SceneNode(SceneNode&&) noexcept = default;
  SceneNode& operator=(SceneNode&&) noexcept = default;

  void attachChild(Ptr child);
  Ptr detachChild(const SceneNode& node);
  void update(const sf::Time dt);

 private:
  void draw(sf::RenderTarget& target,
            const sf::RenderStates& states) const override final;
  virtual void drawCurrent(sf::RenderTarget& target,
                           const sf::RenderStates states) const;
  virtual void updateCurrent(sf::Time dt);
  void updateChildren(sf::Time dt) const;
  sf::Transform getWorldTransform() const;
  sf::Vector2f getWorldPosition() const;

  std::vector<Ptr> children_;
  SceneNode* parent_{nullptr};
};

}  // namespace ink
