#pragma once

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"


class Aircraft final : public Entity {
public:
	enum Type {
		Eagle,
		Raptor,
	};

	Aircraft(Type type, const TextureHolder& textures);
	void drawCurrent(sf::RenderTarget& target,
		sf::RenderStates states) const override;

private:
	Type mType;
	sf::Sprite mSprite;
};