#include "bib/dao/author.hpp"

// STL
#include <algorithm>
#include <iterator>

namespace bib {
    namespace dao {
        author::author(database& db) :
            db{ db }
        {
        }

        std::string author::insert_author(const dto::author& auth)
        {
            db->insert(auth);
            
            return db->dump(auth);
        }

        std::vector<dto::author> author::search_authors(std::string_view book_isbn) const
        {
            using namespace sql;
            const auto rows = db->select(
                columns(
                    &dto::author::email,
                    &dto::author::first_name,
                    &dto::author::last_name,
                    &dto::author::mobile,
                    &dto::author::address,
                    &dto::author::city,
                    &dto::author::birth_date,
                    &dto::authors_of_books::author_email,
                    &dto::authors_of_books::book_isbn
                ),
                left_join<dto::authors_of_books>(
                    on(c(&dto::authors_of_books::author_email) == &dto::author::email)
                ),
                where(c(&dto::authors_of_books::book_isbn) == book_isbn.data())
            );

            std::vector<dto::author> results;
            const auto nb_results = std::distance(std::begin(rows), std::end(rows));
            results.reserve(nb_results);
            std::transform(std::begin(rows), std::end(rows), std::back_inserter(results), [](const auto& row) {
                const auto& [email, first, last, mobile, address, city, birth, _1, _2] = row;
                return dto::author{ email, first, last, mobile, address, city, birth };
            });

            return results;
        }

        std::vector<dto::author> author::get_authors() const
        {
            return db->get_all<dto::author>();
        }
    }
}