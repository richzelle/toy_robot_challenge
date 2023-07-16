#include <gtest/gtest.h>
#include <iostream>
#include <tuple>

#include "constants.h"
#include "command.h"

/******************************************/
/* Base Test Fixture                      */
/******************************************/
class IntegrationTest : public ::testing::Test
{
protected:
    void ExecuteCommand(std::string input, unsigned char expected_err, std::string expected_out)
    {
        unsigned char actual_err = 0xFF;
        std::string actual_out = "";

        actual_err = m_cmd.parse(input);
        ASSERT_EQ(actual_err, E_OK);

        actual_err = m_cmd.execute(m_robot, actual_out);
        ASSERT_EQ(actual_err, expected_err);
        ASSERT_EQ(actual_out, expected_out);
    }

    command m_cmd;
    toy_robot m_robot;
};

/******************************************/
/* Execute Before Place                   */
/******************************************/
class ExecuteBeforePlaceTest : public IntegrationTest,
                               public ::testing::WithParamInterface<std::tuple<std::string, std::string>>
{
protected:
    void SetUp() override
    {
        m_expected_err = 0xFF;
        m_expected_out = "";
    }

    unsigned char m_expected_err;
    std::string m_expected_out;
};

TEST_P(ExecuteBeforePlaceTest, Execute)
{
    std::tuple<std::string, std::string> params = GetParam();
    std::string input = std::get<1>(params);

    ExecuteCommand(input, E_PLACE_NOT_INVOKED, "");
}

INSTANTIATE_TEST_SUITE_P(
    ExecuteBeforePlace,
    ExecuteBeforePlaceTest,
    ::testing::Values(
        std::make_tuple("MoveBeforePlace", "MOVE"),
        std::make_tuple("LeftBeforePlace", "LEFT"),
        std::make_tuple("RightBeforePlace", "RIGHT"),
        std::make_tuple("ReportBeforePlace", "REPORT")),
    [](const testing::TestParamInfo<ExecuteBeforePlaceTest::ParamType> &info)
    {
        return std::get<0>(info.param);
    });

/******************************************/
/* Consecutive calls                      */
/******************************************/
TEST_F(IntegrationTest, ConsecutivePlace)
{
    /* Execute PLACE command */
    ExecuteCommand("PLACE 1,1,EAST", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "1,1,EAST");

    /* Execute another PLACE command */
    ExecuteCommand("PLACE 2,1,WEST", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "2,1,WEST");
}

TEST_F(IntegrationTest, ConsecutiveMove)
{
    /* Execute PLACE command */
    ExecuteCommand("PLACE 0,0,NORTH", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,0,NORTH");

    /* Execute MOVE command */
    ExecuteCommand("MOVE", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,1,NORTH");

    /* Execute another MOVE command */
    ExecuteCommand("MOVE", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,2,NORTH");
}

TEST_F(IntegrationTest, ConsecutiveLeft)
{
    /* Execute PLACE command */
    ExecuteCommand("PLACE 0,0,NORTH", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,0,NORTH");

    /* Execute LEFT command */
    ExecuteCommand("LEFT", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,0,WEST");

    /* Execute another LEFT command */
    ExecuteCommand("LEFT", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,0,SOUTH");
}

TEST_F(IntegrationTest, ConsecutiveRight)
{
    /* Execute PLACE command */
    ExecuteCommand("PLACE 0,0,NORTH", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,0,NORTH");

    /* Execute RIGHT command */
    ExecuteCommand("RIGHT", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,0,EAST");

    /* Execute another RIGHT command */
    ExecuteCommand("RIGHT", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,0,SOUTH");
}

/******************************************/
/* Integration of calls                   */
/******************************************/
TEST_F(IntegrationTest, MoveAndTurnLeft)
{
    /* Execute PLACE command */
    ExecuteCommand("PLACE 0,0,NORTH", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,0,NORTH");

    /* Execute MOVE command */
    ExecuteCommand("MOVE", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,1,NORTH");

    /* Execute LEFT command */
    ExecuteCommand("LEFT", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,1,WEST");
}

TEST_F(IntegrationTest, MoveAndTurnRight)
{
    /* Execute PLACE command */
    ExecuteCommand("PLACE 0,0,NORTH", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,0,NORTH");

    /* Execute MOVE command */
    ExecuteCommand("MOVE", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,1,NORTH");

    /* Execute RIGHT command */
    ExecuteCommand("RIGHT", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,1,EAST");
}

TEST_F(IntegrationTest, TurnLeftAndTurnRight)
{
    /* Execute PLACE command */
    ExecuteCommand("PLACE 0,0,NORTH", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,0,NORTH");

    /* Execute LEFT command */
    ExecuteCommand("LEFT", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,0,WEST");

    /* Execute RIGHT command */
    ExecuteCommand("RIGHT", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,0,NORTH");
}

/******************************************/
/* MOVE out of range                      */
/******************************************/
TEST_F(IntegrationTest, MoveWestMinX)
{
    /* Execute PLACE command */
    ExecuteCommand("PLACE 0,0,WEST", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,0,WEST");

    /* Execute MOVE command */
    ExecuteCommand("MOVE", E_WILL_FALL_OUT, "");
    ExecuteCommand("REPORT", E_OK, "0,0,WEST");
}

TEST_F(IntegrationTest, MoveEastMaxX)
{
    /* Execute PLACE command */
    ExecuteCommand("PLACE 4,0,EAST", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "4,0,EAST");

    /* Execute MOVE command */
    ExecuteCommand("MOVE", E_WILL_FALL_OUT, "");
    ExecuteCommand("REPORT", E_OK, "4,0,EAST");
}

TEST_F(IntegrationTest, MoveSouthMinY)
{
    /* Execute PLACE command */
    ExecuteCommand("PLACE 0,0,SOUTH", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,0,SOUTH");

    /* Execute MOVE command */
    ExecuteCommand("MOVE", E_WILL_FALL_OUT, "");
    ExecuteCommand("REPORT", E_OK, "0,0,SOUTH");
}

TEST_F(IntegrationTest, MoveNorthMaxY)
{
    /* Execute PLACE command */
    ExecuteCommand("PLACE 0,4,NORTH", E_OK, "");
    ExecuteCommand("REPORT", E_OK, "0,4,NORTH");

    /* Execute MOVE command */
    ExecuteCommand("MOVE", E_WILL_FALL_OUT, "");
    ExecuteCommand("REPORT", E_OK, "0,4,NORTH");
}