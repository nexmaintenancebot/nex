#include <cctype>
#include <cstdlib>
#include <iostream>

#include "tokenizer.hpp"

const std::unordered_map<std::string, TokenType> c_keywords
{
    {"return", TokenType::TT_return},
    {"int",    TokenType::TT_int}
};

Token::Token(const std::string& c_value, const TokenType& c_type) : m_value(c_value), m_type(c_type) {}

std::ostream& operator<<(std::ostream& os, const Token& c_token) 
{
    os << "{ Value: " << c_token.m_value << ", Token: " << to_string(c_token.m_type) << " }";
    return os;
}

[[nodiscard]] std::string Token::get_value() const { return m_value; }
[[nodiscard]] TokenType Token::get_type()    const { return m_type; }

[[nodiscard]] bool is_skippable(const char c_c) { return c_c == ' ' || c_c == '\n' || c_c == '\t'; }
[[nodiscard]] std::string ctos(const char c_c)  { return std::string(1, c_c); }

[[nodiscard]] std::string to_string(const TokenType c_token_type)
{
    switch (c_token_type)
    {
    case (TokenType::TT_int_lit):     return "TT_int_lit";
    case (TokenType::TT_identifier):  return "TT_identifier";
    case (TokenType::TT_semi):        return "TT_semi";
    case (TokenType::TT_equals):      return "TT_equals";
    case (TokenType::TT_add):         return "TT_add";
    case (TokenType::TT_subtract):    return "TT_subtract";
    case (TokenType::TT_multiply):    return "TT_multiply";
    case (TokenType::TT_divide):      return "TT_divide";
    case (TokenType::TT_o_paren):     return "TT_o_paren";
    case (TokenType::TT_c_paren):     return "TT_c_paren";
    case (TokenType::TT_o_bracket):   return "TT_o_bracket";
    case (TokenType::TT_c_bracket):   return "TT_c_bracket";
    case (TokenType::TT_int):         return "TT_int";
    case (TokenType::TT_return):      return "TT_return";
    case (TokenType::TT_eof):         return "TT_eof";
    default:                          return "unknown";
    }
}

[[nodiscard]] std::vector<Token> tokenize(std::string& source)
{
    source += " ";

    std::vector<Token> tokens{};
    std::string buffer{};

    for (std::size_t i = 0; i < source.size(); i++)
    {
        if (i < source.size() - 1)
        {
            char current{ source.at(i) };
            char next{ source.at(i + 1) };

            if (!is_skippable(current))
            {
                switch (current)
                {
                case ('('): tokens.push_back({ ctos(current), TokenType::TT_o_paren });   break;
                case (')'): tokens.push_back({ ctos(current), TokenType::TT_c_paren });   break;
                case ('{'): tokens.push_back({ ctos(current), TokenType::TT_o_bracket }); break;
                case ('}'): tokens.push_back({ ctos(current), TokenType::TT_c_bracket }); break;
                case (';'): tokens.push_back({ ctos(current), TokenType::TT_semi });      break;
                case ('='): tokens.push_back({ ctos(current), TokenType::TT_equals });    break;
                case ('+'): tokens.push_back({ ctos(current), TokenType::TT_add });       break;
                case ('-'): tokens.push_back({ ctos(current), TokenType::TT_subtract });  break;
                case ('*'): tokens.push_back({ ctos(current), TokenType::TT_multiply });  break;
                case ('/'): tokens.push_back({ ctos(current), TokenType::TT_divide });    break;
                default:
                    if (std::isdigit(current))
                    {
                        buffer += current;
                        if (!std::isdigit(next))
                        {
                            tokens.push_back({ buffer, TokenType::TT_int_lit });
                            buffer.clear();
                        }
                    }
                    else if (std::isalpha(current))
                    {
                        buffer += current;
                        if (!std::isalpha(next))
                        {
                            auto reserved = c_keywords.find(buffer);
                            if (reserved != c_keywords.end())
                            {
                                tokens.push_back({ buffer, reserved->second });
                            }
                            else
                            {
                                tokens.push_back({ buffer, TokenType::TT_identifier });
                            }
                            buffer.clear();
                        }
                    }
                    else
                    {
                        std::cerr << "Nex : no matching token found for \"" << current << "\"\n";
                        exit(EXIT_FAILURE);
                    }
                }

            }
        }
    }

    tokens.push_back({ "eof", TokenType::TT_eof });

    return tokens;
}
