#include "Document.hpp"
#include "DocumentBuilder.hpp"
#include "InvertedIndex.hpp"
#include <catch2/catch_all.hpp>

using namespace lab5::document_work;

TEST_CASE("Document constructor and getters", "[document]")
{
    Document doc(1, "file.txt", "Hello world");

    REQUIRE(doc.getId() == 1);
    REQUIRE(doc.getName() == "file.txt");
    REQUIRE(doc.getText() == "Hello world");
}

TEST_CASE("Document getters return const references", "[document]")
{
    Document doc(2, "file.txt", "content");

    // Два вызова getName должны вернуть ссылку на один и тот же объект
    const std::string& ref1 = doc.getName();
    const std::string& ref2 = doc.getName();
    REQUIRE(&ref1 == &ref2);

    const std::string& ref3 = doc.getText();
    const std::string& ref4 = doc.getText();
    REQUIRE(&ref3 == &ref4);
}

TEST_CASE("Document copy", "[document]")
{
    Document original(3, "original.txt", "content");
    Document copy = original; // проверка конструктора копирования

    REQUIRE(copy.getId() == original.getId());
    REQUIRE(copy.getName() == original.getName());
    REQUIRE(copy.getText() == original.getText());

    // Копия должна иметь собственные строки (адреса разные)
    REQUIRE(&copy.getName() != &original.getName());
    REQUIRE(&copy.getText() != &original.getText());
}

TEST_CASE("Document move", "[document]")
{
    Document original(4, "move.txt", "content");
    Document moved = std::move(original); // конструктор перемещения

    // moved получает все данные
    REQUIRE(moved.getId() == 4);
    REQUIRE(moved.getName() == "move.txt");
    REQUIRE(moved.getText() == "content");

    // original остаётся в валидном, но неопределённом состоянии.
    // Стандарт гарантирует, что перемещённые std::string становятся пустыми.
    REQUIRE(original.getName().empty());
    REQUIRE(original.getText().empty());
    // id (size_t) не меняется
    REQUIRE(original.getId() == 4);
}

TEST_CASE("Document with empty strings", "[document]")
{
    Document doc(0, "", "");

    REQUIRE(doc.getId() == 0);
    REQUIRE(doc.getName().empty());
    REQUIRE(doc.getText().empty());
}

// создаем функцию проверки наличия структуры Entry с заданым айди и индексом
bool containsEntry(const std::vector<Entry>& entries, size_t docId, size_t index)
{
    auto it = std::find_if(entries.begin(), entries.end(),
                           [docId, index](const Entry& e) { return e.docId == docId && e.index == index; });
    if (it == entries.end())
    {
        return false; // элемент не найден
    }
    return true; // найден – проверяем счётчик
}
TEST_CASE("InvertedIndex : add Document", "[InvertedIndex]")
{
    InvertedIndex index;
    Document doc1(1, "doc1", "cat dog cat");
    Document doc2(2, "doc2", "cat");
    index.addDocument(doc1);
    index.addDocument(doc2);

    SECTION("Cat")
    {
        auto result = index.search("cat");
        // возвращает структуру Entry
        REQUIRE(result.size() == 2);
        REQUIRE(containsEntry(result, doc1.getId(), 2));
        REQUIRE(containsEntry(result, doc2.getId(), 1));
    }
    SECTION("Dog")
    {
        auto result = index.search("dog");
        REQUIRE(result.size() == 1);
        REQUIRE(containsEntry(result, doc1.getId(), 1));
    }
    SECTION("No word")
    {
        auto result = index.search("surprise");
        REQUIRE(result.empty());
    }
}

TEST_CASE("InvertedIndex: remove Document", "[invertedIndex]")
{
    InvertedIndex index;
    Document doc1(1, "doc1", "apple banana apple");
    Document doc2(2, "doc2", "apple cherry");
    index.addDocument(doc1);
    index.addDocument(doc2);
    SECTION("document")
    {
        index.removeDocument(1);
        auto result = index.search("apple");
        REQUIRE(result.size() == 1);
        REQUIRE(containsEntry(result, doc2.getId(), 1));
        REQUIRE(!containsEntry(result, doc1.getId(), 1));

        auto resultBanana = index.search("banana");
        REQUIRE(resultBanana.empty());

        auto resultCherry = index.search("cherry");
        REQUIRE(resultCherry.size() == 1);
        REQUIRE(containsEntry(resultCherry, doc2.getId(), 1));
    }

    SECTION("no document")
    {
        REQUIRE_NOTHROW(index.removeDocument(22));
        REQUIRE(index.search("apple").size() == 2);
    }
}

TEST_CASE("InvertedIndex: WordInDocument", "[InvertedIndex]")
{
    InvertedIndex index;
    Document doc(5, "doc5", "one one two");
    index.addDocument(doc);

    SECTION("Word in document")
    {
        REQUIRE(index.WordInDocument("one", 5) == 2);
        REQUIRE(index.WordInDocument("two", 5) == 1);
    }

    SECTION("No word in this document")
    {
        Document doc2(6, "doc6", "three");
        index.addDocument(doc2);
        REQUIRE(index.WordInDocument("one", 6) == 0);
    }

    SECTION("No word")
    {
        REQUIRE(index.WordInDocument("surprise", 5) == 0);
    }
}
