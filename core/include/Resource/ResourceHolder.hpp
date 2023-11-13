#pragma once

#include <map>
#include <memory>

#include <fmt/format.h>
#include <SFML/Graphics.hpp>

#include <Utils/Assert.hpp>

namespace ink {

template <typename Resource, typename Identifier>
class ResourceHolder final {
 public:
  void load(Identifier id, const std::string& filename) {
    auto resource = std::make_unique<Resource>();
    if (!resource->loadFromFile(filename))
      throw std::runtime_error("ResourceHolder::load - Failed to load " +
                               filename);
    auto inserted =
        resource_map_.insert(std::make_pair(id, std::move(resource)));
    ASSERT_MSG(inserted.second, fmt::format("Duplicate resource with id '{}'",
                                            static_cast<int>(id)));
  }

  // load for sf::Shader.
  template <typename Parameter>
  void load(Identifier id, const std::string& filename,
            const Parameter& second_param) {
    auto resource = std::make_unique<Resource>();
    if (!resource->loadFromFile(filename, second_param))
      throw std::runtime_error("ResourceHolder::load - Failed to load " +
                               filename);
    auto inserted =
        resource_map_.insert(std::make_pair(id, std::move(resource)));
    ASSERT_MSG(inserted.second, fmt::format("Duplicate resource with id '{}'",
                                            static_cast<int>(id)));
  }

  Resource& get(Identifier id) {
    auto found = resource_map_.find(id);
    ASSERT_MSG(found != resource_map_.end(),
               fmt::format("Resource with id '{}' doesn't exist",
                           static_cast<int>(id)));
    return *found->second;
  }

  const Resource& get(Identifier id) const {
    auto found = resource_map_.find(id);
    ASSERT_MSG(found != resource_map_.end(),
               fmt::format("Resource with id '{}' doesn't exist",
                           static_cast<int>(id)));
    return *found->second;
  }

 private:
  std::map<Identifier, std::unique_ptr<Resource>> resource_map_;
};

}  // namespace ink
