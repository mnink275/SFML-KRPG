#pragma once

#include <queue>

namespace ink {

template <class CommandType>
class CommandQueue {
 public:
  void push(const CommandType& command) { queue_.push(command); }

  CommandType pop() {
    auto command = queue_.front();
    queue_.pop();
    return command;
  }

  bool isEmpty() const { return queue_.empty(); }

 private:
  std::queue<CommandType> queue_;
};

}  // namespace ink
