#include "lexer/lexer.hpp"

#include <fstream>
#include <print>

auto main([[maybe_unused]] int argc, char** argv) -> int {
  std::ifstream file(argv[1]);

  const auto tokens = cc::lex(std::string {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()});

  for (const auto& token : tokens) {
    std::println("{}", token);
  }
}
