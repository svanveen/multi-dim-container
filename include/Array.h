#ifndef MULTI_DIM_CONTAINER_ARRAY
#define MULTI_DIM_CONTAINER_ARRAY

#include <algorithm>
#include <array>

namespace md {

template <class T, size_t ...N>
class Array;

template <class T, size_t N1, size_t ...N>
class Array<T, N1, N...>
        : public std::array<Array<T, N...>, N1>
{
    using Base = std::array<Array<T, N...>, N1>;
    using Type = typename Base::value_type;
public:
    Array() = default;

    Array(std::initializer_list<Type> init)
    {
        std::move(std::begin(init), std::end(init), std::begin(*this));
    }

};

template <class T, size_t N1>
class Array<T, N1>
        : public std::array<T, N1>
{
    using Base = std::array<T, N1>;
public:
    Array() = default;

    Array(std::initializer_list<T> init)
    {
        std::move(std::begin(init), std::end(init), std::begin(*this));
    }

};

} // namespace md

#endif // MULTI_DIM_CONTAINER_ARRAY
