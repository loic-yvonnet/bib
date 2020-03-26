#pragma once

// Bib
#include "bib/dto/author.hpp"
#include "bib/database.hpp"

// STL
#include <string_view>
#include <vector>

namespace bib {
    namespace dao {
        /**
         * @brief Author Data Access Object.
         * This is an abstraction on top of Sqlite to
         * manipulate authors (CRUD operations and
         * advanced queries).
         */
        class author final {
        public:
            /**
             * @brief Constructor.
             */
            explicit author(database& db);

            /**
             * @brief Movable, non-copyable type.
             */
            author(const author&) = delete;
            author(author&&) = default;
            author& operator=(const author&) = delete;
            author& operator=(author&&) = default;

            /**
             * @brief Insert an new author in the DB.
             * @param auth - the author to be inserted.
             * @return a JSON serialization of the inserted instance.
             */
            std::string insert_author(const dto::author& auth);

            /**
             * @brief Search the DB for authors involved in
             * the input book.
             * @param book_isbn - the Internal Standard Book Number.
             * @return the container of authors who wrote that book.
             */
            std::vector<dto::author> search_authors(std::string_view book_isbn) const;

            /**
             * @brief Get all authors in the DB.
             * @return all authors.
             */
            std::vector<dto::author> get_authors() const;

        private:
            database& db;
        };
    }
}