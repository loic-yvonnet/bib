#pragma once

// Bib
#include "bib/dto/book.hpp"
#include "bib/database.hpp"

// STL
#include <string>
#include <string_view>
#include <vector>

namespace bib {
    namespace dao {
        /**
         * @brief Book Data Access Object.
         * This is an abstraction on top of Sqlite to
         * manipulate books (CRUD operations and
         * advanced queries).
         */
        class book final {
        public:
            /**
             * @brief Constructor.
             */
            explicit book(database& db);

            /**
             * @brief Movable, non-copyable type.
             */
            book(const book&) = delete;
            book(book&&) = default;
            book& operator=(const book&) = delete;
            book& operator=(book&&) = default;

            /**
             * @brief Insert an new book in the DB.
             * @param bk - the book to be inserted.
             * @return a JSON serialization of the inserted instance.
             */
            std::string insert_book(const dto::book& bk);

            /**
             * @brief Add an author to the input book.
             * @param isbn - the Internal Standard Book Number.
             * @param author_email - the email of the author.
             * @return a JSON serialization of the inserted instance.
             */
            std::string add_author(std::string_view isbn, std::string_view author_email);

            /**
             * @brief Search books written by an author identified
             * by its last name.
             * @param author_last_name - the last name of the author.
             * @return the container of books written by this author.
             */
            std::vector<dto::book> search_books_by_name(std::string_view author_last_name) const;

            /**
             * @brief Search books written by an author identified
             * by its email.
             * @param author_email - the email of the author.
             * @return the container of books written by this author.
             */
            std::vector<dto::book> search_books_by_email(std::string_view author_email) const;

            /**
             * @brief Get all book in the DB.
             * @return all books.
             */
            std::vector<dto::book> get_books() const;

        private:
            database& db;
        };
    }
}