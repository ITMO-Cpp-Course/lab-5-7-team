#include "Document.hpp" // наш класс Document
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
