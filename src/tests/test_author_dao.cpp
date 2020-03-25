// Catch2
#include "catch.hpp"

// Bib
#include "bib.hpp"

SCENARIO("Authors can be inserted", "[author DAO]") {
    GIVEN("An empty memory database and an author DAO") {
        bib::database db(":memory:");
        bib::dao::author dao(db);

        WHEN("an author is inserted") {
            dao.insert_author({
                "loic@yvo.solutions",
                "Loic",
                "Yvonnet",
                "06.77.06.71.37",
                "26 rue de Lorraine",
                "SAUMUR",
                "01/02/3456"
            });

            THEN("this author may now be found") {
                const auto authors = dao.get_authors();

                REQUIRE(!authors.empty());
                REQUIRE(authors.size() == 1);
                REQUIRE(authors.front().email == "loic@yvo.solutions");
            }
        }

        WHEN("another author is inserted") {
            dao.insert_author({
                "b@c.fr",
                "Smith",
                "Johnson",
                "01.02.03.04.05",
                "141 rue de la Bastille",
                "PARIS",
                "07/06/5432"
            });

            THEN("this new author may now be found as well") {
                const auto authors = dao.get_authors();

                REQUIRE(authors.size() == 2);
                REQUIRE(authors.at(2).email == "b@c.fr");
            }
        }

        WHEN("an author is re-inserted") {
            THEN("it is not reinserted and an error is thrown") {
                REQUIRE_THROWS(
                    dao.insert_author({
                        "loic@yvo.solutions",
                        "Loic",
                        "Yvonnet",
                        "06.77.06.71.37",
                        "26 rue de Lorraine",
                        "SAUMUR",
                        "01/02/3456"
                    })
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

        WHEN("an author and her book are inserted") {
            author_dao.insert_author({
                "dana.oaks@none.uk.co",
                "Dana",
                "Oaks",
                "",
                "",
                "",
                "01/02/1440"
            });

            book_dao.insert_book({
                "039485349058",
                "War for the oaks",
                "1472"
            });

            book_dao.add_author("039485349058", "dana.oaks@none.uk.co");

            THEN("this author of the book may now be found") {
                const auto authors = author_dao.search_authors("039485349058");

                REQUIRE(!authors.empty());
                REQUIRE(authors.size() == 1);
                REQUIRE(authors.front().email == "dana.oaks@none.uk.co");
            }
        }
    }
}