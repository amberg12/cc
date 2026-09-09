#pragma once
#include "token.hpp"

#include <vector>

namespace cc {
  [[nodiscard]] auto lex(std::string_view file) -> std::vector<Token>;
}  // namespace cc
