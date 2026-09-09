#include "string.hpp"

#include <algorithm>
#include <locale>

namespace cc {
  auto is_numeric(std::string_view sv) noexcept -> bool {
    return std::ranges::all_of(sv, [](const auto c) {
      return std::isdigit(c);
    });
  }
}  // namespace cc
