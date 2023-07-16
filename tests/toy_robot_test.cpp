#include <gtest/gtest.h>
#include <iostream>

#include "constants.h"
#include "toy_robot.h"

/******************************************/
/* Base Test Fixture                      */
/******************************************/
class ToyRobotTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        m_actual_err = 0xFF;
        m_expected_err = 0xFF;
        m_actual_out = "";
        m_expected_out = "";
    }

    toy_robot m_robot;

    int m_x;
    int m_y;
    std::string m_f;

    unsigned char m_actual_err;
    unsigned char m_expected_err;

    std::string m_actual_out;
    std::string m_expected_out;
};

/******************************************/
/* PLACE Invalid Parameters               */
/******************************************/
class PlaceInvalidParamTest : public ToyRobotTest,
                              public ::testing::WithParamInterface<std::tuple<std::string, int, int, std::string>>
{
    void SetUp() override
    {
        m_expected_err = E_INVALID_PARAM;
    }
};

TEST_P(PlaceInvalidParamTest, Place)
{
    std::tuple<std::string, int, int, std::string> params = GetParam();

    m_x = std::get<1>(params);
    m_y = std::get<2>(params);
    m_f = std::get<3>(params);

    m_actual_err = m_robot.place(m_x, m_y, m_f);
    ASSERT_EQ(m_actual_err, m_expected_err);

    m_robot.report(m_actual_out);
    ASSERT_EQ(m_actual_out, m_expected_out);
}

INSTANTIATE_TEST_SUITE_P(
    PlaceInvalidParam,
    PlaceInvalidParamTest,
    ::testing::Values(
        std::make_tuple("XCoordinateBelowMin", MIN_COORDINATE - 1, MIN_COORDINATE, DIR_NORTH),
        std::make_tuple("XCoordinateAboveMax", MAX_COORDINATE + 1, MIN_COORDINATE, DIR_NORTH),
        std::make_tuple("YCoordinateBelowMin", MIN_COORDINATE, MIN_COORDINATE - 1, DIR_NORTH),
        std::make_tuple("YCoordinateAboveMax", MIN_COORDINATE, MAX_COORDINATE + 1, DIR_NORTH),
        std::make_tuple("InvalidDirection", MIN_COORDINATE, MIN_COORDINATE, "NORTHEAST")),
    [](const testing::TestParamInfo<PlaceInvalidParamTest::ParamType> &info)
    {
        return std::get<0>(info.param);
    });

/******************************************/
/* PLACE Valid Parameters                 */
/******************************************/
class PlaceValidParamTest : public ToyRobotTest,
                            public ::testing::WithParamInterface<std::tuple<std::string, int, int, std::string, std::string>>
{
    void SetUp() override
    {
        m_expected_err = E_OK;
    }
};

TEST_P(PlaceValidParamTest, Place)
{
    std::tuple<std::string, int, int, std::string, std::string> params = GetParam();

    m_x = std::get<1>(params);
    m_y = std::get<2>(params);
    m_f = std::get<3>(params);

    m_expected_out = std::get<4>(params);

    m_actual_err = m_robot.place(m_x, m_y, m_f);
    ASSERT_EQ(m_actual_err, m_expected_err);

    m_robot.report(m_actual_out);
    ASSERT_EQ(m_actual_out, m_expected_out);
}

INSTANTIATE_TEST_SUITE_P(
    PlaceValidParam,
    PlaceValidParamTest,
    ::testing::Values(
        std::make_tuple("MinCoordinates", MIN_COORDINATE, MIN_COORDINATE, DIR_NORTH, "0,0,NORTH"),
        std::make_tuple("MaxCoordinates", MAX_COORDINATE, MAX_COORDINATE, DIR_NORTH, "4,4,NORTH"),
        std::make_tuple("SouthDirection", 2, 2, DIR_SOUTH, "2,2,SOUTH"),
        std::make_tuple("EastDirection", 2, 2, DIR_EAST, "2,2,EAST"),
        std::make_tuple("WestDirection", 2, 2, DIR_WEST, "2,2,WEST")),
    [](const testing::TestParamInfo<PlaceValidParamTest::ParamType> &info)
    {
        return std::get<0>(info.param);
    });

/******************************************/
/* MOVE Invalid                           */
/******************************************/
class MoveOutOfRangeTest : public ToyRobotTest,
                        public ::testing::WithParamInterface<std::tuple<std::string, int, int, std::string, std::string>>
{
    void SetUp() override
    {
        m_expected_err = E_WILL_FALL_OUT;
    }
};

TEST_P(MoveOutOfRangeTest, Move)
{
    std::tuple<std::string, int, int, std::string, std::string> params = GetParam();

    m_x = std::get<1>(params);
    m_y = std::get<2>(params);
    m_f = std::get<3>(params);

    m_expected_out = std::get<4>(params);

    m_robot.place(m_x, m_y, m_f);
    m_actual_err = m_robot.move();
    ASSERT_EQ(m_actual_err, m_expected_err);

    m_robot.report(m_actual_out);
    ASSERT_EQ(m_actual_out, m_expected_out);
}

INSTANTIATE_TEST_SUITE_P(
    MoveOutOfRange,
    MoveOutOfRangeTest,
    ::testing::Values(
        std::make_tuple("MinXCoordinate", MIN_COORDINATE, MIN_COORDINATE, DIR_WEST, "0,0,WEST"),
        std::make_tuple("MaxXCoordinate", MAX_COORDINATE, MIN_COORDINATE, DIR_EAST, "4,0,EAST"),
        std::make_tuple("MinYCoordinate", MIN_COORDINATE, MIN_COORDINATE, DIR_SOUTH, "0,0,SOUTH"),
        std::make_tuple("MaxYCoordinate", MIN_COORDINATE, MAX_COORDINATE, DIR_NORTH, "0,4,NORTH")),
    [](const testing::TestParamInfo<MoveOutOfRangeTest::ParamType> &info)
    {
        return std::get<0>(info.param);
    });

/******************************************/
/* MOVE Valid                             */
/******************************************/
class MoveWithinRangeTest : public ToyRobotTest,
                      public ::testing::WithParamInterface<std::tuple<std::string, int, int, std::string, std::string>>
{
    void SetUp() override
    {
        m_expected_err = E_OK;
    }
};

TEST_P(MoveWithinRangeTest, Move)
{
    std::tuple<std::string, int, int, std::string, std::string> params = GetParam();

    m_x = std::get<1>(params);
    m_y = std::get<2>(params);
    m_f = std::get<3>(params);

    m_expected_out = std::get<4>(params);

    m_robot.place(m_x, m_y, m_f);
    m_actual_err = m_robot.move();
    ASSERT_EQ(m_actual_err, m_expected_err);

    m_robot.report(m_actual_out);
    ASSERT_EQ(m_actual_out, m_expected_out);
}

INSTANTIATE_TEST_SUITE_P(
    MoveWithinRange,
    MoveWithinRangeTest,
    ::testing::Values(
        std::make_tuple("MoveNorth", MIN_COORDINATE, MIN_COORDINATE, DIR_NORTH, "0,1,NORTH"),
        std::make_tuple("MoveSouth", MIN_COORDINATE, MAX_COORDINATE, DIR_SOUTH, "0,3,SOUTH"),
        std::make_tuple("MoveEast", MIN_COORDINATE, MIN_COORDINATE, DIR_EAST, "1,0,EAST"),
        std::make_tuple("MoveWest", MAX_COORDINATE, MIN_COORDINATE, DIR_WEST, "3,0,WEST")),
    [](const testing::TestParamInfo<MoveWithinRangeTest::ParamType> &info)
    {
        return std::get<0>(info.param);
    });

/******************************************/
/* LEFT                                   */
/******************************************/
class LeftTurnTest : public ToyRobotTest,
                      public ::testing::WithParamInterface<std::tuple<std::string, std::string, std::string>>
{
    void SetUp() override
    {
        m_x = MIN_COORDINATE;
        m_y = MIN_COORDINATE;
        m_expected_err = E_OK;
    }
};

TEST_P(LeftTurnTest, Left)
{
    std::tuple<std::string, std::string, std::string> params = GetParam();

    m_f = std::get<1>(params);
    m_expected_out = std::get<2>(params);

    m_robot.place(m_x, m_y, m_f);
    m_actual_err = m_robot.left();
    ASSERT_EQ(m_actual_err, m_expected_err);

    m_robot.report(m_actual_out);
    ASSERT_EQ(m_actual_out, m_expected_out);
}

INSTANTIATE_TEST_SUITE_P(
    LeftTurn,
    LeftTurnTest,
    ::testing::Values(
        std::make_tuple("NorthToWest", DIR_NORTH, "0,0,WEST"),
        std::make_tuple("WestToSouth", DIR_WEST, "0,0,SOUTH"),
        std::make_tuple("SouthToEast", DIR_SOUTH, "0,0,EAST"),
        std::make_tuple("EastToNorth", DIR_EAST, "0,0,NORTH")),
    [](const testing::TestParamInfo<LeftTurnTest::ParamType> &info)
    {
        return std::get<0>(info.param);
    });

/******************************************/
/* RIGHT                                  */
/******************************************/
class RightTurnTest : public ToyRobotTest,
                       public ::testing::WithParamInterface<std::tuple<std::string, std::string, std::string>>
{
    void SetUp() override
    {
        m_x = MIN_COORDINATE;
        m_y = MIN_COORDINATE;
        m_expected_err = E_OK;
    }
};

TEST_P(RightTurnTest, Right)
{
    std::tuple<std::string, std::string, std::string> params = GetParam();

    m_f = std::get<1>(params);

    m_expected_out = std::get<2>(params);

    m_robot.place(m_x, m_y, m_f);
    m_actual_err = m_robot.right();
    ASSERT_EQ(m_actual_err, m_expected_err);

    m_robot.report(m_actual_out);
    ASSERT_EQ(m_actual_out, m_expected_out);
}

INSTANTIATE_TEST_SUITE_P(
    RightTurn,
    RightTurnTest,
    ::testing::Values(
        std::make_tuple("NorthToEast", DIR_NORTH, "0,0,EAST"),
        std::make_tuple("EastToSouth", DIR_EAST, "0,0,SOUTH"),
        std::make_tuple("SouthToWest", DIR_SOUTH, "0,0,WEST"),
        std::make_tuple("WestToNorth", DIR_WEST, "0,0,NORTH")),
    [](const testing::TestParamInfo<RightTurnTest::ParamType> &info)
    {
        return std::get<0>(info.param);
    });

/******************************************/
/* PLACE NOT INVOKED                      */
/******************************************/
TEST_F(ToyRobotTest, MoveBeforePlace)
{
    m_expected_err = E_PLACE_NOT_INVOKED;

    m_actual_err = m_robot.move();
    ASSERT_EQ(m_actual_err, m_expected_err);

    m_robot.report(m_actual_out);
    ASSERT_EQ(m_actual_out, m_expected_out);
}

TEST_F(ToyRobotTest, LeftBeforePlace)
{
    m_expected_err = E_PLACE_NOT_INVOKED;

    m_actual_err = m_robot.left();
    ASSERT_EQ(m_actual_err, m_expected_err);

    m_robot.report(m_actual_out);
    ASSERT_EQ(m_actual_out, m_expected_out);
}

TEST_F(ToyRobotTest, RightBeforePlace)
{
    m_expected_err = E_PLACE_NOT_INVOKED;

    m_actual_err = m_robot.right();
    ASSERT_EQ(m_actual_err, m_expected_err);

    m_robot.report(m_actual_out);
    ASSERT_EQ(m_actual_out, m_expected_out);
}

TEST_F(ToyRobotTest, ReportBeforePlace)
{
    m_expected_err = E_PLACE_NOT_INVOKED;

    m_actual_err = m_robot.report(m_actual_out);

    ASSERT_EQ(m_actual_err, m_expected_err);
    ASSERT_EQ(m_actual_out, m_expected_out);
}