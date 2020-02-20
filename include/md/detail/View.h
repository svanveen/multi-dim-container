#ifndef MULTI_DIM_CONTAINER_VIEW
#define MULTI_DIM_CONTAINER_VIEW

namespace md::detail {

template <class T, size_t ...N>
class View;

template <class T, size_t N1, size_t ...N>
class View<T, N1, N...>
{
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

private:
    T* _data;
};

template <class T, size_t N1>
class View<T, N1>
{
public:
    explicit View(T* data)
        : _data(data)
    {
    }

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

private:
    T* _data;
};

}

#endif //MULTI_DIM_CONTAINER_VIEW
