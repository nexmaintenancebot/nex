#ifndef PARSER_HPP
#define PARSER_HPP

#include <optional>

#include "ast.hpp"

class Parser
{
public:
	Parser(const std::vector<Token>& c_tokens);

	[[nodiscard]] Expr parse_expr();
	[[nodiscard]] Stmt parse_stmt();
	[[nodiscard]] FuncDecl parse_func_decl();
	void parse();

	[[nodiscard]] Token peek(const std::size_t c_offset = 0) const;
	Token advance(const std::size_t c_distance = 1);

	[[nodiscard]] Program get_program() const;
	[[nodiscard]] std::vector<Token> get_tokens() const;
private:
	Program m_program{};
	std::vector<Token> m_tokens{};

	std::size_t m_index{};
};

#endif
