#pragma once

#include <format>
#include <string>

namespace cc {
  struct Token {
    enum TokenType {
      open_brace,
      close_brace,
      open_parenthesis,
      close_parenthesis,
      semicolon,
      identifier,
      integer_literal,
      end_of_file,
    };

    explicit Token(const std::string& s) noexcept;

    static auto eof() -> Token;

    /* implicit */ operator Token::TokenType() const;

    [[nodiscard]] auto is_keyword(std::string_view kw) const noexcept -> bool;

    TokenType token_type;
    std::string contained_string;

  private:
    explicit Token(TokenType) noexcept;
  };
}  // namespace cc

template<>
struct std::formatter<cc::Token> : std::formatter<std::string> {
  auto format(const cc::Token& tok, std::format_context& ctx) const {
    switch (tok) {
    case cc::Token::open_brace: {
      return std::format_to(ctx.out(), "open_brace");
    }
    case cc::Token::close_brace: {
      return std::format_to(ctx.out(), "close_brace");
    }
    case cc::Token::open_parenthesis: {
      return std::format_to(ctx.out(), "open_parenthesis");
    }
    case cc::Token::close_parenthesis: {
      return std::format_to(ctx.out(), "close_parenthesis");
    }
    case cc::Token::semicolon: {
      return std::format_to(ctx.out(), "semicolon");
    }
    case cc::Token::identifier: {
      return std::format_to(ctx.out(), "identifier {}", tok.contained_string);
    }
    case cc::Token::integer_literal: {
      return std::format_to(ctx.out(), "integer_literal {}", tok.contained_string);
    }
    case cc::Token::end_of_file: {
      return std::format_to(ctx.out(), "end_of_file");
    }
    }
  }
};
