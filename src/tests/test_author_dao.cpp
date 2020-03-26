// Catch2
#include "catch.hpp"

// Bib
#include "bib.hpp"

SCENARIO("Authors can be inserted", "[author DAO]") {
    GIVEN("An empty memory database and an author DAO") {
        bib::database db(":memory:");
        bib::dao::author dao(db);
        const bib::dto::author loic{
            "loic@yvo.solutions",
            "Loic",
            "Yvonnet",
            "06.77.06.71.37",
            "26 rue de Lorraine",
            "SAUMUR",
            "01/02/3456"
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

        WHEN("an author is inserted") {
            dao.insert_author(loic);

            THEN("this author may now be found") {
                const auto authors = dao.get_authors();

                REQUIRE(!authors.empty());
                REQUIRE(authors.size() == 1);
                REQUIRE(authors.front().email == loic.email);
            }
        }

        WHEN("another author is inserted") {
            dao.insert_author(loic);
            dao.insert_author(smith);

            THEN("this new author may now be found as well") {
                const auto authors = dao.get_authors();

                REQUIRE(authors.size() == 2);
                REQUIRE(authors.at(0).email == loic.email);
                REQUIRE(authors.at(1).email == smith.email);
            }
        }

        WHEN("an author is re-inserted") {
            dao.insert_author(loic);

            THEN("it is not reinserted and an error is thrown") {
                REQUIRE_THROWS(
                    dao.insert_author(loic)
                );
            }
        }
    }
}

SCENARIO("Authors of books may be found", "[author & book DAO]") {
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

        WHEN("a book has no known author") {
            book_dao.insert_book(bestseller);

            THEN("there is no author to be found") {
                const auto authors = author_dao.search_authors(bestseller.isbn);

                REQUIRE(authors.empty());
            }
        }

        WHEN("an author and her book are inserted") {
            author_dao.insert_author(dana);
            book_dao.insert_book(bestseller);
            book_dao.add_author(bestseller.isbn, dana.email);

            THEN("this author of the book may now be found") {
                const auto authors = author_dao.search_authors(bestseller.isbn);

                REQUIRE(!authors.empty());
                REQUIRE(authors.size() == 1);
                REQUIRE(authors.front().email == dana.email);
            }
        }

        WHEN("there are two authors for a book") {
            author_dao.insert_author(dana);
            author_dao.insert_author(smith);
            book_dao.insert_book(bestseller);
            book_dao.add_author(bestseller.isbn, dana.email);
            book_dao.add_author(bestseller.isbn, smith.email);

            THEN("these authors of the book may now be found") {
                const auto authors = author_dao.search_authors(bestseller.isbn);

                REQUIRE(authors.size() == 2);
                REQUIRE(authors.at(0).email == dana.email);
                REQUIRE(authors.at(1).email == smith.email);
            }
        }

        WHEN("there are multiple relationships and we search for authors") {
            author_dao.insert_author(dana);
            author_dao.insert_author(smith);
            book_dao.insert_book(bestseller);
            book_dao.insert_book(bovary);
            book_dao.insert_book(game_of_road);
            book_dao.add_author(bestseller.isbn, dana.email);
            book_dao.add_author(bovary.isbn, dana.email);
            book_dao.add_author(game_of_road.isbn, smith.email);

            THEN("we still get the right number of authors") {
                const auto authors = author_dao.search_authors(bestseller.isbn);

                REQUIRE(authors.size() == 1);
                REQUIRE(authors.front().email == dana.email);;
            }
        }
    }
}