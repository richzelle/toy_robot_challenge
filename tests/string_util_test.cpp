#include <gtest/gtest.h>
#include <iostream>
#include <tuple>

#include "string_util.h"

/******************************************/
/* Base Test Fixture                      */
/******************************************/
class TrimTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        m_actual_out = "";
        m_expected_out = "";
        m_input = "";
    }

    std::string m_input;

    std::string m_actual_out;
    std::string m_expected_out;
};

/******************************************/
/* Left Trim                              */
/******************************************/
class LeftTrimTest : public TrimTest,
                     public ::testing::WithParamInterface<std::tuple<std::string, std::string, std::string>>
{
};

TEST_P(LeftTrimTest, Parse)
{
    std::tuple<std::string, std::string, std::string> params = GetParam();
    m_input = std::get<1>(params);
    m_expected_out = std::get<2>(params);

    m_actual_out = string_util::ltrim(m_input);
    ASSERT_EQ(m_actual_out, m_expected_out);
}

INSTANTIATE_TEST_SUITE_P(
    LeftTrim,
    LeftTrimTest,
    ::testing::Values(
        std::make_tuple("EmptyString", "", ""),
        std::make_tuple("WhiteSpaceOnly", " ", ""),
        std::make_tuple("WhitestringAtStart", " string", "string"),
        std::make_tuple("WhitestringAtMiddle", "string string", "string string"),
        std::make_tuple("WhitestringAtEnd", "string ", "string "),
        std::make_tuple("WhitestringOnBothSides", " string ", "string "),
        std::make_tuple("NoWhitestring", "string", "string"),
        std::make_tuple("Tab", "\tstring", "string"),
        std::make_tuple("NewLine", "\nstring", "string")),
    [](const testing::TestParamInfo<LeftTrimTest::ParamType> &info)
    {
        return std::get<0>(info.param);
    });

/******************************************/
/* Right Trim                             */
/******************************************/
class RightTrimTest : public TrimTest,
                      public ::testing::WithParamInterface<std::tuple<std::string, std::string, std::string>>
{
};

TEST_P(RightTrimTest, Parse)
{
    std::tuple<std::string, std::string, std::string> params = GetParam();
    m_input = std::get<1>(params);
    m_expected_out = std::get<2>(params);

    m_actual_out = string_util::rtrim(m_input);
    ASSERT_EQ(m_actual_out, m_expected_out);
}

INSTANTIATE_TEST_SUITE_P(
    RightTrim,
    RightTrimTest,
    ::testing::Values(
        std::make_tuple("EmptyString", "", ""),
        std::make_tuple("WhiteSpaceOnly", " ", ""),
        std::make_tuple("WhitestringAtStart", " string", " string"),
        std::make_tuple("WhitestringAtMiddle", "string string", "string string"),
        std::make_tuple("WhitestringAtEnd", "string ", "string"),
        std::make_tuple("WhitestringOnBothSides", " string ", " string"),
        std::make_tuple("NoWhitestring", "string", "string"),
        std::make_tuple("Tab", "string\t", "string"),
        std::make_tuple("NewLine", "string\n", "string")),
    [](const testing::TestParamInfo<RightTrimTest::ParamType> &info)
    {
        return std::get<0>(info.param);
    });

/******************************************/
/* Trim                                   */
/******************************************/
class LeftRightTrimTest : public TrimTest,
                          public ::testing::WithParamInterface<std::tuple<std::string, std::string, std::string>>
{
};

TEST_P(LeftRightTrimTest, Parse)
{
    std::tuple<std::string, std::string, std::string> params = GetParam();
    m_input = std::get<1>(params);
    m_expected_out = std::get<2>(params);

    m_actual_out = string_util::trim(m_input);
    ASSERT_EQ(m_actual_out, m_expected_out);
}

INSTANTIATE_TEST_SUITE_P(
    LeftRightTrim,
    LeftRightTrimTest,
    ::testing::Values(
        std::make_tuple("EmptyString", "", ""),
        std::make_tuple("WhiteSpaceOnly", " ", ""),
        std::make_tuple("WhitestringAtStart", " string", "string"),
        std::make_tuple("WhitestringAtMiddle", "string string", "string string"),
        std::make_tuple("WhitestringAtEnd", "string ", "string"),
        std::make_tuple("WhitestringOnBothSides", " string ", "string"),
        std::make_tuple("NoWhitestring", "string", "string"),
        std::make_tuple("Tab", "\tstring\t", "string"),
        std::make_tuple("NewLine", "\nstring\n", "string")),
    [](const testing::TestParamInfo<LeftRightTrimTest::ParamType> &info)
    {
        return std::get<0>(info.param);
    });