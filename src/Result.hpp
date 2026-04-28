#pragma once
#include <expected>
#include <string>
#include <type_traits>

namespace lab6
{
struct IndexError
{
    std::string message;
}; // строка оповещения об ошибке

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

    Result(T value) noexcept(std::is_nothrow_move_constructible_v<T>);
    // если noexcept(false) - разрешены исключения(в итоге Result не создаем)
    Result(IndexError error) noexcept;

    bool has_value() const noexcept;

    const T& value() const&;
    const IndexError& error() const&; // только для долгоживущих тк & (ref-квалификатор)
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

} // namespace lab6