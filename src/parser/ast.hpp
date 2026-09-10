#pragma once

#include <format>
#include <functional>
#include <memory>
#include <string>

namespace cc {
  struct Expression;
  struct FunctionDeclaration;
  struct Program;
  struct Statement;

  struct Expression {
    int literal;
  };

  struct FunctionDeclaration {
    std::string id;
    std::unique_ptr<Statement> statement;
  };

  struct Program {
    std::unique_ptr<FunctionDeclaration> function;
  };

  struct Statement {
    std::unique_ptr<Expression> expr;
  };

}  // namespace cc

template<>
struct std::formatter<cc::Program> : std::formatter<std::string> {
  auto format(const cc::Program& prog, std::format_context& ctx) const {
    using namespace cc;

    std::size_t indent = 0;
    std::string out;

    std::function<void(const Expression&)> print_expression;
    std::function<void(const Statement&)> print_statement;
    std::function<void(const FunctionDeclaration&)> print_function_declaration;

    print_expression = [&](const Expression& expr) {
      out += std::format("{}Int<{}>\n", std::string(indent, ' '), expr.literal);
    };

    print_statement = [&](const Statement& stmt) {
      out += std::format("{}RETURN\n", std::string(indent, ' '));
      if (stmt.expr) {
        indent += 2;
        print_expression(*stmt.expr);
        indent -= 2;
      }
    };

    print_function_declaration = [&](const FunctionDeclaration& decl) {
      out += std::format("{}FUN INT {}:\n", std::string(indent, ' '), decl.id);
      if (decl.statement) {
        indent += 2;
        print_statement(*decl.statement);
        indent -= 2;
      }
    };

    out += "PROGRAM\n";
    if (prog.function) {
      indent += 2;
      print_function_declaration(*prog.function);
      indent -= 2;
    }

    return std::formatter<std::string>::format(out, ctx);
  }
};
