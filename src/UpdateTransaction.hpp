#pragma once

#include "InvertedIndex.hpp"
#include "Result.hpp"
#include <utility>
#include <unordered_set>

namespace lab_6
{
    class IndexStore;

    class UpdateTransaction
    {
    public:
        explicit UpdateTransaction(IndexStore& store);
        UpdateTransaction(const UpdateTransaction&) = delete;
        UpdateTransaction& operator=(const UpdateTransaction&) = delete;

        UpdateTransaction(UpdateTransaction&& other) noexcept;
        UpdateTransaction& operator=(UpdateTransaction&& other) noexcept;

        ~UpdateTransaction();

        Result<void> addDocument(const Document& doc);
        Result<void> removeDocument(size_t id);

        void commit();
        bool isCommitted() const { return committed_; }

    private:
        IndexStore& store_;
        InvertedIndex draft_; // копия индекса
        std::unordered_set<size_t> draftDocIds_; // копия множества id
        bool committed_ = false;
    };
} // namespace lab_6
