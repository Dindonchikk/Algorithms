#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include <string>

#include "stack.h"

namespace
{
    // Если стек пуст, считаем, что извлекли 0.
    Data popValue(Stack* stack)
    {
        if (stack_empty(stack))
            return 0;

        Data value = stack_get(stack);
        stack_pop(stack);
        return value;
    }

    bool pushResult(Stack* stack, long long result)
    {
        if (result < std::numeric_limits<Data>::min() ||
            result > std::numeric_limits<Data>::max())
        {
            std::cerr << "Error: arithmetic overflow\n";
            return false;
        }

        stack_push(stack, static_cast<Data>(result));
        return true;
    }

    bool interpret(const std::string& program, Stack* stack,
        std::ostream& output)
    {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<Data> distribution(0, 99);

        for (char command : program)
        {
            if (command >= '0' && command <= '9')
            {
                stack_push(stack, command - '0');
            }
            else
            {
                switch (command)
                {
                case '+':
                {
                    Data right = popValue(stack);
                    Data left = popValue(stack);

                    if (!pushResult(stack,
                        static_cast<long long>(left) + right))
                        return false;
                    break;
                }

                case '-':
                {
                    Data right = popValue(stack);
                    Data left = popValue(stack);

                    if (!pushResult(stack,
                        static_cast<long long>(left) - right))
                        return false;
                    break;
                }

                case '*':
                {
                    Data right = popValue(stack);
                    Data left = popValue(stack);

                    if (!pushResult(stack,
                        static_cast<long long>(left) * right))
                        return false;
                    break;
                }

                case '/':
                {
                    Data right = popValue(stack);
                    Data left = popValue(stack);

                    if (right == 0)
                    {
                        std::cerr << "Error: division by zero\n";
                        return false;
                    }

                    long long result =
                        static_cast<long long>(left) / right;

                    if (!pushResult(stack, result))
                        return false;
                    break;
                }

                case '%':
                {
                    Data right = popValue(stack);
                    Data left = popValue(stack);

                    if (right == 0)
                    {
                        std::cerr << "Error: modulo by zero\n";
                        return false;
                    }

                    long long result =
                        static_cast<long long>(left) % right;

                    if (!pushResult(stack, result))
                        return false;
                    break;
                }

                case '!':
                {
                    Data value = popValue(stack);
                    stack_push(stack, value == 0 ? 1 : 0);
                    break;
                }

                case '`':
                {
                    Data right = popValue(stack);
                    Data left = popValue(stack);
                    stack_push(stack, left > right ? 1 : 0);
                    break;
                }

                case ':':
                {
                    Data value = popValue(stack);
                    stack_push(stack, value);
                    stack_push(stack, value);
                    break;
                }

                case '.':
                {
                    output << popValue(stack) << '\n';
                    break;
                }

                case '&':
                {
                    stack_push(stack, distribution(generator));
                    break;
                }

                default:
                    break;
                }
            }
        }

        return true;
    }
}

int main(int argc, char* argv[])
{
    std::string program;

    if (argc > 1)
    {
        std::ifstream input(argv[1]);

        if (!input)
        {
            std::cerr << "Error: cannot open input file\n";
            return 1;
        }

        std::getline(input, program);
    }
    else
    {
        if (!std::getline(std::cin, program))
            return 0;
    }

    std::ofstream outputFile;
    std::ostream* output = &std::cout;

    if (argc > 2)
    {
        outputFile.open(argv[2]);

        if (!outputFile)
        {
            std::cerr << "Error: cannot open output file\n";
            return 1;
        }

        output = &outputFile;
    }

    Stack* stack = stack_create();
    bool success = interpret(program, stack, *output);
    stack_delete(stack);

    return success ? 0 : 1;
}

