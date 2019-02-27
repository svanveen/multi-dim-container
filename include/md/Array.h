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

    template <class IndexContainer, size_t I = 0, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    constexpr T& at(const IndexContainer& index)
    {
        static_assert(std::tuple_size_v<IndexContainer> == dimensions + I, "Index dimension mismatch");
        static_assert(std::is_integral_v<std::tuple_element_t<I, IndexContainer>>, "Index type mismatch");
        return Base::at(std::get<I>(index)).template at<IndexContainer, I + 1>(index);
    }

    template <class IndexContainer, size_t I = 0, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    constexpr const T& at(const IndexContainer& index) const
    {
        static_assert(std::tuple_size_v<IndexContainer> == dimensions + I, "Index dimension mismatch");
        static_assert(std::is_integral_v<std::tuple_element_t<I, IndexContainer>>, "Index type mismatch");
        return Base::at(std::get<I>(index)).template at<IndexContainer, I + 1>(index);
    }

    using Base::operator[];

    template <class IndexContainer, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    constexpr T& operator[](const IndexContainer& index)
    {
        return at(index);
    }

    template <class IndexContainer, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    constexpr const T& operator[](const IndexContainer& index) const
    {
        return at(index);
    }

    constexpr T *data() noexcept
    {
        return Base::front().data();
    }

    constexpr const T *data() const noexcept
    {
        return Base::front().data();
    }

    // Capacity
    constexpr size_t total_size() const noexcept
    {
        return N1 * (N * ...);
    }

    // Operations
    void fill(const T& value)
    {
        std::for_each(std::begin(*this), std::end(*this), std::bind(&Type::fill, std::placeholders::_1, value));
    }

    static constexpr size_t dimensions = 1 + sizeof...(N);
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

    template <class IndexContainer, size_t I = 0, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    constexpr T& at(const IndexContainer& index)
    {
        static_assert(std::tuple_size_v<IndexContainer> == dimensions + I, "Index dimension mismatch");
        static_assert(std::is_integral_v<std::tuple_element_t<I, IndexContainer>>, "Index type mismatch");
        return Base::at(std::get<I>(index));
    }

    template <class IndexContainer, size_t I = 0, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    constexpr const T& at(const IndexContainer& index) const
    {
        static_assert(std::tuple_size_v<IndexContainer> == dimensions + I, "Index dimension mismatch");
        static_assert(std::is_integral_v<std::tuple_element_t<I, IndexContainer>>, "Index type mismatch");
        return Base::at(std::get<I>(index));
    }

    using Base::operator[];

    template <class IndexContainer, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    constexpr T& operator[](const IndexContainer& index)
    {
        return at(index);
    }

    template <class IndexContainer, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    constexpr const T& operator[](const IndexContainer& index) const
    {
        return at(index);
    }

    static constexpr size_t dimensions = 1;
};

} // namespace md

#endif // MULTI_DIM_CONTAINER_ARRAY
