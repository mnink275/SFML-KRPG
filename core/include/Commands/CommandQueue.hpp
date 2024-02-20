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
    while (!isEmpty()) {
      auto command = pop();
      command.delay -= dt;
      if (command.delay <= sf::Time::Zero) {
        func(command, dt);
      } else {
        delayed_tasks_.push(command);
      }
    }

    std::swap(queue_, delayed_tasks_);
  }

  [[nodiscard]] bool isEmpty() const { return queue_.empty(); }

  [[nodiscard]] std::size_t getSize() const noexcept { return queue_.size(); }

 private:
  CommandType pop() {
    auto command = std::move(queue_.front());
    queue_.pop();
    return command;
  }

 private:
  std::queue<CommandType> queue_;
  std::queue<CommandType> delayed_tasks_;
};

}  // namespace ink
