#pragma once
#include "Document.hpp"
#include "DocumentBuilder.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace lab_6
{
class Document;
class DocumentBuilder;

struct Entry
{
    size_t docId;
    size_t index; // количество слов в этом документе
    Entry() : docId(0), index(0) {}

    Entry(size_t Id, size_t ind) : docId(Id), index(ind) {}
};

class InvertedIndex
{
  public:
    InvertedIndex() = default;
    InvertedIndex(const InvertedIndex& other);
    InvertedIndex& operator=(const InvertedIndex&) = default;
    InvertedIndex& operator=(InvertedIndex&&) = default;
    void addDocument(const Document& document);
    void removeDocument(size_t Id);
    std::vector<Entry> search(const std::string& word) const;
    size_t WordInDocument(const std::string& word, size_t docId) const;
    bool hasDocument(size_t id) const;

  private:
    std::unordered_map<std::string, std::vector<Entry>> invertedIndex_;
    std::unordered_map<size_t, std::shared_ptr<Document>> documents_;
};
} // namespace lab_6
