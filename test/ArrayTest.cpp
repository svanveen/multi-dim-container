#include <gtest/gtest.h>
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
}

TEST (ArrayTest, ConstAt)
{
    const md::Array<int, 3> arr1i{1, 2, 3};

    ASSERT_EQ(arr1i.at(0), 1);
    ASSERT_EQ(arr1i.at(1), 2);
    ASSERT_EQ(arr1i.at(2), 3);

    const md::Array<int, 2, 3> arr2i{{1, 2, 3},
                                     {4, 5, 6}};
    // dimension wise
    ASSERT_EQ(arr2i.at(0).at(0), 1);
    ASSERT_EQ(arr2i.at(1).at(0), 4);
    ASSERT_EQ(arr2i.at(1).at(2), 6);

    // pair
    ASSERT_EQ(arr2i.at(std::pair(0, 0)), 1);
    ASSERT_EQ(arr2i.at(std::pair(1, 0)), 4);
    ASSERT_EQ(arr2i.at(std::pair(1, 2)), 6);

    // tuple
    ASSERT_EQ(arr2i.at(std::tuple(0, 0)), 1);
    ASSERT_EQ(arr2i.at(std::tuple(1, 0)), 4);
    ASSERT_EQ(arr2i.at(std::tuple(1, 2)), 6);

    // array
    ASSERT_EQ(arr2i.at(std::array{0, 0}), 1);
    ASSERT_EQ(arr2i.at(std::array{1, 0}), 4);
    ASSERT_EQ(arr2i.at(std::array{1, 2}), 6);
}

TEST (ArrayTest, AccessOperator)
{
}

TEST (ArrayTest, ConstAccessOperator)
{
    const md::Array<int, 3> arr1i{1, 2, 3};

    ASSERT_EQ(arr1i[0], 1);
    ASSERT_EQ(arr1i[1], 2);
    ASSERT_EQ(arr1i[2], 3);

    const md::Array<int, 2, 3> arr2i{{1, 2, 3},
                                     {4, 5, 6}};
    // dimension wise
    ASSERT_EQ(arr2i[0][0], 1);
    ASSERT_EQ(arr2i[1][0], 4);
    ASSERT_EQ(arr2i[1][2], 6);

    // pair
    ASSERT_EQ(arr2i[std::pair(0, 0)], 1);
    ASSERT_EQ(arr2i[std::pair(1, 0)], 4);
    ASSERT_EQ(arr2i[std::pair(1, 2)], 6);

    // tuple
    ASSERT_EQ(arr2i[std::tuple(0, 0)], 1);
    ASSERT_EQ(arr2i[std::tuple(1, 0)], 4);
    ASSERT_EQ(arr2i[std::tuple(1, 2)], 6);

    // array
    ASSERT_EQ((arr2i[std::array{0, 0}]), 1);
    ASSERT_EQ((arr2i[std::array{1, 0}]), 4);
    ASSERT_EQ((arr2i[std::array{1, 2}]), 6);
}

TEST (ArrayTest, TotalSize)
{
    const md::Array<int, 3> arr1i{1, 2, 3};
    ASSERT_EQ(arr1i.total_size(), 3);

    const md::Array<int, 2, 3> arr2i{{1, 2, 3},
                                     {4, 5, 6}};
    ASSERT_EQ(arr2i.total_size(), 6);

    const md::Array<int, 2, 3, 4> arr3i{{{11, 12, 13}, {14, 15, 16}},
                                        {{21, 22, 23}, {24, 25, 26}},
                                        {{31, 32, 33}, {34, 35, 36}},
                                        {{41, 42, 43}, {44, 45, 46}}};
    ASSERT_EQ(arr3i.total_size(), 24);
}

TEST (ArrayTest, Data)
{
}
