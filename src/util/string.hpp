#pragma once
#include <string_view>

namespace cc {
  [[nodiscard]] auto is_numeric(std::string_view sv) noexcept -> bool;
}
