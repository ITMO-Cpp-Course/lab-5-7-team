#pragma once
#include <cstdint>

namespace lab_6 {

    enum class IndexError : uint8_t {
        DocumentAlreadyExists,   // документ с таким id уже есть
        DocumentNotFound,// документ с таким id не найден
        InvalidDocument,
        InvalidId,               // id равен 0 или некорректен
        EmptyWord,               // поиск по пустому слову
        TransactionNotCommitted,  // (опционально) транзакция не была зафиксированa
        TransactionAlreadyActive,
        TransactionAlreadyCompleted,
        TransactionInvalidState,
    };

} // namespace lab_6