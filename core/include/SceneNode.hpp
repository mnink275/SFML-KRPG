#pragma once

#include <memory>
#include <set>

#include <SFML/Graphics.hpp>

#include <Commands/Command.hpp>
#include <Commands/CommandQueue.hpp>

namespace ink {

class SceneNode : public sf::Transformable, public sf::Drawable {
 public:
  using Ptr = std::unique_ptr<SceneNode>;
  using NodePair = std::pair<SceneNode*, SceneNode*>;

  SceneNode(NodeCategory category = NodeCategory::kNone);
  virtual ~SceneNode() = default;

  SceneNode(const SceneNode&) = delete;
  SceneNode& operator=(const SceneNode&) = delete;

  SceneNode(SceneNode&&) noexcept = default;
  SceneNode& operator=(SceneNode&&) noexcept = default;

  void attachChild(Ptr child);
  Ptr detachChild(const SceneNode& node);
  void update(const sf::Time dt, CommandQueue<NodeCommand>& commands);

  void onCommand(const NodeCommand& command, sf::Time dt);

  void checkSceneCollision(SceneNode& scene_root,
                           std::set<NodePair>& collisions);
  void checkNodeCollision(SceneNode& node, std::set<NodePair>& collisions);
  virtual void handleCollisionWith(NodeCategory category,
                                   const SceneNode* node);
  virtual sf::FloatRect getBoundingRect() const;

  sf::Transform getWorldTransform() const;
  NodeCategory getCategory() const noexcept;

  void cleanGarbage();
  void destroy() noexcept;
  bool isDestroyed() const noexcept;

 private:
  void draw(sf::RenderTarget& target,
            const sf::RenderStates& states) const override final;
  virtual void drawCurrent(sf::RenderTarget& target,
                           const sf::RenderStates states) const;
  virtual void updateCurrent(sf::Time dt, CommandQueue<NodeCommand>& commands);
  void updateChildren(sf::Time dt, CommandQueue<NodeCommand>& commands) const;
  sf::Vector2f getWorldPosition() const;
  bool isCollide(const SceneNode& lhs, const SceneNode& rhs) const;

  std::vector<Ptr> children_;
  SceneNode* parent_;
  NodeCategory category_;
  bool is_destroyed_;
};

}  // namespace ink
