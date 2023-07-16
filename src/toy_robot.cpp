#include <iostream>

#include "constants.h"
#include "toy_robot.h"

toy_robot::toy_robot() : m_x(-1), m_y(-1), m_direction("")
{
}

toy_robot::~toy_robot()
{
}

unsigned char toy_robot::place(const int x, const int y, const std::string f)
{
    unsigned char result = E_INVALID_PARAM;

    if ((x >= MIN_COORDINATE && x <= MAX_COORDINATE) &&
        (y >= MIN_COORDINATE && y <= MAX_COORDINATE) &&
        (f.compare(DIR_NORTH) == 0 ||
         f.compare(DIR_SOUTH) == 0 ||
         f.compare(DIR_EAST) == 0 ||
         f.compare(DIR_WEST) == 0))
    {
        m_x = x;
        m_y = y;
        m_direction = f;
        result = E_OK;
    }

    return result;
}

unsigned char toy_robot::move()
{
    unsigned char result = E_PLACE_NOT_INVOKED;

    if (m_x >= MIN_COORDINATE && m_y >= MIN_COORDINATE)
    {
        if ((m_direction.compare(DIR_NORTH) == 0) && (m_y < MAX_COORDINATE))
        {
            result = E_OK;
            m_y++;
        }
        else if ((m_direction.compare(DIR_SOUTH) == 0) && (m_y > MIN_COORDINATE))
        {
            result = E_OK;
            m_y--;
        }
        else if ((m_direction.compare(DIR_EAST) == 0) && (m_x < MAX_COORDINATE))
        {
            result = E_OK;
            m_x++;
        }
        else if ((m_direction.compare(DIR_WEST) == 0) && (m_x > MIN_COORDINATE))
        {
            result = E_OK;
            m_x--;
        }
        else
        {
            result = E_WILL_FALL_OUT;
        }
    }

    return result;
}

unsigned char toy_robot::left()
{
    unsigned char result = E_PLACE_NOT_INVOKED;

    if (m_x >= MIN_COORDINATE && m_y >= MIN_COORDINATE)
    {
        if (m_direction.compare(DIR_NORTH) == 0)
        {
            result = E_OK;
            m_direction = DIR_WEST;
        }
        else if (m_direction.compare(DIR_WEST) == 0)
        {
            result = E_OK;
            m_direction = DIR_SOUTH;
        }
        else if (m_direction.compare(DIR_SOUTH) == 0)
        {
            result = E_OK;
            m_direction = DIR_EAST;
        }
        else if (m_direction.compare(DIR_EAST) == 0)
        {
            result = E_OK;
            m_direction = DIR_NORTH;
        }
    }

    return result;
}

unsigned char toy_robot::right()
{
    unsigned char result = E_PLACE_NOT_INVOKED;

    if (m_x >= MIN_COORDINATE && m_y >= MIN_COORDINATE)
    {
        if (m_direction.compare(DIR_NORTH) == 0)
        {
            result = E_OK;
            m_direction = DIR_EAST;
        }
        else if (m_direction.compare(DIR_EAST) == 0)
        {
            result = E_OK;
            m_direction = DIR_SOUTH;
        }
        else if (m_direction.compare(DIR_SOUTH) == 0)
        {
            result = E_OK;
            m_direction = DIR_WEST;
        }
        else if (m_direction.compare(DIR_WEST) == 0)
        {
            result = E_OK;
            m_direction = DIR_NORTH;
        }
    }

    return result;
}

unsigned char toy_robot::report(std::string &out)
{
    unsigned char result = E_PLACE_NOT_INVOKED;
    out = "";

    if (m_x >= MIN_COORDINATE && m_y >= MIN_COORDINATE)
    {
        result = E_OK;
        out = std::to_string(m_x) + "," +
              std::to_string(m_y) + "," +
              m_direction;
    }

    return result;
}
