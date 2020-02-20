#ifndef MULTI_DIM_CONTAINER_VIEW
#define MULTI_DIM_CONTAINER_VIEW

namespace md::detail {

template <class T, size_t ...N>
class View;

template <class T, size_t ...N>
class Iterator;

template <class T, size_t N1, size_t ...N>
class View<T, N1, N...>
{
public:
    using value_type = View<T, N...>;
    using iterator = Iterator<T, N1, N...>;
    using const_iterator = Iterator<const T, N1, N...>;

public:
    explicit View(T* data)
        : _data(data)
    {
    }

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
        return View<T, N...>{&_data[index * (N * ...)]};
    }

    constexpr auto operator[](size_t index) const
    {
        return View<const T, N...>{&_data[index * (N * ...)]};
    }

    iterator begin()
    {
        return _data;
    }

    const_iterator begin() const
    {
        return _data;
    }

    iterator end()
    {
        return std::next(_data + (N1 * (N * ...)));
    }

    const_iterator end() const
    {
        return std::next(_data + (N1 * (N * ...)));
    }


private:
    T* _data;
};

template <class T, size_t N1>
class View<T, N1>
{
public:
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;

public:
    explicit View(T* data)
        : _data(data)
    {}

    constexpr T& at(size_t index)
    {
        return const_cast<T&>(static_cast<const View<T, N1>>(*this).at(index));
    }

    constexpr const T& at(size_t index) const
    {
        if (index >= N1)
        {
            throw std::out_of_range("index out of bounds");
        }
        return (*this)[index];
    }

    constexpr T& operator[](size_t index)
    {
        return const_cast<T&>(static_cast<const View<T, N1>>(*this)[index]);
    }

    constexpr const T& operator[](size_t index) const
    {
        return _data[index];
    }

    iterator begin()
    {
        return _data;
    }

    const_iterator begin() const
    {
        return _data;
    }

    iterator end()
    {
        return std::next(_data + N1);
    }

    const_iterator end() const
    {
        return std::next(_data + N1);
    }

private:
    T* _data;
};

template <class T, size_t N1, size_t ...N>
class Iterator<T, N1, N...>
{
public:
    using value_type = View<T, N...>;

    explicit Iterator(T* data)
        : _data(data)
    {}

    constexpr View<T, N...> operator*()
    {
        return View<T, N...>{_data};
    }

    Iterator& operator++()
    {
        std::next(_data, (N * ...));
        return *this;
    }

    bool operator!=(const Iterator& other) const
    {
        return _data != other._data;
    }

private:
    T* _data;
};

}

#endif //MULTI_DIM_CONTAINER_VIEW
