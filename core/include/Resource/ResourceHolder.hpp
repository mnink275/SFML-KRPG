#pragma once

#include <cassert>
#include <map>
#include <memory>

#include <SFML/Graphics.hpp>

namespace ink {

template <typename Resource, typename Identifier>
class ResourceHolder {
 public:
  // Basic load method.
  void load(Identifier id, const std::string& filename);

  // load method for sf::Shader.
  template <typename Parameter>
  void load(Identifier id, const std::string& filename,
            const Parameter& second_param);

  // get methods.
  Resource& get(Identifier id);
  const Resource& get(Identifier id) const;

 private:
  std::map<Identifier, std::unique_ptr<Resource>> resource_map_;
};

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id,
	const std::string& filename) {
	auto resource = std::make_unique<Resource>();
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("TextureHolder::load - Failed to load "
			+ filename);
	auto inserted = resource_map_.insert(
		std::make_pair(id, std::move(resource))
	);
	assert(inserted.second);
}


template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id,
	const std::string& filename, const Parameter& secondParam) {
	auto resource = std::make_unique<Resource>();
	if (!resource->loadFromFile(filename, secondParam))
		throw std::runtime_error("TextureHolder::load - Failed to load "
			+ filename);
	auto inserted = resource_map_.insert(
		std::make_pair(id, std::move(resource))
	);
	assert(inserted.second);
}


template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = resource_map_.find(id);
	assert(found != resource_map_.end());
	return *found->second;
}


template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(
	Identifier id) const
{
	auto found = resource_map_.find(id);
	assert(found != resource_map_.end());
	return *found->second;
}

}  // namespace ink
