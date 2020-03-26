#pragma once

// Bib
#include "bib/dto/author.hpp"
#include "bib/dto/book.hpp"

// STL
#include <string_view>

/**
 * @brief Collection of utilities to validate the user inputs
 * for security reasons.
 */
namespace bib {
    namespace utils {
        /**
         * @brief Check if an email address is valid.
         * @param email - the email address.
         * @return true if the address is valid.
         */
        bool is_valid_email(std::string_view email);

        /**
         * @brief Check a given entry is valid for
         * DB processing.
         * @param text - the text field to check.
         * @return true if the text field is valid.
         */
        bool is_valid_field(std::string_view text);

        /**
         * @brief Check a date.
         * @param date - the date to check.
         * @return true if the date is valid.
         */
        bool is_valid_date(std::string_view date);

        /**
         * @brief Check a year.
         * @param year - the year to check.
         * @return true if the year is valid.
         */
        bool is_valid_year(std::string_view year);

        /**
         * @brief Check an ISBN.
         * @param isbn - the ISBN.
         * @return true if the ISBN is valid.
         */
        bool is_valid_isbn(std::string_view isbn);

        /**
         * @brief Check an author entry.
         * @param author - the author to check.
         * @return true if the author is valid.
         */
        bool is_valid_author(const dto::author& author);

        /**
         * @brief Check a book entry.
         * @param book - the book to check.
         * @return true if the book is valid.
         */
        bool is_valid_book(const dto::author& book);
    }
}