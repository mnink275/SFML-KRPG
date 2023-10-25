#pragma once

#include <functional>
#include <queue>

namespace ink {

using Task = std::function<void()>;
using EventQueue = std::queue<Task>;

}  // namespace ink
