#ifndef MULTI_DIM_CONTAINER_ARRAY
#define MULTI_DIM_CONTAINER_ARRAY

#include <algorithm>
#include <array>
#include <functional>

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

    // Element access
    using Base::at;

    template <class IndexContainer, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    T& at(const IndexContainer& index)
    {
        return Base::at(get_head(index))[get_tail(index)];
    }

    template <class IndexContainer, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    const T& at(const IndexContainer& index) const
    {
        return Base::at(get_head(index))[get_tail(index)];
    }

    using Base::operator[];

    template <class IndexContainer, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    T& operator[](const IndexContainer& index)
    {
        return at(index);
    }

    template <class IndexContainer, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    const T& operator[](const IndexContainer& index) const
    {
        return at(index);
    }

    void fill(const T& value)
    {
        std::for_each(std::begin(*this), std::end(*this), std::bind(&Type::fill, std::placeholders::_1, value));
    }

private:
    template <class IndexContainer>
    static auto get_head(const IndexContainer& index)
    {
        return std::get<0>(index);
    }

    template <class IndexContainer>
    static auto get_tail(const IndexContainer& index)
    {
        return get_tail(index, std::make_index_sequence<std::tuple_size<IndexContainer>() - 1>());
    }

    template <class IndexContainer, size_t ...Index>
    static auto get_tail(const IndexContainer& index, std::index_sequence<Index...>)
    {
        return std::make_tuple(std::get<Index + 1>(index)...);
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

    // Element access
    using Base::at;

    template <class IndexContainer, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    T& at(const IndexContainer& index)
    {
        return Base::at(std::get<0>(index));
    }

    template <class IndexContainer, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    const T& at(const IndexContainer& index) const
    {
        return Base::at(std::get<0>(index));
    }

    using Base::operator[];

    template <class IndexContainer, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    T& operator[](const IndexContainer& index)
    {
        return at(index);
    }

    template <class IndexContainer, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    const T& operator[](const IndexContainer& index) const
    {
        return at(index);
    }
};

} // namespace md

#endif // MULTI_DIM_CONTAINER_ARRAY
