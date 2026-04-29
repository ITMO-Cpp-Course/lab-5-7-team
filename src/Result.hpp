#pragma once
#include <expected>
#include <type_traits>
#include "IndexError.hpp"

namespace lab_6
{
    template <typename T>
    // следующий класс с параметром типа Т (может быть число, вектор, строка)

    class Result
    {
    private:
        std::expected<T, IndexError> exp_;

    public:
        using value_type = T;
        // выдает какой тип у Т, если нет ошибки
        using error_type = IndexError;

        Result() = delete;
        // удаляем конструктор - не может быть пустой объект

        Result(T value) noexcept(std::is_nothrow_move_constructible_v<T>) : exp_(std::move(value))
        {
        }

        // если noexcept(false) - разрешены исключения(в итоге Result не создаем)
        Result(IndexError error) noexcept : exp_(std::unexpected(error))
        {
        }

        bool has_value() const noexcept { return exp_.has_value(); }

        const T& value() const & { return exp_.value(); }
        const IndexError& error() const { return exp_.error(); } // только для долгоживущих тк & (ref-квалификатор)
        T&& value() && { return std::move(exp_.value()); }
    };

    template <>
    // обязательно для написания для уточнения шаблона следующего класса
    class Result<void>
    {
    private:
        std::expected<void, IndexError> exp_;

    public:
        using value_type = void;
        using error_type = IndexError;

        Result() noexcept;
        // наоборот, создаем пустой результат
        Result(IndexError error) noexcept;

        bool has_value() const noexcept;

        void value() const;
        const IndexError& error() const &;
    };
} // namespace lab6
