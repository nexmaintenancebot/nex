#ifndef AST_HPP
#define AST_HPP

#include <vector>
#include <string>
#include <variant>

enum class ExprType
{
    normal,
    return_,
};

struct Expr
{
    ExprType m_expr_type{};
    int m_int_lit{};
};

struct Stmt
{
    Expr m_expr{};
};

struct FuncDecl
{
    std::string m_name{};
    std::vector<Stmt> m_body{};
};

struct Program
{
    std::vector<std::variant<FuncDecl, Stmt>> m_body{};
};

void print_expr(const Expr& c_expr);
void print_stmt(const Stmt& c_stmt);
void print_func_decl(const FuncDecl& c_func_decl);
void print_program(const Program& c_program);

#endif