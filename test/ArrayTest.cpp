#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <md/Array.h>

using namespace testing;

TEST (ArrayTest, InitEmpty)
{
}

TEST (ArrayTest, Init)
{
}

TEST (ArrayTest, Fill)
{
}

TEST (ArrayTest, At)
{
    md::Array<int, 3> arr1i;

    arr1i.at(0) = 1;
    arr1i.at(1) = 2;
    arr1i.at(2) = 3;

    EXPECT_THAT(arr1i, ElementsAre(1, 2, 3));

    md::Array<int, 2, 4> arr2i;

    // dimension wise
    arr2i.at(0).at(0) = 1;
    arr2i.at(1).at(0) = 2;

    // pair
    arr2i.at(std::pair(0, 1)) = 3;
    arr2i.at(std::pair(1, 1)) = 4;

    // tuple
    arr2i.at(std::tuple(0, 2)) = 5;
    arr2i.at(std::tuple(1, 2)) = 6;

    // array
    arr2i.at(std::array{0, 3}) = 7;
    arr2i.at(std::array{1, 3}) = 8;

    EXPECT_THAT(arr2i, ElementsAre(ElementsAre(1, 3, 5, 7),
                                   ElementsAre(2, 4, 6, 8)));
}

TEST (ArrayTest, ConstAt)
{
    const md::Array<int, 3> arr1i{1, 2, 3};

    EXPECT_EQ(arr1i.at(0), 1);
    EXPECT_EQ(arr1i.at(1), 2);
    EXPECT_EQ(arr1i.at(2), 3);

    const md::Array<int, 2, 3> arr2i{{1, 2, 3},
                                     {4, 5, 6}};
    // dimension wise
    EXPECT_EQ(arr2i.at(0).at(0), 1);
    EXPECT_EQ(arr2i.at(1).at(0), 4);
    EXPECT_EQ(arr2i.at(1).at(2), 6);

    // pair
    EXPECT_EQ(arr2i.at(std::pair(0, 0)), 1);
    EXPECT_EQ(arr2i.at(std::pair(1, 0)), 4);
    EXPECT_EQ(arr2i.at(std::pair(1, 2)), 6);

    // tuple
    EXPECT_EQ(arr2i.at(std::tuple(0, 0)), 1);
    EXPECT_EQ(arr2i.at(std::tuple(1, 0)), 4);
    EXPECT_EQ(arr2i.at(std::tuple(1, 2)), 6);

    // array
    EXPECT_EQ(arr2i.at(std::array{0, 0}), 1);
    EXPECT_EQ(arr2i.at(std::array{1, 0}), 4);
    EXPECT_EQ(arr2i.at(std::array{1, 2}), 6);
}

TEST (ArrayTest, AccessOperator)
{
    md::Array<int, 3> arr1i;

    arr1i[0] = 1;
    arr1i[1] = 2;
    arr1i[2] = 3;

    EXPECT_THAT(arr1i, ElementsAre(1, 2, 3));

    md::Array<int, 2, 4> arr2i;

    // dimension wise
    arr2i[0][0] = 1;
    arr2i[1][0] = 2;

    // pair
    arr2i[std::pair(0, 1)] = 3;
    arr2i[std::pair(1, 1)] = 4;

    // tuple
    arr2i[std::tuple(0, 2)] = 5;
    arr2i[std::tuple(1, 2)] = 6;

    // array
    arr2i[std::array{0, 3}] = 7;
    arr2i[std::array{1, 3}] = 8;

    EXPECT_THAT(arr2i, ElementsAre(ElementsAre(1, 3, 5, 7),
                                   ElementsAre(2, 4, 6, 8)));
}

TEST (ArrayTest, ConstAccessOperator)
{
    const md::Array<int, 3> arr1i{1, 2, 3};

    EXPECT_EQ(arr1i[0], 1);
    EXPECT_EQ(arr1i[1], 2);
    EXPECT_EQ(arr1i[2], 3);

    const md::Array<int, 2, 3> arr2i{{1, 2, 3},
                                     {4, 5, 6}};
    // dimension wise
    EXPECT_EQ(arr2i[0][0], 1);
    EXPECT_EQ(arr2i[1][0], 4);
    EXPECT_EQ(arr2i[1][2], 6);

    // pair
    EXPECT_EQ(arr2i[std::pair(0, 0)], 1);
    EXPECT_EQ(arr2i[std::pair(1, 0)], 4);
    EXPECT_EQ(arr2i[std::pair(1, 2)], 6);

    // tuple
    EXPECT_EQ(arr2i[std::tuple(0, 0)], 1);
    EXPECT_EQ(arr2i[std::tuple(1, 0)], 4);
    EXPECT_EQ(arr2i[std::tuple(1, 2)], 6);

    // array
    EXPECT_EQ((arr2i[std::array{0, 0}]), 1);
    EXPECT_EQ((arr2i[std::array{1, 0}]), 4);
    EXPECT_EQ((arr2i[std::array{1, 2}]), 6);
}

TEST (ArrayTest, TotalSize)
{
    const md::Array<int, 3> arr1i{1, 2, 3};
    EXPECT_EQ(arr1i.total_size(), 3);

    const md::Array<int, 2, 3> arr2i{{1, 2, 3},
                                     {4, 5, 6}};
    EXPECT_EQ(arr2i.total_size(), 6);

    const md::Array<int, 2, 3, 4> arr3i{{{11, 12, 13}, {14, 15, 16}},
                                        {{21, 22, 23}, {24, 25, 26}},
                                        {{31, 32, 33}, {34, 35, 36}},
                                        {{41, 42, 43}, {44, 45, 46}}};
    EXPECT_EQ(arr3i.total_size(), 24);
}

TEST (ArrayTest, Data)
{
}
