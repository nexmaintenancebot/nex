#include <variant>
#include <iostream>

#include "ast.hpp"

void print_expr(const Expr& c_expr)
{
    std::cout << "Expr: { Type: ";
    switch (c_expr.m_expr_type)
    {
    case (ExprType::normal):
        std::cout << "Normal";
        break;
    case (ExprType::return_):
        std::cout << "Return";
        break;
    }
    std::cout << ", IntLit: " << c_expr.m_int_lit << " }";
}

void print_stmt(const Stmt& c_stmt)
{
    std::cout << "Stmt: { ";
    print_expr(c_stmt.m_expr);
    std::cout << " }";
}

void print_func_decl(const FuncDecl& c_func_decl)
{
    std::cout << "FuncDecl: { Name: \"" << c_func_decl.m_name << "\", Body: [ ";
    for (const auto& stmt : c_func_decl.m_body)
    {
        print_stmt(stmt);
        std::cout << " ";
    }
    std::cout << "] }";
}

void print_program(const Program& c_program)
{
    std::cout << "Program: [ ";
    for (const auto& item : c_program.m_body)
    {
        std::visit([](auto&& arg)
            {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, FuncDecl>)
                    print_func_decl(arg);
                else if constexpr (std::is_same_v<T, Stmt>)
                    print_stmt(arg);
            }, item);
        std::cout << " ";
    }
    std::cout << "]\n";
}