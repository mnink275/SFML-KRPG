#include <gtest/gtest.h>

#include <Components/ComponentManager.hpp>
#include <Components/Graphics/EmptyGraphics.hpp>
#include <Resource/ResourceIdentifiers.hpp>
#include <Room/Door.hpp>

#include <cmath>
#include <memory>

namespace ink::test {

TEST(Door, nearOf) {
  const auto door_pos = sf::Vector2f{0.0f, 0.0f};
  const auto opposite_door_pos = sf::Vector2f{};
  auto door = std::make_unique<Door>(
      ComponentManager{std::make_unique<component::EmptyGraphics>()},
      door_pos, opposite_door_pos, NodeCategory::kDoor);

  EXPECT_TRUE(door->nearOf(door_pos));

  const auto player_pos1 = door_pos + sf::Vector2f{0.0, 30.0f};
  EXPECT_TRUE(door->nearOf(player_pos1));

  const auto player_pos2 = door_pos + sf::Vector2f{50.0, 50.0f};
  EXPECT_TRUE(door->nearOf(player_pos2));

  const auto player_pos3 = door_pos + sf::Vector2f{0.0, 110.0f};
  EXPECT_FALSE(door->nearOf(player_pos3));
};

}  // namespace ink::test
