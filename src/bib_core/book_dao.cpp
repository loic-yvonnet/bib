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

        std::string book::insert_book(const dto::book& bk)
        {
            db->insert(bk);
            
            return db->dump(bk);
        }

        std::string book::add_author(std::string_view isbn, std::string_view author_email)
        {
            dto::authors_of_books entry{
                isbn.data(),
                author_email.data()
            };

            db->insert(entry);
            
            return db->dump(entry);
        }

        std::vector<dto::book> book::search_books_by_name(std::string_view author_last_name) const
        {
            using namespace sql;
            const auto rows = db->select(
                columns(
                    &dto::book::isbn,
                    &dto::book::title,
                    &dto::book::year,
                    &dto::author::email,
                    &dto::author::last_name,
                    &dto::authors_of_books::author_email,
                    &dto::authors_of_books::book_isbn
                ),
                inner_join<dto::book>(
                    on(c(&dto::authors_of_books::book_isbn) == &dto::book::isbn)
                ),
                inner_join<dto::author>(
                    on(c(&dto::authors_of_books::author_email) == &dto::author::email)
                ),
                where(c(&dto::author::last_name) == author_last_name.data())
            );

            std::vector<dto::book> result;
            const auto nb_results = std::distance(std::begin(rows), std::end(rows));
            result.reserve(nb_results);
            std::transform(std::begin(rows), std::end(rows), std::back_inserter(result), [](const auto& row) {
                const auto& [isbn, title, year, _1, _2, _3, _4] = row;
                return dto::book{ isbn, title, year };
            });

            return result;
        }

        std::vector<dto::book> book::search_books_by_email(std::string_view author_email) const
        {
            using namespace sql;
            const auto rows = db->select(
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

            std::vector<dto::book> result;
            const auto nb_results = std::distance(std::begin(rows), std::end(rows));
            result.reserve(nb_results);
            std::transform(std::begin(rows), std::end(rows), std::back_inserter(result), [](const auto& row) {
                const auto& [isbn, title, year, _1, _2] = row;
                return dto::book{ isbn, title, year };
            });

            return result;
        }

        std::vector<dto::book> book::get_books() const
        {
            return db->get_all<dto::book>();
        }
    }
}