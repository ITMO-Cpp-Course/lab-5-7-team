#include "IndexStore.hpp"
#include "DocumentBuilder.hpp"
#include "IndexError.hpp"
#include "UpdateTransaction.hpp"
namespace lab_6
{

IndexStore::IndexStore() = default;

Result<void> IndexStore::addDocument(const Document& doc)
{
    if (transactionActive_)
    {
        return Result<void>(IndexError::TransactionAlreadyActive);
    }
    if (doc.getId() == 0)
    {
        return Result<void>(IndexError::InvalidId);
    }
    // Проверка на пустой документ
    if (doc.getName().empty() || doc.getText().empty())
    {
        return Result<void>(IndexError::InvalidDocument);
    }
    if (docIds_.find(doc.getId()) != docIds_.end())
    {
        return Result<void>(IndexError::DocumentAlreadyExists);
    }

    invertedIndex_.addDocument(doc); // метод InvertedIndex принимает только один аргумент
    docIds_.insert(doc.getId());
    return Result<void>();
}

Result<void> IndexStore::removeDocument(size_t docId)
{
    if (transactionActive_)
    {
        return Result<void>(IndexError::TransactionAlreadyActive);
    }
    if (docId == 0)
    {
        return Result<void>(IndexError::InvalidId);
    }
    // Проверка на пустой документ
    if (docIds_.find(docId) == docIds_.end())
    {
        return Result<void>(IndexError::DocumentNotFound);
    }

    invertedIndex_.removeDocument(docId);
    docIds_.erase(docId);
    return Result<void>();
}

Result<std::vector<Entry>> IndexStore::search(const std::string& word) const
{
    if (word.empty())
    {
        return Result<std::vector<Entry>>(IndexError::EmptyWord);
    }

    return Result<std::vector<Entry>>(invertedIndex_.search(word));
}

Result<size_t> IndexStore::WordInDocument(const std::string& word, size_t docId) const
{
    if (word.empty())
    {
        return Result<size_t>(IndexError::EmptyWord);
    }
    if (docId == 0)
    {
        return Result<size_t>(IndexError::InvalidId);
    }
    if (docIds_.find(docId) == docIds_.end())
    {
        return Result<size_t>(IndexError::DocumentNotFound);
    }
    return Result<size_t>(invertedIndex_.WordInDocument(word, docId));
}
Result<UpdateTransaction> IndexStore::beginTransaction()
{
    if (transactionActive_)
    {
        return Result<UpdateTransaction>(IndexError::TransactionAlreadyActive);
    }
    transactionActive_ = true;
    return UpdateTransaction(*this);
}

} // namespace lab_6