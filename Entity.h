#pragma once

#include "SceneNode.h"

class Entity : public SceneNode {
public:
	Entity() = default;
	virtual ~Entity() = default;

	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;

private:
	virtual void updateCurrent(sf::Time dt);

	sf::Vector2f mVelocity;
};