#include "InvertedIndex.hpp"
#include "DocumentBuilder.hpp"
#include <algorithm>
#include <string>
#include <vector>
namespace lab_6
{
InvertedIndex::InvertedIndex(const InvertedIndex& other)
    : invertedIndex_(other.invertedIndex_),
      documents_(other.documents_) // если используется shared_ptr, копия разделяемая
{
}
void InvertedIndex::addDocument(const Document& document)
{
    size_t Id = document.getId();
    if (documents_.find(Id) != documents_.end())
    {
        InvertedIndex::removeDocument(Id);
    }
    std::string lower = DocumentBuilder::ToLower(document.getText());
    auto words = DocumentBuilder::SplitToWords(lower);
    documents_[Id] = std::make_shared<Document>(document);
    for (const std::string& word : words)
    {
        std::vector<Entry>& entries = invertedIndex_[word];
        bool found = false;
        for (Entry& entry : entries)
        {
            if (entry.docId == Id)
            {
                found = true;
                entry.index++;
                break;
            }
        }
        if (!found)
        {
            entries.push_back(Entry(Id, 1));
        }
    }
}

void InvertedIndex::removeDocument(size_t Id)
{
    auto it = documents_.find(Id);
    if (it == documents_.end())
    {
        return;
    }
    std::shared_ptr<Document> Ptr = it->second;
    std::string lower = DocumentBuilder::ToLower(Ptr->getText());
    auto words = DocumentBuilder::SplitToWords(lower);

    for (const std::string& word : words)
    {
        auto wordDoc = invertedIndex_.find(word);
        if (wordDoc != invertedIndex_.end())
        {
            std::vector<Entry>& entries = wordDoc->second;
            entries.erase(std::remove_if(entries.begin(), entries.end(),
                                         [Id](const Entry& entry) {
                                             return entry.docId == Id; //[]-объект,() у кого берет
                                         }),
                          entries.end());

            if (entries.empty())
            {
                invertedIndex_.erase(wordDoc);
            }
        }
    }
    documents_.erase(it);
}

std::vector<Entry> InvertedIndex::search(const std::string& word) const
{
    auto it = invertedIndex_.find(word);
    if (it != invertedIndex_.end())
    {
        return it->second;
    }
    return {};
}

size_t InvertedIndex::WordInDocument(const std::string& word, size_t Id) const
{
    auto it = invertedIndex_.find(word);
    if (it == invertedIndex_.end())
    {
        return 0;
    }
    const std::vector<Entry>& entries = it->second;
    for (const Entry& entry : entries)
    {
        if (entry.docId == Id)
        {
            return entry.index;
        }
    }
    return 0;
}
    bool InvertedIndex::hasDocument(size_t id) const
{
    return documents_.find(id) != documents_.end();
}

} // namespace lab_6