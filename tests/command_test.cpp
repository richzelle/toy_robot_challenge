#include <gtest/gtest.h>
#include <iostream>
#include <tuple>

#include "constants.h"
#include "command.h"

/******************************************/
/* Base Test Fixture                      */
/******************************************/
class CommandTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        m_actual_err = 0xFF;
        m_expected_err = 0xFF;
        m_input = "";
    }

    command m_cmd;
    std::string m_input;

    unsigned char m_actual_err;
    unsigned char m_expected_err;
};

/******************************************/
/* Parse Invalid Commands                 */
/******************************************/
class ParseInvalidCommandTest : public CommandTest,
                                public ::testing::WithParamInterface<std::tuple<std::string, std::string>>
{
    void SetUp() override
    {
        m_expected_err = E_INVALID_CMD;
    }
};

TEST_P(ParseInvalidCommandTest, Parse)
{
    std::tuple<std::string, std::string> params = GetParam();
    m_input = std::get<1>(params);

    m_actual_err = m_cmd.parse(m_input);
    ASSERT_EQ(m_actual_err, m_expected_err);
}

INSTANTIATE_TEST_SUITE_P(
    ParseInvalidCommand,
    ParseInvalidCommandTest,
    ::testing::Values(
        std::make_tuple("EmptyString", ""),
        std::make_tuple("WhiteSpaceOnly", " "),
        std::make_tuple("InvalidCommand", "PRINT"),
        std::make_tuple("LowerCase", "place"),
        std::make_tuple("MoveWithParam", "MOVE 1,2,NORTH"),
        std::make_tuple("LeftWithParam", "LEFT 1,2,NORTH"),
        std::make_tuple("RightWithParam", "RIGHT 1,2,NORTH"),
        std::make_tuple("ReportWithParam", "REPORT 1,2,NORTH"),
        std::make_tuple("PlaceNoParam", "PLACE"),
        std::make_tuple("PlaceNonNumericX", "PLACE A,0,NORTH"),
        std::make_tuple("PlaceNonNumericY", "PLACE 0,A,NORTH"),
        std::make_tuple("PlaceAboveMaxX", "PLACE 5,0,NORTH"),
        std::make_tuple("PlaceAboveMaxY", "PLACE 0,5,NORTH"),
        std::make_tuple("PlaceBelowMinX", "PLACE -1,0,NORTH"),
        std::make_tuple("PlaceBelowMinY", "PLACE 0,-1,NORTH"),
        std::make_tuple("PlaceInvalidDirection", "PLACE 0,0,NORTHEAST")),
    [](const testing::TestParamInfo<ParseInvalidCommandTest::ParamType> &info)
    {
        return std::get<0>(info.param);
    });

/******************************************/
/* Parse Valid Commands                   */
/******************************************/
class ParseValidCommandTest : public CommandTest,
                              public ::testing::WithParamInterface<std::tuple<std::string, std::string>>
{
    void SetUp() override
    {
        m_expected_err = E_OK;
    }
};

TEST_P(ParseValidCommandTest, Parse)
{
    std::tuple<std::string, std::string> params = GetParam();
    m_input = std::get<1>(params);

    m_actual_err = m_cmd.parse(m_input);
    ASSERT_EQ(m_actual_err, m_expected_err);
}

INSTANTIATE_TEST_SUITE_P(
    ParseValidCommand,
    ParseValidCommandTest,
    ::testing::Values(
        std::make_tuple("MoveCommand", "MOVE"),
        std::make_tuple("LeftCommand", "LEFT"),
        std::make_tuple("RightCommand", "RIGHT"),
        std::make_tuple("ReportCommand", "REPORT"),
        std::make_tuple("PlaceMinCoordinates", "PLACE 0,0,NORTH"),
        std::make_tuple("PlaceMaxCoordinates", "PLACE 4,4,NORTH"),
        std::make_tuple("PlaceSouthDirection", "PLACE 2,2,SOUTH"),
        std::make_tuple("PlaceEastDirection", "PLACE 2,2,EAST"),
        std::make_tuple("PlaceWestDirection", "PLACE 2,2,WEST"),
        std::make_tuple("WithWhitespaceAtStart", " MOVE"),
        std::make_tuple("WithWhitespaceAtEnd", "MOVE "),
        std::make_tuple("WithWhitespaceOnBothSides", " MOVE ")),
    [](const testing::TestParamInfo<ParseValidCommandTest::ParamType> &info)
    {
        return std::get<0>(info.param);
    });

/******************************************/
/* Execute                                */
/******************************************/
TEST(ExecuteTest, EmptyCommand)
{
    command m_cmd;
    toy_robot m_robot;

    unsigned char m_actual_err = 0xFF;
    std::string m_actual_out = "";

    m_actual_err = m_cmd.execute(m_robot, m_actual_out);

    ASSERT_EQ(m_actual_err, E_INVALID_CMD);
    ASSERT_EQ(m_actual_out, "");
}

TEST(ExecuteTest, Place)
{
    command m_cmd;
    toy_robot m_robot;

    unsigned char m_actual_err = 0xFF;
    std::string m_actual_out = "";

    m_actual_err = m_cmd.parse("PLACE 0,0,NORTH");
    m_actual_err = m_cmd.execute(m_robot, m_actual_out);

    ASSERT_EQ(m_actual_err, E_OK);
    ASSERT_EQ(m_actual_out, "");
}

/******************************************/
/* Execute Valid Commands                 */
/******************************************/
class ExecuteValidCommandTest : public CommandTest,
                                public ::testing::WithParamInterface<std::tuple<std::string, std::string, std::string>>
{
protected:
    void SetUp() override
    {
        m_actual_err = m_cmd.parse("PLACE 0,0,NORTH");
        m_actual_err = m_cmd.execute(m_robot, m_actual_out);

        m_expected_err = E_OK;

        m_actual_out = "";
        m_expected_out = "";
    }

    toy_robot m_robot;
    std::string m_actual_out;
    std::string m_expected_out;
};

TEST_P(ExecuteValidCommandTest, Execute)
{
    std::tuple<std::string, std::string, std::string> params = GetParam();
    m_input = std::get<1>(params);
    m_expected_out = std::get<2>(params);

    m_actual_err = m_cmd.parse(m_input);
    m_actual_err = m_cmd.execute(m_robot, m_actual_out);

    ASSERT_EQ(m_actual_err, m_expected_err);
    ASSERT_EQ(m_actual_out, m_expected_out);
}

INSTANTIATE_TEST_SUITE_P(
    ExecuteValidCommand,
    ExecuteValidCommandTest,
    ::testing::Values(
        std::make_tuple("MoveCommand", "MOVE", ""),
        std::make_tuple("LeftCommand", "LEFT", ""),
        std::make_tuple("RightCommand", "RIGHT", ""),
        std::make_tuple("ReportCommand", "REPORT", "0,0,NORTH")),
    [](const testing::TestParamInfo<ExecuteValidCommandTest::ParamType> &info)
    {
        return std::get<0>(info.param);
    });
