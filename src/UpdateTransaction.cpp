#include "UpdateTransaction.hpp"
#include "DocumentBuilder.hpp"
#include "IndexStore.hpp"
#include "InvertedIndex.hpp"

namespace lab_6
{
UpdateTransaction::UpdateTransaction(IndexStore& store, std::unique_ptr<InvertedIndex> draft)
    : store_(&store), draft_(std::move(draft)), committed_(false)
{
}
    // Деструктор: откат, если не был вызван commit
    UpdateTransaction::~UpdateTransaction() {
    if (!committed_ && store_) {
        store_->rollbackTransaction();   // сброс флага активности
        // draft_ удаляется автоматически
    }
}
UpdateTransaction::UpdateTransaction(UpdateTransaction&& other) noexcept
    : store_(other.store_), draft_(std::move(other.draft_)), committed_(other.committed_)
{
    other.store_ = nullptr;
    other.committed_ = true;
}

UpdateTransaction& UpdateTransaction::operator=(UpdateTransaction&& other) noexcept
{
    if (this != &other)
    {
        if (!committed_ && store_) {
            store_->rollbackTransaction();
        }
        store_ = other.store_;
        draft_ = std::move(other.draft_);
        committed_ = other.committed_;
        other.committed_ = true;
        other.store_ = nullptr;

    }
    return *this;
}

Result<void> UpdateTransaction::addDocument(const Document& doc)
{
    if (committed_)
    {
        return IndexError::TransactionAlreadyCompleted;
    }
    if (doc.getName().empty() || doc.getText().empty())
    {
        return IndexError::DocumentAlreadyExists;
    }
    if (draft_->hasDocument(doc.getId()))
    {
        return IndexError::DocumentAlreadyExists;
    }

    std::string lowerText = DocumentBuilder::ToLower(doc.getText());
    auto words = DocumentBuilder::SplitToWords(lowerText);
    draft_->addDocument(doc, words);
    return {};
}

Result<void> UpdateTransaction::removeDocument(size_t id)
{
    if (committed_)
        return IndexError::TransactionAlreadyCompleted;
    if (!draft_)
        return IndexError::TransactionInvalidState;
    if (!draft_->hasDocument(id))
        return IndexError::DocumentNotFound;
    draft_->removeDocument(id);
    return {};
}

void UpdateTransaction::сommit()
{
    if (committed_) return;
    if (store_)
    {
        store_->commitTransaction(std::move(draft_));
        committed_ = true;
        store_ = nullptr;   // чтобы деструктор не пытался откатить
    }
}
} // namespace lab_6