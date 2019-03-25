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

    // Element access

    template <class IndexContainer, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    constexpr T& at(const IndexContainer& index)
    {
        static_assert(std::tuple_size_v<IndexContainer> == DIMS, "Index dimension mismatch");
        static_assert(std::is_integral_v<std::tuple_element_t<0, IndexContainer>>, "Index type mismatch");
        return _data.at(computeIndex(index));
    }

    template <class IndexContainer, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    constexpr const T& at(const IndexContainer& index) const
    {
        static_assert(std::tuple_size_v<IndexContainer> == DIMS, "Index dimension mismatch");
        static_assert(std::is_integral_v<std::tuple_element_t<0, IndexContainer>>, "Index type mismatch");
        return _data.at(computeIndex(index));
    }


    template <class IndexContainer, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    constexpr T& operator[](const IndexContainer& index)
    {
        static_assert(std::tuple_size_v<IndexContainer> == DIMS, "Index dimension mismatch");
        static_assert(std::is_integral_v<std::tuple_element_t<0, IndexContainer>>, "Index type mismatch");
        return _data[computeIndex(index)];
    }

    template <class IndexContainer, class Unused = std::enable_if_t<!std::is_integral_v<IndexContainer>>>
    constexpr const T& operator[](const IndexContainer& index) const
    {
        static_assert(std::tuple_size_v<IndexContainer> == DIMS, "Index dimension mismatch");
        static_assert(std::is_integral_v<std::tuple_element_t<0, IndexContainer>>, "Index type mismatch");
        return _data[computeIndex(index)];
    }

    constexpr T *data() noexcept
    {
        return _data.data();
    }

    constexpr const T *data() const noexcept
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
        std::for_each(std::begin(initializerList), std::end(initializerList),
                      std::bind(Array<T, N...>::init, std::placeholders::_1, std::ref(it)));
    }

    template <class IndexContainer, size_t Depth = 0>
    static constexpr size_t computeIndex(const IndexContainer& indexContainer)
    {
        if constexpr (sizeof...(N) > 0) {
            return std::get<Depth>(indexContainer) * (TOTAL_SIZE / N1) +
                   Array<T, N...>::template computeIndex<IndexContainer, Depth + 1>(indexContainer);
        }
        else {
            return std::get<Depth>(indexContainer) * (TOTAL_SIZE / N1) +
                   std::get<Depth + 1>(indexContainer);
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

    template <class _T, size_t ..._N> friend
    class Array;

    Array() = default;

    Array(std::initializer_list<T> initializerList)
    {
        std::move(std::begin(initializerList), std::end(initializerList), std::begin(*this));
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

private:
    static void init(const std::initializer_list<T>& initializerList, typename std::array<T, N1>::iterator& it)
    {
        it = std::move(std::begin(initializerList), std::end(initializerList), it);
    }

    template <class IndexContainer, size_t Depth = 0>
    static constexpr size_t computeIndex(const IndexContainer& indexContainer)
    {
        return std::get<Depth>(indexContainer);
    }
};

} // namespace md

#endif // MULTI_DIM_CONTAINER_ARRAY
