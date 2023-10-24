#include <Combat/Projectile.hpp>

namespace ink::combat {

Projectile::Projectile(const sf::Texture& texture) : Entity(texture, true) {
  setVelocity({30.f, 30.f});
}

}  // namespace ink::combat
