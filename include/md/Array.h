#ifndef MULTI_DIM_CONTAINER_ARRAY
#define MULTI_DIM_CONTAINER_ARRAY

#include <algorithm>
#include <array>
#include <functional>

#include <md/detail/View.h>

namespace md {

template <class T, size_t ...N>
class Array;

template <class T, size_t N1, size_t ...N>
class Array<T, N1, N...>
{
    static constexpr size_t DIMS = 1 + sizeof...(N);
    static constexpr size_t TOTAL_SIZE = N1 * (N * ...);
public:
    template <class _T, size_t ..._N> friend
    class Array;

    using InitializerList = std::initializer_list<typename Array<T, N...>::InitializerList>;

    Array() = default;

    Array(InitializerList initializerList)
    {
        auto start = std::begin(_data);
        init(initializerList, start);
    }

    explicit constexpr Array(const std::array<T, TOTAL_SIZE>& other)
        : _data(other)
    {
    }

    explicit constexpr Array(const std::array<T, TOTAL_SIZE>&& other)
        : _data(std::move(other))
    {
    }

    explicit constexpr operator std::array<T, TOTAL_SIZE>() const
    {
        return _data;
    }

    // Element access
    constexpr auto at(size_t index)
    {
        if (index >= N1)
        {
            throw std::out_of_range("index out of bounds");
        }
        return (*this)[index];
    }

    constexpr auto at(size_t index) const
    {
        if (index >= N1)
        {
            throw std::out_of_range("index out of bounds");
        }
        return (*this)[index];
    }

    constexpr auto operator[](size_t index)
    {
        return detail::View<T, N...>{&_data[index * (N * ...)]};
    }

    constexpr auto operator[](size_t index) const
    {
        return detail::View<const T, N...>{&_data[index * (N * ...)]};
    }

    template <class IndexContainer, class = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    constexpr T& at(const IndexContainer& indexContainer)
    {
        static_assert(std::tuple_size_v<IndexContainer> == DIMS, "Index dimension mismatch");
        static_assert(std::is_integral_v<std::tuple_element_t<0, IndexContainer>>, "Index type mismatch");
        return _data.at(computeIndexWithRangeCheck(indexContainer));
    }

    template <class IndexContainer, class = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    constexpr const T& at(const IndexContainer& indexContainer) const
    {
        static_assert(std::tuple_size_v<IndexContainer> == DIMS, "Index dimension mismatch");
        static_assert(std::is_integral_v<std::tuple_element_t<0, IndexContainer>>, "Index type mismatch");
        return _data.at(computeIndexWithRangeCheck(indexContainer));
    }


    template <class IndexContainer, class = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    constexpr T& operator[](const IndexContainer& indexContainer)
    {
        static_assert(std::tuple_size_v<IndexContainer> == DIMS, "Index dimension mismatch");
        static_assert(std::is_integral_v<std::tuple_element_t<0, IndexContainer>>, "Index type mismatch");
        return _data[computeIndex(indexContainer)];
    }

    template <class IndexContainer, class = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    constexpr const T& operator[](const IndexContainer& indexContainer) const
    {
        static_assert(std::tuple_size_v<IndexContainer> == DIMS, "Index dimension mismatch");
        static_assert(std::is_integral_v<std::tuple_element_t<0, IndexContainer>>, "Index type mismatch");
        return _data[computeIndex(indexContainer)];
    }

    constexpr T* data() noexcept
    {
        return _data.data();
    }

    constexpr const T* data() const noexcept
    {
        return _data.data();
    }

    // Capacity
    constexpr size_t total_size() const noexcept
    {
        return TOTAL_SIZE;
    }

    constexpr size_t dimensions() const noexcept
    {
        return DIMS;
    }

    // Operations
    void fill(const T& value)
    {
        std::fill(std::begin(_data), std::end(_data), value);
    }

private:
    static void init(const InitializerList& initializerList, typename std::array<T, TOTAL_SIZE>::iterator& it)
    {
        if constexpr (sizeof...(N) > 1)
        {
            std::for_each(std::begin(initializerList), std::end(initializerList),
                          std::bind(Array<T, N...>::init, std::placeholders::_1, std::ref(it)));
        }
        else
        {
            std::for_each(std::begin(initializerList), std::end(initializerList),
                          [&](const auto& subList) {
                              it = std::move(std::begin(subList), std::end(subList), it);
                          });
        }
    }

    template <class IndexContainer, size_t Depth = 0>
    static constexpr size_t computeIndex(const IndexContainer& indexContainer)
    {
        constexpr auto HYPERPLANE_SIZE = (N * ...);
        if constexpr (sizeof...(N) > 1)
        {
            return std::get<Depth>(indexContainer) * HYPERPLANE_SIZE +
                   Array<T, N...>::template computeIndex<IndexContainer, Depth + 1>(indexContainer);
        }
        else
        {
            return std::get<Depth>(indexContainer) * HYPERPLANE_SIZE +
                   std::get<Depth + 1>(indexContainer);
        }
    }

    template <class IndexContainer>
    static constexpr size_t computeIndexWithRangeCheck(const IndexContainer& indexContainer)
    {
        checkRange(indexContainer, std::make_index_sequence<DIMS>{});
        return computeIndex(indexContainer);
    }

    template <class IndexContainer, size_t I1, size_t ...I>
    static constexpr void checkRange(const IndexContainer& indexContainer, std::index_sequence<I1, I...>)
    {
        if (!(std::get<I1>(indexContainer) < N1 && ((std::get<I>(indexContainer) < N) && ...)))
        {
            throw std::out_of_range{"index out of bounds"};
        }
    }

private:
    std::array<T, TOTAL_SIZE> _data;
};

template <class T, size_t N1>
class Array<T, N1>
        : public std::array<T, N1>
{
    static constexpr size_t DIMS = 1;
    static constexpr size_t TOTAL_SIZE = N1;
public:
    using InitializerList = std::initializer_list<T>;

    // Capacity
    constexpr size_t total_size() const noexcept
    {
        return TOTAL_SIZE;
    }

    constexpr size_t dimensions() const noexcept
    {
        return DIMS;
    }
};

} // namespace md

#endif // MULTI_DIM_CONTAINER_ARRAY
