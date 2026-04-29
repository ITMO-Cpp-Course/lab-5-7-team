#include "UpdateTransaction.hpp"
#include "DocumentBuilder.hpp"
#include "IndexStore.hpp"
#include "InvertedIndex.hpp"

namespace lab_6
{
UpdateTransaction::UpdateTransaction(IndexStore& store)
    : store_(store), draft_(store.invertedIndex_), draftDocIds_(store.docIds_)
{
}
UpdateTransaction::~UpdateTransaction() {
    if (!committed_) {
        // транзакция не была зафиксирована — сбрасываем флаг активности в хранилище
        store_.transactionActive_ = false;
    }
}
UpdateTransaction::UpdateTransaction(UpdateTransaction&& other) noexcept
    : store_(other.store_), draft_(std::move(other.draft_)), draftDocIds_(std::move(other.draftDocIds_)), committed_(other.committed_)
{
    other.committed_ = true;
}

UpdateTransaction& UpdateTransaction::operator=(UpdateTransaction&& other) noexcept
{
    if (this != &other)
    {
        store_ = other.store_;
        draft_ = std::move(other.draft_);
        committed_ = other.committed_;
        other.committed_ = true;

    }
    return *this;
}

Result<void> UpdateTransaction::addDocument(const Document& doc)
{
    if (committed_) {
        return Result<void>(IndexError::TransactionAlreadyCompleted);
    }
    if (doc.getId() == 0) {
        return Result<void>(IndexError::InvalidId);
    }
    if (doc.getName().empty() || doc.getText().empty())
    {
        return IndexError::DocumentAlreadyExists;
    }
    if (draftDocIds_.find(doc.getId()) != draftDocIds_.end()) {
        return Result<void>(IndexError::DocumentAlreadyExists);
    }
    // InvertedIndex::addDocument сам делает обработку текста
    draft_.addDocument(doc);
    draftDocIds_.insert(doc.getId());
    return Result<void>();
}

Result<void> UpdateTransaction::removeDocument(size_t id)
{
    if (committed_) {
        return Result<void>(IndexError::TransactionAlreadyCompleted);
    }
    if (id == 0) {
        return Result<void>(IndexError::InvalidId);
    }
    if (draftDocIds_.find(id) == draftDocIds_.end()) {
        return Result<void>(IndexError::DocumentNotFound);
    }
    draft_.removeDocument(id);
    draftDocIds_.erase(id);
    return Result<void>();
}

void UpdateTransaction::commit()
{
    if (!committed_)
    {
        store_.invertedIndex_ = std::move(draft_);
        store_.docIds_ = std::move(draftDocIds_);
        committed_ = true;
        store_.transactionActive_ = false;   // транзакция завершена
    }
}
} // namespace lab_6