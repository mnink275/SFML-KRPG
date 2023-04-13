#include "ResourceHolder.h"

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id,
	const std::string& filename) {
	auto resource = std::make_unique<Resource>();
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("TextureHolder::load - Failed to load "
			+ filename);
	auto inserted = mResourceMap.insert(
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
	auto inserted = mResourceMap.insert(
		std::make_pair(id, std::move(resource))
	);
	assert(inserted.second);
}


template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());
	return *found->second;
}


template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(
	Identifier id) const
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());
	return *found->second;
}