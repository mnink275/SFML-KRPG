#pragma once

#include <SFML/Graphics.hpp>
#include <cassert>
#include <map>
#include <memory>

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

// Methods implementation.
#include "ResourceHolder.inl"