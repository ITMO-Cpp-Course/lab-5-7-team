#pragma once
#include <cstdint>

namespace lab_6
{

enum class IndexError : uint8_t // строго типизированное перечисление
{ // задаёт базовый тип для хранения значений перечисления. uint8_t — беззнаковое 8-битное целое
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
