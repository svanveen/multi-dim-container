#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <md/Array.h>

using namespace testing;

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
    const md::Array<int, 3> arr1i{1, 2, 3};
    EXPECT_THAT(arr1i, ElementsAre(1, 2, 3));

    const md::Array<int, 2, 3> arr2i{{1, 2, 3},
                                     {4, 5, 6}};
//    EXPECT_THAT(arr2i, ElementsAre(ElementsAre(1, 2, 3),
//                                   ElementsAre(4, 5, 6)));
}

TEST (ArrayTest, Fill)
{
    md::Array<int, 3> arr1i;
    arr1i.fill(42);
    EXPECT_THAT(arr1i, Each(42));

    md::Array<int, 2, 3> arr2i;
    arr2i.fill(42);
//    EXPECT_THAT(arr2i, Each(Each(42)));

    md::Array<int, 2, 3, 5> arr3i;
    arr3i.fill(42);
//    EXPECT_THAT(arr3i, Each(Each(Each(42))));
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
//    arr2i.at(0).at(0) = 1;
//    arr2i.at(1).at(0) = 2;

    // pair
    arr2i.at(std::pair(0, 1)) = 3;
    arr2i.at(std::pair(1, 1)) = 4;

    // tuple
    arr2i.at(std::tuple(0, 2)) = 5;
    arr2i.at(std::tuple(1, 2)) = 6;

    // array
    arr2i.at(std::array{0, 3}) = 7;
    arr2i.at(std::array{1, 3}) = 8;

//    EXPECT_THAT(arr2i, ElementsAre(ElementsAre(1, 3, 5, 7),
//                                   ElementsAre(2, 4, 6, 8)));
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
//    EXPECT_EQ(arr2i.at(0).at(0), 1);
//    EXPECT_EQ(arr2i.at(1).at(0), 4);
//    EXPECT_EQ(arr2i.at(1).at(2), 6);

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
//    arr2i[0][0] = 1;
//    arr2i[1][0] = 2;

    // pair
    arr2i[std::pair(0, 1)] = 3;
    arr2i[std::pair(1, 1)] = 4;

    // tuple
    arr2i[std::tuple(0, 2)] = 5;
    arr2i[std::tuple(1, 2)] = 6;

    // array
    arr2i[std::array{0, 3}] = 7;
    arr2i[std::array{1, 3}] = 8;

//    EXPECT_THAT(arr2i, ElementsAre(ElementsAre(1, 3, 5, 7),
//                                   ElementsAre(2, 4, 6, 8)));
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
//    EXPECT_EQ(arr2i[0][0], 1);
//    EXPECT_EQ(arr2i[1][0], 4);
//    EXPECT_EQ(arr2i[1][2], 6);

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

TEST(ArrayTest, RangeCheck)
{
    md::Array<int, 2, 4> arr2i;
    EXPECT_THROW(arr2i.at(std::pair{3, 1}), std::out_of_range);
    EXPECT_THROW(arr2i.at(std::tuple{4, 5}), std::out_of_range);
    EXPECT_THROW(arr2i.at(std::array{1, 4}), std::out_of_range);

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

    const md::Array<int, 2, 3, 4> arr3i{{{11, 12, 13}, {14, 15, 16}},
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

    const md::Array<int, 2, 3, 4> arr3i{{{11, 12, 13}, {14, 15, 16}},
                                        {{21, 22, 23}, {24, 25, 26}},
                                        {{31, 32, 33}, {34, 35, 36}},
                                        {{41, 42, 43}, {44, 45, 46}}};
    EXPECT_EQ(arr3i.dimensions(), 3);
}

TEST (ArrayTest, Data)
{
    md::Array<int, 3> arr1i{1, 2, 3};
    EXPECT_EQ(reinterpret_cast<size_t>(arr1i.data()), reinterpret_cast<size_t>(&arr1i));
    EXPECT_TRUE((std::is_same_v<decltype(arr1i.data()), int *>));

    md::Array<int, 2, 3> arr2i{{1, 2, 3},
                               {4, 5, 6}};
    EXPECT_EQ(reinterpret_cast<size_t>(arr2i.data()), reinterpret_cast<size_t>(&arr2i));
    EXPECT_TRUE((std::is_same_v<decltype(arr2i.data()), int *>));
}

TEST (ArrayTest, ConstData)
{
    const md::Array<int, 3> arr1i{1, 2, 3};
    EXPECT_EQ(reinterpret_cast<size_t>(arr1i.data()), reinterpret_cast<size_t>(&arr1i));
    EXPECT_TRUE((std::is_same_v<decltype(arr1i.data()), const int *>));

    const md::Array<int, 2, 3> arr2i{{1, 2, 3},
                                     {4, 5, 6}};
    EXPECT_EQ(reinterpret_cast<size_t>(arr2i.data()), reinterpret_cast<size_t>(&arr2i));
    EXPECT_TRUE((std::is_same_v<decltype(arr2i.data()), const int *>));
}
