#pragma once

// Bib
#include "bib/dto/author.hpp"
#include "bib/dto/book.hpp"

// STL
#include <string_view>

// @TODO - implement & integrate
namespace bib {
    namespace utils {
        bool is_valid_email(std::string_view email);

        bool is_valid_field(std::string_view text);

        bool is_valid_date(std::string_view date);

        bool is_valid_year(std::string_view year);

        bool is_valid_isbn(std::string_view isbn);

        bool is_valid_author(const dto::author& author);

        bool is_valid_book(const dto::author& book);
    }
}