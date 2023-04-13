#pragma once

#include <map>
#include <memory>
#include <cassert>
#include <SFML/Graphics.hpp>

template <typename Resource, typename Identifier>
class ResourceHolder {
public:
	// Basic load method.
	void load(Identifier id, const std::string& filename);
	
	// load method for sf::Shader.
	template <typename Parameter>
	void load(Identifier id, const std::string& filename,
		const Parameter& secondParam);

	// get methods.
	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;

private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

// Methods implementation.
#include "ResourceHolder.inl"