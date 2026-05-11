#pragma once
#include "IndexError.hpp"
#include <expected>
#include <type_traits>
namespace lab_6
{
template <typename T> // Шаблон класса
// следующий класс с параметром типа Т (может быть число, вектор, строка)

class Result
{
  private:
    std::expected<T, IndexError> exp_;
    // библиотечный тип. Если операция успешна, в нём лежит T, иначе IndexError.
  public:
    using value_type = T;
    // выдает какой тип у Т, если нет ошибки
    using error_type = IndexError;

    Result() = delete;
    // удаляем конструктор - не может быть пустой объект

    Result(T value) noexcept(std::is_nothrow_move_constructible_v<T>)
        : exp_(std::move(value)) {} // Мы забираем данные у временного объекта, а не копируем их.

    Result(IndexError error) noexcept : exp_(std::unexpected(error)) {}
    // std::unexpected(error) — вспомогательная функция, создающая объект, который std::expected интерпретирует как
    // ошибку.
    bool has_value() const noexcept
    {
        return exp_.has_value();
    }

    const T& value() const& // lvalue
    {
        return exp_.value();
    }
    const IndexError& error() const
    {
        return exp_.error();
    } // только для долгоживущих тк & (ref-квалификатор)
    T&& value() && // rvalue
    {              // Возвращает rvalue-ссылку на значение, используя std::move.
        return std::move(
            exp_.value()); // Это позволяет переместить значение из временного Result наружу, избегая копирования.
    }
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
    const IndexError& error() const&;
};

} // namespace lab_6