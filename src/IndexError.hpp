#pragma once
#include <cstdint>

namespace lab_6
{

enum class IndexError : uint8_t  //строго типизированное перечисление
{  // задаёт базовый тип для хранения значений перечисления. uint8_t — беззнаковое 8-битное целое
    DocumentAlreadyExists, // документ с таким id уже есть
    DocumentNotFound,      // документ с таким id не найден
    InvalidDocument,
    InvalidId,               // id равен 0 или некорректен
    EmptyWord,               // поиск по пустому слову
    TransactionNotCommitted, // (опционально) транзакция не была зафиксированa
    TransactionAlreadyActive,
    TransactionAlreadyCompleted,
    TransactionInvalidState,
};

} // namespace lab_6
//Имена ошибок не попадают в окружающее пространство имён. Нужно писать IndexError::DocumentAlreadyExists.
//Компилятор не позволит тебе случайно сравнить ошибку с обычным числом int. Это защищает от глупых багов.
//Нет неявного преобразования в целые типы.
//Приходится явно приводить, если нужен числовой код: static_cast<int>(err).