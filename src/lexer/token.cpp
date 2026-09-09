#include "token.hpp"

#include "../util/string.hpp"

namespace cc {
  Token::Token(std::string_view sv) {
    *this = Token(std::string(sv));
  }

  Token::Token(const std::string &s)
    : contained_string(s) {
    if (s == "{") {
      token_type = open_brace;
    }

    if (s == "}") {
      token_type = close_brace;
    }

    if (s == "(") {
      token_type = open_parenthesis;
    }

    if (s == ")") {
      token_type = close_parenthesis;
    }

    if (s == ";") {
      token_type = semicolon;
    }

    if (is_numeric(s)) {
      token_type = integer_literal;
    }

    token_type = identifier;
  }
}
