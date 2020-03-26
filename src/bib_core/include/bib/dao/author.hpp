#pragma once

// Bib
#include "bib/dto/author.hpp"
#include "bib/database.hpp"

// STL
#include <string_view>
#include <vector>

namespace bib {
    namespace dao {
        class author final {
        public:
            explicit author(database& db);

            author(const author&) = delete;
            author(author&&) = default;
            author& operator=(const author&) = delete;
            author& operator=(author&&) = delete;

            std::string insert_author(const dto::author& auth);

            std::vector<dto::author> search_authors(std::string_view book_isbn) const;

            std::vector<dto::author> get_authors() const;

        private:
            database& db;
        };
    }
}