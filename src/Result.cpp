#include "Result.hpp"
#include <type_traits>
#include <utility>

namespace lab6
{
template <typename T>
Result<T>::Result(T value) noexcept(std::is_nothrow_move_constructible_v<T>) : exp_(std::move(value))
{
}

template <typename T> Result<T>::Result(IndexError error) noexcept : exp_(std::unexpected(std::move(error))) {}

template <typename T> bool Result<T>::has_value() const noexcept
{
    return exp_.has_value();
} // уже готовая реализация у std::expected
template <typename T> const T& Result<T>::value() const&
{
    return exp_.value();
}
template <typename T> const IndexError& Result<T>::error() const&
{
    return exp_.error();
}

Result<void>::Result() noexcept : exp_() {}
Result<void>::Result(IndexError error) noexcept : exp_(std::unexpected(std::move(error))) {}

bool Result<void>::has_value() const noexcept
{
    return exp_.has_value();
}

void Result<void>::value() const
{
    exp_.value();
}
const IndexError& Result<void>::error() const&
{
    return exp_.error();
}

} // namespace lab6
