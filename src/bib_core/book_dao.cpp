#include "bib/dao/book.hpp"

// Bib
#include "bib/dto/author.hpp"
#include "bib/dto/authors_of_books.hpp"

// STL
#include <algorithm>
#include <iterator>

namespace bib {
    namespace dao {
        book::book(database& db) :
            db{ db }
        {
        }

        void book::insert_book(const dto::book& bk)
        {
            db->insert(bk);
        }

        void book::add_author(std::string_view isbn, std::string_view author_email)
        {
            dto::authors_of_books entry{ -1, isbn.data(), author_email.data() };

            db->insert(entry);
        }

        std::vector<dto::book> book::search_books_by_name(std::string_view author_last_name) const
        {
            std::vector<dto::book> result;

            using namespace sql;

            auto rows = db->select(
                columns(
                    &dto::book::isbn,
                    &dto::book::title,
                    &dto::book::year,
                    &dto::author::email,
                    &dto::author::last_name,
                    &dto::authors_of_books::author_email,
                    &dto::authors_of_books::book_isbn
                ),
                left_join<dto::authors_of_books>(
                    on(c(&dto::author::email) == &dto::authors_of_books::author_email)
                ),
                left_join<dto::authors_of_books>(
                    on(c(&dto::book::isbn) == &dto::authors_of_books::book_isbn)
                ),
                where(c(&dto::author::last_name) == author_last_name.data())
            );

            const auto nb_results = std::distance(std::begin(rows), std::end(rows));
            result.reserve(nb_results);

            std::transform(std::begin(rows), std::end(rows), std::back_inserter(result), [](const auto& row) {
                return dto::book{
                    std::get<0>(row),
                    std::get<1>(row),
                    std::get<2>(row)
                };
            });

            return result;
        }

        std::vector<dto::book> book::search_books_by_email(std::string_view author_email) const
        {
            std::vector<dto::book> result;

            using namespace sql;

            auto rows = db->select(
                columns(
                    &dto::book::isbn,
                    &dto::book::title,
                    &dto::book::year,
                    &dto::authors_of_books::author_email,
                    &dto::authors_of_books::book_isbn
                ),
                left_join<dto::authors_of_books>(
                    on(c(&dto::book::isbn) == &dto::authors_of_books::book_isbn)
                ),
                where(c(&dto::authors_of_books::author_email) == author_email.data())
            );

            const auto nb_results = std::distance(std::begin(rows), std::end(rows));
            result.reserve(nb_results);

            std::transform(std::begin(rows), std::end(rows), std::back_inserter(result), [](const auto& row) {
                return dto::book{
                    std::get<0>(row),
                    std::get<1>(row),
                    std::get<2>(row)
                };
            });

            return result;
        }

        std::vector<dto::book> book::get_books() const
        {
            return db->get_all<dto::book>();
        }
    }
}