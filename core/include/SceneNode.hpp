#pragma once

#include <cassert>
#include <memory>

#include <SFML/Graphics.hpp>

#include <Commands/Command.hpp>
#include <Commands/CommandQueue.hpp>

namespace ink {

class SceneNode : public sf::Transformable, public sf::Drawable {
 public:
  using Ptr = std::unique_ptr<SceneNode>;

  SceneNode(NodeCategory category = NodeCategory::None);
  virtual ~SceneNode() = default;

  SceneNode(const SceneNode&) = delete;
  SceneNode& operator=(const SceneNode&) = delete;

  SceneNode(SceneNode&&) noexcept = default;
  SceneNode& operator=(SceneNode&&) noexcept = default;

  void attachChild(Ptr child);
  Ptr detachChild(const SceneNode& node);
  void update(const sf::Time dt, CommandQueue<NodeCommand>& commands);

  void onCommand(const NodeCommand& command, sf::Time dt);

 private:
  void draw(sf::RenderTarget& target,
            const sf::RenderStates& states) const override final;
  virtual void drawCurrent(sf::RenderTarget& target,
                           const sf::RenderStates states) const;
  virtual void updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands);
  void updateChildren(sf::Time dt, CommandQueue<NodeCommand>& commands) const;
  sf::Transform getWorldTransform() const;
  sf::Vector2f getWorldPosition() const;

  std::vector<Ptr> children_;
  SceneNode* parent_;
  NodeCategory category_;
};

}  // namespace ink
