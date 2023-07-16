#ifndef TOY_ROBOT_H
#define TOY_ROBOT_H

#include <iostream>
#include <string>

const int MIN_COORDINATE = 0;
const int MAX_COORDINATE = 4;

/* Cardinal Directions */
const std::string DIR_NORTH = "NORTH";
const std::string DIR_SOUTH = "SOUTH";
const std::string DIR_EAST = "EAST";
const std::string DIR_WEST = "WEST";

class toy_robot
{
    int m_x;
    int m_y;
    std::string m_direction;

public:
    toy_robot();
    ~toy_robot();

    unsigned char place(const int x, const int y, const std::string f);
    unsigned char move();
    unsigned char left();
    unsigned char right();
    unsigned char report(std::string &out);
};

#endif /* TOY_ROBOT_H */