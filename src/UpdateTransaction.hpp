#pragma once

#include "InvertedIndex.hpp"
#include "Result.hpp"
#include <utility>

namespace lab_6 {

    class IndexStore;

    class UpdateTransaction {
    public:
        UpdateTransaction(IndexStore& store, std::unique_ptr<InvertedIndex> draft);

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
        std::unique_ptr<InvertedIndex> draft_;
        bool committed_ = false;
    };

} // namespace lab_6