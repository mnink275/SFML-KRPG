// #pragma once

// namespace ink::component {

// class CollisionComponent : public Component {
//  public:
//   CollisionComponent();
//   virtual ~CollisionComponent() = default;

//   virtual void handleInput(CommandQueue<NodeCommand>& command_queue,
//                            const sf::Keyboard::Key key,
//                            const bool is_pressed) = 0;
//   virtual void handleRealtimeInput(sf::Time dt,
//                                    CommandQueue<NodeCommand>& commands) = 0;

//  protected:
//   void createCommand(sf::Keyboard::Key key,
//                      ComponentCommand::Receiver receiver_category,
//                      ComponentCommand::Action action);

//   std::unordered_map<sf::Keyboard::Key, std::vector<ComponentCommand>>
//       commands_;
// };

// }  // namespace ink::component
