#pragma once

#include <SFML/Graphics.hpp>
#include <cassert>
#include <utility>

class SceneNode : public sf::Transformable,
                  public sf::Drawable,
                  private sf::NonCopyable {
 public:
  using Ptr = std::unique_ptr<SceneNode>;

  SceneNode() = default;
  virtual ~SceneNode() = default;

  void attachChild(Ptr child);
  Ptr detachChild(const SceneNode& node);
  void update(const sf::Time dt);

 private:
  void draw(sf::RenderTarget& target,
            sf::RenderStates states) const override final;
  virtual void drawCurrent(sf::RenderTarget& target,
                           const sf::RenderStates states) const;
  virtual void updateCurrent(sf::Time dt);
  void updateChildren(sf::Time dt) const;
  sf::Transform getWorldTransform() const;
  sf::Vector2f getWorldPosition() const;

  std::vector<Ptr> children_;
  SceneNode* parent_{nullptr};
};