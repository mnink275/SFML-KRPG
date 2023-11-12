#include <Components/Input/EmptyInput.hpp>

namespace ink::component {

void EmptyInput::handleInput(CommandQueue<NodeCommand>& /*command_queue*/,
                             const sf::Keyboard::Key /*key*/,
                             const bool /*is_pressed*/) {}

void EmptyInput::handleRealtimeInput(sf::Time /*dt*/,
                                     CommandQueue<NodeCommand>& /*commands*/) {}

}  // namespace ink::component
