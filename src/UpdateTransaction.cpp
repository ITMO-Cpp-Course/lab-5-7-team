#include "UpdateTransaction.hpp"
#include "DocumentBuilder.hpp"
#include "IndexStore.hpp"
#include "InvertedIndex.hpp"

namespace lab_6
{
UpdateTransaction::UpdateTransaction(IndexStore& store)
    : store_(&store), clone_(std::make_unique<InvertedIndex>(*store.index_)), committed_(false)
{
}

UpdateTransaction::UpdateTransaction(UpdateTransaction&& other) noexcept
    : store_(other.store_), clone_(std::move(other.clone_)), committed_(other.committed_)
{
    other.store_ = nullptr;
    other.committed_ = false;
}

UpdateTransaction& UpdateTransaction::operator=(UpdateTransaction&& other) noexcept
{
    if (this != &other)
    {
        store_ = other.store_;
        clone_ = std::move(other.clone_);
        committed_ = other.committed_;
        other.store_ = nullptr;
        other.committed_ = false;
    }
    return *this;
}

UpdateTransaction::~UpdateTransaction()
{
    if (!committed_ && store_)
    {
        // просто уничтожаем clone_, не применяя изменения
    }
}

Result<void> UpdateTransaction::addDocument(const Document& doc)
{
    if (!clone_)
    {
        return IndexError{"Transaction is in invalid state"};
    }
    if (doc.getName().empty() || doc.getText().empty())
    {
        return IndexError{"Invalid document: empty name or text"};
    }
    if (clone_->hasDocument(doc.getId()))
    {
        return IndexError{"Duplicate document ID: " + std::to_string(doc.getId())};
    }

    std::string lowerText = DocumentBuilder::ToLower(doc.getText());
    auto words = DocumentBuilder::SplitToWords(lowerText);
    clone_->addDocument(doc, words);
    return {};
}

Result<void> UpdateTransaction::removeDocument(size_t docId)
{
    if (!clone_)
    {
        return IndexError{"Transaction is in invalid state"};
    }
    if (!clone_->hasDocument(docId))
    {
        return IndexError{"Document not found: ID " + std::to_string(docId)};
    }

    clone_->removeDocument(docId);
    return {};
}

Result<std::vector<Entry>> UpdateTransaction::search(const std::string& word) const
{
    if (!clone_)
    {
        return IndexError{"Transaction is in invalid state"};
    }
    return clone_->search(word);
}

Result<void> UpdateTransaction::сommit()
{
    if (!store_ || committed_)
    {
        return IndexError{"Cannot commit: transaction is already committed or invalid"};
    }

    // Заменяем индекс в хранилище на наш клон
    store_->assignIndex(std::move(clone_));
    committed_ = true;
    store_ = nullptr;
    return {};
}
} // namespace lab_6