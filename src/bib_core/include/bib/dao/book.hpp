#pragma once

// Bib
#include "bib/dto/book.hpp"
#include "bib/database.hpp"

// STL
#include <string_view>
#include <vector>

namespace bib {
    namespace dao {
        class book final {
        public:
            explicit book(database& db);

            book(const book&) = delete;
            book(book&&) = default;
            book& operator=(const book&) = delete;
            book& operator=(book&&) = delete;

            void insert_book(const dto::book& bk);

            void add_author(std::string_view isbn, std::string_view author_email);

            std::vector<dto::book> search_books_by_name(std::string_view author_last_name) const;

            std::vector<dto::book> search_books_by_email(std::string_view author_email) const;

        private:
            database& db;
        };
    }
}