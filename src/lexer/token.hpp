#pragma once

#include <string>

namespace cc {
  struct Token {
    enum TokenType {
      open_brace,
      close_brace,
      open_parenthesis,
      close_parenthesis,
      semicolon,
      keyword,
      identifier,
      integer_literal,
    };

    explicit Token(std::string_view sv);

    explicit Token(const std::string &s);

    TokenType token_type;
    std::string contained_string;
  };
}
