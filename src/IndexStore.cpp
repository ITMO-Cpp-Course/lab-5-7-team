#include "IndexStore.hpp"
#include "UpdateTransaction.hpp"
namespace lab_6
{

IndexStore::IndexStore() : index_(std::make_unique<InvertedIndex>()) {}

Result<void> IndexStore::addDocument(const Document& doc)
{
    // Проверка на пустой документ
    if (doc.getName().empty() || doc.getText().empty())
    {
        return IndexError{"Invalid document: empty name or text"};
    }

    // Проверка на дубликат ID
    if (index_->hasDocument(doc.getId()))
    {
        return IndexError{"Duplicate document ID: " + std::to_string(doc.getId())};
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
    if (!index_->hasDocument(docId))
    {
        return IndexError{"Document not found: ID " + std::to_string(docId)};
    }

    index_->removeDocument(docId);
    return {};
}

Result<std::vector<Entry>> IndexStore::search(const std::string& word) const
{
    return index_->search(word);
}

Result<size_t> IndexStore::wordCount(const std::string& word, size_t docId) const
{
    // Если документа нет, вернём 0
    if (!index_->hasDocument(docId))
    {
        return IndexError{"Document not found"};
    }
    return index_->wordCount(word, docId);
}

void IndexStore::assignIndex(std::unique_ptr<InvertedIndex> newIndex)
{
    index_ = std::move(newIndex);
}

UpdateTransaction IndexStore::beginTransaction()
{
    return UpdateTransaction(*this);
}
} // namespace lab_6