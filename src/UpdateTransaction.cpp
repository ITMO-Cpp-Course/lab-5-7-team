#include "UpdateTransaction.hpp"
#include "DocumentBuilder.hpp"
#include "IndexStore.hpp"
#include "InvertedIndex.hpp"

namespace lab_6
{
UpdateTransaction::UpdateTransaction(IndexStore& store) : store_(store), draft_(store.invertedIndex_)
{
    store_.transactionActive_ = true;
}
} // не помечен noexcept, потому что копирование индекса может вызвать исключение (выделение памяти)

UpdateTransaction::~UpdateTransaction()
{
    if (!committed_)
    {
        store_.invertedIndex_ = std::move(draft_);
        // транзакция не была зафиксирована — сбрасываем флаг активности в хранилище
        store_.transactionActive_ = false;
    }
}
UpdateTransaction::UpdateTransaction(
    UpdateTransaction&& other) noexcept // Он "перемещает" ресурсы из временного объекта other в новый.
    : store_(other.store_), draft_(std::move(other.draft_)), committed_(other.committed_)
{
    other.committed_ = true;
    // деструктор не будет вызываться, а у нового объекта commited_ = false
}

UpdateTransaction& UpdateTransaction::operator=(UpdateTransaction&& other) noexcept
{ // оператор перемещающего присваивания. Вызывается, когда мы пишем tx1 = std::move(tx2);.
    if (this != &other)
    {
        store_ = other.store_;
        draft_ = std::move(other.draft_);
        committed_ = other.committed_;
        other.committed_ = true;
    }
    return *this;
}

InvertedIndex& UpdateTransaction::index()
{
    return store_.invertedIndex_;
}

void UpdateTransaction::commit()
{
    if (!committed_)
    {
        committed_ = true;
        store_.transactionActive_ = false; // транзакция завершена
        // разблокировали хранилище для следующих транзакций
    } // commit() сбрасывает флаг после успешного перемещения данных.
}
} // namespace lab_6