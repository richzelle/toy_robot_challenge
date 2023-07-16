#include <iostream>
#include <vector>
#include <sstream>
#include <regex>

#include "command.h"
#include "constants.h"
#include "string_util.h"

command::command() : m_cmd("")
{
}

command::~command()
{
}

unsigned char command::parse(std::string input)
{
    unsigned char result = E_INVALID_CMD;

    const std::regex cmd_no_param_regex("(MOVE|LEFT|RIGHT|REPORT)");
    const std::regex cmd_has_param_regex("PLACE [0-4]{1},[0-4]{1},(NORTH|SOUTH|EAST|WEST)");

    input = string_util::trim(input);
    if (std::regex_match(input, cmd_no_param_regex))
    {
        m_cmd = input;
        result = E_OK;
    }
    else if (std::regex_match(input, cmd_has_param_regex))
    {
        std::vector<std::string> cmd = tokenize(input, CMD_DELIM);

        m_cmd = cmd[0];
        m_params = tokenize(cmd[1], PARAM_DELIM);
        result = E_OK;
    }

    return result;
}

unsigned char command::execute(toy_robot &robot, std::string &out)
{
    unsigned char result = E_INVALID_CMD;
    out = "";

    if (!m_cmd.empty())
    {
        if (m_cmd.compare(CMD_PLACE) == 0)
        {
            result = robot.place(std::stoi(m_params[0]), std::stoi(m_params[1]), m_params[2]);
        }
        else if (m_cmd.compare(CMD_MOVE) == 0)
        {
            result = robot.move();
        }
        else if (m_cmd.compare(CMD_LEFT) == 0)
        {
            result = robot.left();
        }
        else if (m_cmd.compare(CMD_RIGHT) == 0)
        {
            result = robot.right();
        }
        else if (m_cmd.compare(CMD_REPORT) == 0)
        {
            result = robot.report(out);
        }
    }

    return result;
}

std::vector<std::string> command::tokenize(const std::string input, const char delimiter)
{
    std::stringstream ss(input);
    std::vector<std::string> tokens;
    std::string token;

    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}
