#include <iostream>
#include <vector>
#include <sstream>

#include "constants.h"
#include "toy_robot.h"
#include "command.h"

int main()
{
    toy_robot robot;
    std::string input = "";

    while (true)
    {
        std::cout << "Please enter a command: ";
        std::getline(std::cin, input);

        command cmd;
        unsigned char result = cmd.parse(input);

        if (result == E_OK)
        {
            std::string out = "";
            result = cmd.execute(robot, out);

            if (!out.empty())
            {
                std::cout << out << "\n";
            }
        }
        else
        {
            std::cout << "Invalid command. Try again."
                      << "\n";
        }
    }

    return 0;
}