#include "token.hpp"

#include "../util/string.hpp"

namespace cc {
  Token::Token(const std::string& s) noexcept :
      contained_string(s) {
    if (s == "{") {
      token_type = open_brace;
      return;
    }

    if (s == "}") {
      token_type = close_brace;
      return;
    }

    if (s == "(") {
      token_type = open_parenthesis;
      return;
    }

    if (s == ")") {
      token_type = close_parenthesis;
      return;
    }

    if (s == ";") {
      token_type = semicolon;
      return;
    }

    if (is_numeric(s)) {
      token_type = integer_literal;
      return;
    }

    token_type = identifier;
  }

  auto Token::eof() -> Token {
    return Token {end_of_file};
  }

  Token::operator TokenType() const {
    return token_type;
  }

  auto Token::is_keyword(const std::string_view kw) const noexcept -> bool {
    return token_type == identifier && contained_string == kw;
  }

  Token::Token(TokenType tt) noexcept :
      token_type(tt) {
  }
}  // namespace cc
