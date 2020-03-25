// Catch2
#include "catch.hpp"

// Bib
#include "bib.hpp"

SCENARIO("Books can be inserted", "[book DAO]") {
    GIVEN("An empty memory database and a book DAO") {
        bib::database db(":memory:");
        bib::dao::book dao(db);

        WHEN("a book is inserted") {
            dao.insert_book({
                "12345",
                "A song of earth of wind",
                "1980"
            });

            THEN("this book may now be found") {
                const auto books = dao.get_books();

                REQUIRE(!books.empty());
                REQUIRE(books.size() == 1);
                REQUIRE(books.front().isbn == "12345");
            }
        }

        WHEN("another book is inserted") {
            dao.insert_book({
                "67890",
                "Mister Bovary Junior",
                "1795"
            });

            THEN("this new book may now be found as well") {
                const auto books = dao.get_books();

                REQUIRE(books.size() == 2);
                REQUIRE(books.at(2).isbn == "67890");
            }
        }

        WHEN("a book is re-inserted") {
            THEN("it is not reinserted and an error is thrown") {
                REQUIRE_THROWS(
                    dao.insert_book({
                        "12345",
                        "A song of earth of wind",
                        "1980"
                    })
                );
            }
        }
    }
}