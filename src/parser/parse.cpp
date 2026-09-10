#include "parse.hpp"

#include "../util/string.hpp"

namespace cc {
  namespace {
    using TokenIt = std::vector<Token>::const_iterator;

    [[nodiscard]] auto parse_expression(TokenIt& token_it) -> std::unique_ptr<Expression>;
    [[nodiscard]] auto parse_function_declaration(TokenIt& token_it) -> std::unique_ptr<FunctionDeclaration>;
    [[nodiscard]] auto parse_statement(TokenIt& token_it) -> std::unique_ptr<Statement>;

    auto expect(TokenIt& token_it, Token::TokenType kind) -> void {
      if (Token tok = *token_it++; tok.token_type != kind) {
        throw ParseError("Expected Token");
      }
    }

    auto expect(TokenIt& token_it, const std::string_view sv) -> void {
      if (Token tok = *token_it++; !tok.is_keyword(sv)) {
        throw ParseError("Expected Keyword");
      }
    }

    [[nodiscard]] auto parse_expression(TokenIt& token_it) -> std::unique_ptr<Expression> {
      Token tok = *token_it++;

      const auto num = parse_number<int>(tok.contained_string);

      if (!num) {
        throw ParseError("Invalid Expression");
      }

      return std::make_unique<Expression>(Expression {*num});
    }

    [[nodiscard]] auto parse_function_declaration(TokenIt& token_it) -> std::unique_ptr<FunctionDeclaration> {
      FunctionDeclaration func;

      expect(token_it, "int");

      Token tok = *token_it++;

      if (tok.token_type != Token::identifier) {
        throw ParseError("Expected Identifier");
      }

      func.id = tok.contained_string;

      expect(token_it, Token::open_parenthesis);
      expect(token_it, Token::close_parenthesis);
      expect(token_it, Token::open_brace);

      func.statement = parse_statement(token_it);

      expect(token_it, Token::close_brace);

      return std::make_unique<FunctionDeclaration>(std::move(func));
    }

    [[nodiscard]] auto parse_statement(TokenIt& token_it) -> std::unique_ptr<Statement> {
      expect(token_it, "return");

      Statement statement;
      statement.expr = parse_expression(token_it);

      expect(token_it, Token::semicolon);

      return std::make_unique<Statement>(std::move(statement));
    }
  }  // namespace

  auto parse_program(const std::vector<Token>& token_stream) -> Program {
    TokenIt token_it = token_stream.begin();

    Program program;

    program.function = parse_function_declaration(token_it);

    return program;
  }

}  // namespace cc
