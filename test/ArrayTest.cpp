#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <md/Array.h>

using namespace testing;

template <class T, size_t ...N>
auto toArray(const md::Array<T, N...>& arr)
{
    return static_cast<std::array<T, (N * ...)>>(arr);
}

#define ExpectElementsAre(value, expected...) \
    EXPECT_THAT(toArray(value), ElementsAre(expected));

#define ExpectAllElementsAre(value, expected) \
    EXPECT_THAT(toArray(value), Each(expected));

TEST (ArrayTest, InitEmpty)
{
    // check different types 1D
    md::Array<double, 1> arr1d;
    md::Array<float, 1> arr1f;
    md::Array<int, 1> arr1i;
    md::Array<char, 1> arr1c;
    md::Array<std::string, 1> arr1s;

    // check different types 2D
    md::Array<double, 2, 2> arr2d;
    md::Array<float, 2, 2> arr2f;
    md::Array<int, 2, 2> arr2i;
    md::Array<char, 2, 2> arr2c;
    md::Array<std::string, 2, 2> arr2s;

    // check different dimensions
    md::Array<int, 3, 4, 5> arr3i;
    md::Array<int, 4, 2, 3, 5> arr4i;
    md::Array<int, 5, 4, 3, 2, 1> arr5i;

    /// no asserts here, only for compile checking
}

TEST (ArrayTest, Init)
{
    {
        const md::Array<int, 3> arr1i{1, 2, 3};
        EXPECT_THAT(arr1i, ElementsAre(1, 2, 3));

        const md::Array<int, 2, 3> arr2i{{1, 2, 3},
                                         {4, 5, 6}};

        ExpectElementsAre(arr2i, 1, 2, 3, 4, 5, 6);
    }
    {
        const std::array<int, 6> data{1, 2, 3, 4, 5, 6};

        const md::Array<int, 6> arr1i {data};
        ExpectElementsAre(arr1i, 1, 2, 3, 4, 5, 6);

        const md::Array<int, 2, 3> arr2i {data};
        ExpectElementsAre(arr2i, 1, 2, 3, 4, 5, 6);
    }
    {
        const md::Array<int, 6> arr1i {std::array<int, 6>{1, 2, 3, 4, 5, 6}};
        ExpectElementsAre(arr1i, 1, 2, 3, 4, 5, 6);

        const md::Array<int, 2, 3> arr2i {std::array<int, 6>{1, 2, 3, 4, 5, 6}};
        ExpectElementsAre(arr2i, 1, 2, 3, 4, 5, 6);
    }
}

TEST (ArrayTest, StdArrayCast)
{
    const md::Array<int, 3> arr1i{1, 2, 3};
    EXPECT_EQ((static_cast<std::array<int, 3>>(arr1i)), (std::array<int, 3>{1, 2, 3}));

    const md::Array<int, 2, 3> arr2i{{1, 2, 3},
                                     {4, 5, 6}};
    EXPECT_EQ((static_cast<std::array<int, 6>>(arr2i)), (std::array<int, 6>{1, 2, 3, 4, 5, 6}));
}

TEST (ArrayTest, Fill)
{
    md::Array<int, 3> arr1i;
    arr1i.fill(42);
    EXPECT_THAT(arr1i, Each(42));

    md::Array<int, 2, 3> arr2i;
    arr2i.fill(42);
    ExpectAllElementsAre(arr2i, 42);

    md::Array<int, 2, 3, 5> arr3i;
    arr3i.fill(42);
    ExpectAllElementsAre(arr3i, 42);
}

TEST (ArrayTest, At)
{
    md::Array<int, 3> arr1i;

    arr1i.at(0) = 1;
    arr1i.at(1) = 2;
    arr1i.at(2) = 3;

    EXPECT_THAT(arr1i, ElementsAre(1, 2, 3));

    md::Array<int, 2, 3> arr2i;

    // pair
    arr2i.at(std::pair(0, 0)) = 3;
    arr2i.at(std::pair(1, 0)) = 4;

    // tuple
    arr2i.at(std::tuple(0, 1)) = 5;
    arr2i.at(std::tuple(1, 1)) = 6;

    // array
    arr2i.at(std::array{0, 2}) = 7;
    arr2i.at(std::array{1, 2}) = 8;

    ExpectElementsAre(arr2i, 3, 5, 7, 4, 6, 8);
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

    ExpectElementsAre(arr2i, 1, 3, 5, 7, 2, 4, 6, 8);

    md::Array<int, 3, 2, 2> arr3i;
    // dimension wise
    arr3i[0][0][0] = 11;
    arr3i[0][0][1] = 12;
    arr3i[0][1][0] = 13;
    arr3i[0][1][1] = 14;

    // tuple
    arr3i[std::tuple(1, 0, 0)] = 21;
    arr3i[std::tuple(1, 0, 1)] = 22;
    arr3i[std::tuple(1, 1, 0)] = 23;
    arr3i[std::tuple(1, 1, 1)] = 24;

    // array
    arr3i[std::array{2, 0, 0}] = 31;
    arr3i[std::array{2, 0, 1}] = 32;
    arr3i[std::array{2, 1, 0}] = 33;
    arr3i[std::array{2, 1, 1}] = 34;

    ExpectElementsAre(arr3i, 11, 12, 13, 14, 21, 22, 23, 24, 31, 32, 33, 34);
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

    const md::Array<int, 2, 4, 3> arr3i{{{11, 12, 13}, {14, 15, 16}, {21, 22, 23}, {24, 25, 26}},
                                        {{31, 32, 33}, {34, 35, 36}, {41, 42, 43}, {44, 45, 46}}};
    // dimension wise
    EXPECT_EQ(arr3i[0][0][0], 11);
    EXPECT_EQ(arr3i[1][0][1], 32);
    EXPECT_EQ(arr3i[1][3][2], 46);

    // tuple
    EXPECT_EQ(arr3i[std::tuple(0, 0, 0)], 11);
    EXPECT_EQ(arr3i[std::tuple(1, 0, 1)], 32);
    EXPECT_EQ(arr3i[std::tuple(1, 3, 2)], 46);

    // array
    EXPECT_EQ((arr3i[std::array{0, 0, 0}]), 11);
    EXPECT_EQ((arr3i[std::array{1, 0, 1}]), 32);
    EXPECT_EQ((arr3i[std::array{1, 3, 2}]), 46);
}

TEST(ArrayTest, RangeCheck)
{
    md::Array<int, 2, 4> arr2i;

    EXPECT_THROW(arr2i.at(3).at(6), std::out_of_range);
    EXPECT_THROW(arr2i.at(std::pair{3, 1}), std::out_of_range);
    EXPECT_THROW(arr2i.at(std::tuple{4, 5}), std::out_of_range);
    EXPECT_THROW(arr2i.at(std::array{1, 4}), std::out_of_range);

    EXPECT_NO_THROW(arr2i[3][6]);
    EXPECT_NO_THROW((arr2i[std::pair{3, 1}]));
    EXPECT_NO_THROW((arr2i[std::tuple{4, 5}]));
    EXPECT_NO_THROW((arr2i[std::array{1, 4}]));
}

TEST (ArrayTest, TotalSize)
{
    const md::Array<int, 3> arr1i{1, 2, 3};
    EXPECT_EQ(arr1i.total_size(), 3);

    const md::Array<int, 2, 3> arr2i{{1, 2, 3},
                                     {4, 5, 6}};
    EXPECT_EQ(arr2i.total_size(), 6);

    const md::Array<int, 4, 2, 3> arr3i{{{11, 12, 13}, {14, 15, 16}},
                                        {{21, 22, 23}, {24, 25, 26}},
                                        {{31, 32, 33}, {34, 35, 36}},
                                        {{41, 42, 43}, {44, 45, 46}}};
    EXPECT_EQ(arr3i.total_size(), 24);
}

TEST (ArrayTest, Dimensions)
{
    const md::Array<int, 3> arr1i{1, 2, 3};
    EXPECT_EQ(arr1i.dimensions(), 1);

    const md::Array<int, 2, 3> arr2i{{1, 2, 3},
                                     {4, 5, 6}};
    EXPECT_EQ(arr2i.dimensions(), 2);

    const md::Array<int, 4, 2, 3> arr3i{{{11, 12, 13}, {14, 15, 16}},
                                        {{21, 22, 23}, {24, 25, 26}},
                                        {{31, 32, 33}, {34, 35, 36}},
                                        {{41, 42, 43}, {44, 45, 46}}};
    EXPECT_EQ(arr3i.dimensions(), 3);
}

TEST (ArrayTest, Data)
{
    md::Array<int, 3> arr1i{1, 2, 3};
    EXPECT_EQ(arr1i.data()[0], 1);
    EXPECT_EQ(arr1i.data()[1], 2);
    EXPECT_EQ(arr1i.data()[2], 3);
    EXPECT_TRUE((std::is_same_v<decltype(arr1i.data()), int*>));

    md::Array<int, 2, 3> arr2i{{1, 2, 3},
                               {4, 5, 6}};
    EXPECT_EQ(arr1i.data()[0], 1);
    EXPECT_EQ(arr1i.data()[1], 2);
    EXPECT_EQ(arr1i.data()[2], 3);
    EXPECT_TRUE((std::is_same_v<decltype(arr2i.data()), int*>));
}

TEST (ArrayTest, ConstData)
{
    const md::Array<int, 3> arr1i{1, 2, 3};
    EXPECT_EQ(arr1i.data()[0], 1);
    EXPECT_EQ(arr1i.data()[1], 2);
    EXPECT_EQ(arr1i.data()[2], 3);
    EXPECT_TRUE((std::is_same_v<decltype(arr1i.data()), const int*>));

    const md::Array<int, 2, 3> arr2i{{1, 2, 3},
                                     {4, 5, 6}};
    EXPECT_EQ(arr1i.data()[0], 1);
    EXPECT_EQ(arr1i.data()[1], 2);
    EXPECT_EQ(arr1i.data()[2], 3);
    EXPECT_TRUE((std::is_same_v<decltype(arr2i.data()), const int*>));
}
