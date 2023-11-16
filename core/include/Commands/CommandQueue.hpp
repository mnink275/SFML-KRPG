#pragma once

#include <cstddef>
#include <functional>
#include <queue>

#include <SFML/System/Time.hpp>

namespace ink {

template <class CommandType>
class CommandQueue final {
 public:
  CommandQueue() = default;

  ~CommandQueue() = default;

  CommandQueue(const CommandQueue&) = delete;
  CommandQueue& operator=(const CommandQueue&) = delete;

  CommandQueue(CommandQueue&&) = delete;
  CommandQueue& operator=(CommandQueue&&) = delete;

  void push(const CommandType& command) { queue_.push(command); }

  void handle(std::function<void(const CommandType&, sf::Time)> func,
              sf::Time dt) {
    for (std::size_t i = 0; i < getSize(); ++i) {
      auto command = pop();
      command.delay -= dt;
      if (command.delay <= sf::Time::Zero) {
        func(command, dt);
      } else {
        push(command);
      }
    }
  }

  bool isEmpty() const { return queue_.empty(); }

  std::size_t getSize() const noexcept { return queue_.size(); }

 private:
  CommandType pop() {
    auto command = queue_.front();
    queue_.pop();
    return command;
  }

 private:
  std::queue<CommandType> queue_;
};

}  // namespace ink
