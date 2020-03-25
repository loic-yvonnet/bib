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

        void author::insert_author(const dto::author& auth)
        {
            db->insert(auth);
        }

        std::vector<dto::author> author::search_authors(std::string_view book_isbn) const
        {
            std::vector<dto::author> result;

            using namespace sql;

            auto rows = db->select(
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

            const auto nb_results = std::distance(std::begin(rows), std::end(rows));
            result.reserve(nb_results);

            std::transform(std::begin(rows), std::end(rows), std::back_inserter(result), [](const auto& row) {
                return dto::author{
                    std::get<0>(row),
                    std::get<1>(row),
                    std::get<2>(row),
                    std::get<3>(row),
                    std::get<4>(row),
                    std::get<5>(row),
                    std::get<6>(row)
                };
            });

            return result;
        }

        std::vector<dto::author> author::get_authors() const
        {
            return db->get_all<dto::author>();
        }
    }
}