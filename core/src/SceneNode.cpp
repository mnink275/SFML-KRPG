#include <SceneNode.hpp>

#include <algorithm>

namespace ink {

SceneNode::SceneNode(Category category)
    : children_(), parent_(nullptr), category_(category) {}

void SceneNode::attachChild(Ptr child) {
  child->parent_ = this;
  children_.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node) {
  const auto found =
      std::find_if(children_.begin(), children_.end(),
                   [&](const Ptr& p) -> bool { return p.get() == &node; });
  assert(found != children_.end());
  Ptr result = std::move(*found);
  result->parent_ = nullptr;
  children_.erase(found);
  return result;
}

void SceneNode::update(const sf::Time dt, CommandQueue<Command>& commands) {
  updateCurrent(dt, commands);
  updateChildren(dt, commands);
}

void SceneNode::onCommand(const Command& command, sf::Time dt) {
  if (command.category & static_cast<CategoryType>(category_))
    command.action(*this, dt);

  for (auto&& child : children_) {
    child->onCommand(command, dt);
  }
}

void SceneNode::draw(sf::RenderTarget& target,
                     const sf::RenderStates& states) const {
  sf::RenderStates node_states(states);
  node_states.transform *= getTransform();
  drawCurrent(target, node_states);
  for (const Ptr& child : children_) {
    child->draw(target, node_states);
  }
}

void SceneNode::drawCurrent(sf::RenderTarget& /*target*/,
                            const sf::RenderStates /*states*/) const {}

void SceneNode::updateCurrent(sf::Time, CommandQueue<Command>&) {}

void SceneNode::updateChildren(const sf::Time dt,
                               CommandQueue<Command>& commands) const {
  for (auto&& child : children_) {
    child->update(dt, commands);
  }
}

sf::Transform SceneNode::getWorldTransform() const {
  sf::Transform transform = sf::Transform::Identity;
  for (auto node = this; node != nullptr; node = node->parent_) {
    transform = node->getTransform() * transform;
  }

  return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const {
  return getWorldTransform() * sf::Vector2f();
}

}  // namespace ink
