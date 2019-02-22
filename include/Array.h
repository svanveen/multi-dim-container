#ifndef MULTI_DIM_CONTAINER_ARRAY
#define MULTI_DIM_CONTAINER_ARRAY

#include <array>

namespace md {

template <class T, size_t ...N>
class Array;

template <class T, size_t N1, size_t ...N>
class Array<T, N1, N...>
        : public std::array<Array<T, N...>, N1>
{

};

template <class T, size_t N1>
class Array<T, N1>
        : public std::array<T, N1>
{

};

} // namespace md

#endif // MULTI_DIM_CONTAINER_ARRAY
