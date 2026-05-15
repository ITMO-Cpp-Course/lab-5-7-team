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

UpdateTransaction::~UpdateTransaction()
{
    if (!committed_)
    {
        store_.invertedIndex_ = std::move(draft_);
        store_.transactionActive_ = false;
    }
}
UpdateTransaction::UpdateTransaction(UpdateTransaction&& other) noexcept
    : store_(other.store_), draft_(std::move(other.draft_)), committed_(other.committed_)
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

InvertedIndex& UpdateTransaction::index()
{
    return store_.invertedIndex_;
}

void UpdateTransaction::commit()
{
    if (!committed_)
    {
        committed_ = true;
        store_.transactionActive_ = false;
    }
}
} // namespace lab_6