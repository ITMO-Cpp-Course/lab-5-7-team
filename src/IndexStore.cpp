#include "IndexStore.hpp"
#include "UpdateTransaction.hpp"
#include "DocumentBuilder.hpp"
#include "IndexError.hpp"
namespace lab_6
{

IndexStore::IndexStore() : index_(std::make_unique<InvertedIndex>()) {}

Result<void> IndexStore::addDocument(const Document& doc)
{
    if (transactionActive_)
    {
        return IndexError::TransactionAlreadyActive;
    }
    // Проверка на пустой документ
    if (doc.getName().empty() || doc.getText().empty())
    {
        return IndexError::InvalidDocument;
    }

    // Проверка на дубликат ID
    if (index_->hasDocument(doc.getId()))
    {
        return IndexError::DocumentAlreadyExists;
    }

    // Обработка текста
    std::string lowerText = DocumentBuilder::ToLower(doc.getText());
    auto words = DocumentBuilder::SplitToWords(lowerText);

    // Добавление в индекс
    index_->addDocument(doc, words);

    return {};
}

Result<void> IndexStore::removeDocument(size_t docId)
{
        if (transactionActive_)
        {
            return IndexError::TransactionAlreadyActive;
        }
    if (!index_->hasDocument(docId))
    {
        return IndexError::DocumentNotFound;
    }

    index_->removeDocument(docId);
    return {};
}

Result<std::vector<Entry>> IndexStore::search(const std::string& word) const
{
        if (word.empty())
        {
            return IndexError::EmptyWord;
        }

    return index_->search(word);
}

Result<size_t> IndexStore::WordInDocument(const std::string& word, size_t docId) const
{
    // Если документа нет, вернём 0
    if (!index_->hasDocument(docId))
    {
        return IndexError::DocumentNotFound;
    }
    return index_->WordInDocument(word, docId);
}


    Result<UpdateTransaction> IndexStore::beginTransaction()
    {
        if (transactionActive_) {
            return IndexError::TransactionAlreadyActive;
        }
        transactionActive_ = true;
        auto draft = std::make_unique<InvertedIndex>(*index_);  // копия
        return UpdateTransaction(*this, std::move(draft));
    }

    void IndexStore::rollbackTransaction() {
        transactionActive_ = false;
        // draft_ в UpdateTransaction уже уничтожен (или будет) - здесь только сброс флага
    }

    void IndexStore::commitTransaction(std::unique_ptr<InvertedIndex> newIndex) {
        index_ = std::move(newIndex);
        transactionActive_ = false;
    }

} // namespace lab_6