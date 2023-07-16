#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>
#include <vector>

#include "toy_robot.h"

/* Commands */
const std::string CMD_PLACE = "PLACE";
const std::string CMD_MOVE = "MOVE";
const std::string CMD_LEFT = "LEFT";
const std::string CMD_RIGHT = "RIGHT";
const std::string CMD_REPORT = "REPORT";

const char CMD_DELIM = ' ';
const char PARAM_DELIM = ',';

const int MIN_CMD_SIZE = 1;
const int PARAM_SIZE = 3;

class command
{
    std::string m_cmd;
    std::vector<std::string> m_params;

    std::vector<std::string> tokenize(const std::string input, const char delimiter);

public:
    command();
    ~command();

    unsigned char parse(std::string input);
    unsigned char execute(toy_robot &robot, std::string &out);
};

#endif /* COMMAND_H */