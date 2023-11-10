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
  void load(Identifier id, const std::string& filename) {
    auto resource = std::make_unique<Resource>();
    if (!resource->loadFromFile(filename))
      throw std::runtime_error("ResourceHolder::load - Failed to load " +
                               filename);
    auto inserted =
        resource_map_.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
  }

  // load method for sf::Shader.
  template <typename Parameter>
  void load(Identifier id, const std::string& filename,
            const Parameter& second_param) {
    auto resource = std::make_unique<Resource>();
    if (!resource->loadFromFile(filename, second_param))
      throw std::runtime_error("ResourceHolder::load - Failed to load " +
                               filename);
    auto inserted =
        resource_map_.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
  }

  Resource& get(Identifier id) {
    auto found = resource_map_.find(id);
    assert(found != resource_map_.end());
    return *found->second;
  }

  const Resource& get(Identifier id) const {
    auto found = resource_map_.find(id);
    assert(found != resource_map_.end());
    return *found->second;
  }

 private:
  std::map<Identifier, std::unique_ptr<Resource>> resource_map_;
};

}  // namespace ink
