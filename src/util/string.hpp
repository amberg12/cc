#pragma once
#include <charconv>
#include <optional>
#include <string_view>

namespace cc {
  [[nodiscard]] auto is_numeric(std::string_view sv) noexcept -> bool;

  template<class T>
    requires(std::is_arithmetic_v<T>)
  [[nodiscard]] auto parse_number(std::string_view sv) noexcept -> std::optional<T> {
    if (T value {}; std::from_chars(sv.data(), sv.data() + sv.length(), value).ec == std::errc {}) {
      return value;
    }

    return std::nullopt;
  }
}  // namespace cc
