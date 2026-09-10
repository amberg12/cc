#pragma once

#include "../lexer/token.hpp"
#include "ast.hpp"

#include <stdexcept>
#include <vector>

namespace cc {
  class ParseError : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

  [[nodiscard]] auto parse_program(const std::vector<Token>& token_stream) -> Program;
}  // namespace cc
