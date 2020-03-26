// Catch2
#include "catch.hpp"

// Bib
#include "bib.hpp"

SCENARIO("Books can be inserted", "[book DAO]") {
    GIVEN("An empty memory database and a book DAO") {
        bib::database db(":memory:");
        bib::dao::book dao(db);
        const bib::dto::book game_of_road{
            "12345",
            "A song of earth of wind",
            "1980"
        };
        const bib::dto::book bovary{
            "67890",
            "Mister Bovary Junior",
            "1795"
        };

        WHEN("a book is inserted") {
            dao.insert_book(game_of_road);

            THEN("this book may now be found") {
                const auto books = dao.get_books();

                REQUIRE(!books.empty());
                REQUIRE(books.size() == 1);
                REQUIRE(books.front().isbn == game_of_road.isbn);
            }
        }

        WHEN("another book is inserted") {
            dao.insert_book(game_of_road);
            dao.insert_book(bovary);

            THEN("this new book may now be found as well") {
                const auto books = dao.get_books();

                REQUIRE(books.size() == 2);
                REQUIRE(books.at(0).isbn == game_of_road.isbn);
                REQUIRE(books.at(1).isbn == bovary.isbn);
            }
        }

        WHEN("a book is re-inserted") {
            dao.insert_book(game_of_road);

            THEN("it is not reinserted and an error is thrown") {
                REQUIRE_THROWS(
                    dao.insert_book(game_of_road)
                );
            }
        }
    }
}

SCENARIO("The books written by an author may be found", "[author & book DAO]") {
    GIVEN("An empty memory database, an author DAO and a book DAO") {
        bib::database db(":memory:");
        bib::dao::author author_dao(db);
        bib::dao::book book_dao(db);
        const bib::dto::author dana{
            "dana.oaks@none.uk.co",
            "Dana",
            "Oaks",
            "",
            "",
            "",
            "01/02/1440"
        };
        const bib::dto::author smith{
            "b@c.fr",
            "Smith",
            "Johnson",
            "01.02.03.04.05",
            "141 rue de la Bastille",
            "PARIS",
            "07/06/5432"
        };
        const bib::dto::book bestseller{
            "039485349058",
            "War for the oaks",
            "1472"
        };
        const bib::dto::book bovary{
            "67890",
            "Mister Bovary Junior",
            "1795"
        };
        const bib::dto::book game_of_road{
            "12345",
            "A song of earth of wind",
            "1980"
        };

        WHEN("a book has no know author") {
            book_dao.insert_book(bestseller);

            THEN("no author may be found by email") {
                const auto books = book_dao.search_books_by_email(dana.email);

                REQUIRE(books.empty());
            }

            THEN("no author may be found by name") {
                const auto books = book_dao.search_books_by_name(dana.last_name);

                REQUIRE(books.empty());
            }
        }

        WHEN("an author wrote one book") {
            author_dao.insert_author(dana);
            book_dao.insert_book(bestseller);
            book_dao.add_author(bestseller.isbn, dana.email);

            THEN("the book may be found from the author's email") {
                const auto books = book_dao.search_books_by_email(dana.email);

                REQUIRE(!books.empty());
                REQUIRE(books.size() == 1);
                REQUIRE(books.front().isbn == bestseller.isbn);
            }

            THEN("the book may be found from the author's last name") {
                const auto books = book_dao.search_books_by_name(dana.last_name);

                REQUIRE(!books.empty());
                REQUIRE(books.size() == 1);
                REQUIRE(books.front().isbn == bestseller.isbn);
            }
        }

        WHEN("an author wrote two books") {
            author_dao.insert_author(dana);
            book_dao.insert_book(bestseller);
            book_dao.insert_book(bovary);
            book_dao.add_author(bestseller.isbn, dana.email);
            book_dao.add_author(bovary.isbn, dana.email);

            THEN("the book may be found from the author's email") {
                const auto books = book_dao.search_books_by_email(dana.email);

                REQUIRE(books.size() == 2);
                REQUIRE(books.at(0).isbn == bestseller.isbn);
                REQUIRE(books.at(1).isbn == bovary.isbn);
            }

            THEN("the book may be found from the author's last name") {
                const auto books = book_dao.search_books_by_name(dana.last_name);

                REQUIRE(books.size() == 2);
                REQUIRE(books.at(0).isbn == bestseller.isbn);
                REQUIRE(books.at(1).isbn == bovary.isbn);
            }
        }

        WHEN("there are multiple relationships and we search for books") {
            author_dao.insert_author(dana);
            author_dao.insert_author(smith);
            book_dao.insert_book(bestseller);
            book_dao.insert_book(bovary);
            book_dao.insert_book(game_of_road);
            book_dao.add_author(bestseller.isbn, dana.email);
            book_dao.add_author(bovary.isbn, dana.email);
            book_dao.add_author(game_of_road.isbn, smith.email);

            THEN("we still get the right number of books by email") {
                const auto books = book_dao.search_books_by_email(dana.email);

                REQUIRE(books.size() == 2);
                REQUIRE(books.at(0).isbn == bestseller.isbn);
                REQUIRE(books.at(1).isbn == bovary.isbn);
            }

            THEN("we still get the right number of books by name") {
                const auto books = book_dao.search_books_by_name(dana.last_name);

                REQUIRE(books.size() == 2);
                REQUIRE(books.at(0).isbn == bestseller.isbn);
                REQUIRE(books.at(1).isbn == bovary.isbn);
            }
        }
    }
}