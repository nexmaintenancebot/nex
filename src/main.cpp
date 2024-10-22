#include <iostream>
#include <fstream>
#include <streambuf>
#include <vector>

#include "tokenizer.hpp"
#include "parser.hpp"
#include "ast.hpp"

int main(int argc, char* argv[])
{
    std::vector<Token> tokens{};

    if (argc == 2)
    {
        std::ifstream file(argv[2]);
        std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        tokens = tokenize(str);
    }
    else
    {
        std::cout << "nex v1.0\n";
        while (true)
        {
            std::string input{};
            std::cout << "> ";
            std::getline(std::cin, input);

            tokens = tokenize(input);

            for (const Token& token : tokens)
            {
                std::cout << token << "\n";
            }

            Parser parser{ tokens };

            parser.parse();

            print_program(parser.get_program());

        }
    }

    for (const Token& token : tokens)
    {
        std::cout << token << "\n";
    }

    Parser parser{ tokens };

    parser.parse();

    print_program(parser.get_program());

    return 0;
}