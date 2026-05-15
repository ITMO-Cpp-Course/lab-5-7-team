#pragma once
#include "IndexError.hpp"
#include <expected>
#include <type_traits>
namespace lab_6
{
template <typename T>

class Result
{
  private:
    std::expected<T, IndexError> exp_;

  public:
    using value_type = T;
    using error_type = IndexError;

    Result() = delete;

    Result(T value) noexcept(std::is_nothrow_move_constructible_v<T>) : exp_(std::move(value)) {}

    Result(IndexError error) noexcept : exp_(std::unexpected(error)) {}
    bool has_value() const noexcept
    {
        return exp_.has_value();
    }

    const T& value() const& // lvalue
    {
        return exp_.value();
    }
    const IndexError& error() const&
    {
        return exp_.error();
    }
    T&& value() && // rvalue
    {
        return std::move(exp_.value());
    }
};

template <> class Result<void>
{
  private:
    std::expected<void, IndexError> exp_;

  public:
    using value_type = void;
    using error_type = IndexError;

    Result() noexcept;
    Result(IndexError error) noexcept;
    bool has_value() const noexcept;
    const IndexError& error() const&;
};

} // namespace lab_6