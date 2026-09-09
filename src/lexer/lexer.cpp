#include "lexer.hpp"

#include <sstream>

namespace cc {
  auto lex(const std::string_view file) -> std::vector<Token> {
    auto tokens = std::vector<Token> {};

    std::size_t current = 0;

    const auto is_at_end = [&] {
      return current >= file.size();
    };

    const auto advance = [&] {
      return file.at(current++);
    };

    const auto peek = [&] {
      return file.at(current);
    };

    while (!is_at_end()) {
      const char c = advance();

      switch (c) {
      case ' ': {
      } break;
      case '\r': {
      } break;
      case '\n': {
      } break;
      case '(': {
        tokens.emplace_back("(");
      } break;
      case ')': {
        tokens.emplace_back(")");
      } break;
      case '{': {
        tokens.emplace_back("{");
      } break;
      case '}': {
        tokens.emplace_back("}");
      } break;
      default: {
        auto token = std::string {c};

        while (std::isalnum(peek())) {
          token += advance();
        }

        tokens.emplace_back(token);
      }
      }
    }

    tokens.emplace_back(Token::eof());

    return tokens;
  }
}  // namespace cc
