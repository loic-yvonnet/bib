#pragma once

// STL
#include <optional>
#include <string>
#include <vector>

namespace bib {
    namespace front_end {
        /**
         * @brief Available actions on the command line.
         */
        enum class action_t {
            addition,
            search,
            help
        };

        /**
         * @brief Available subjects on the command line.
         */
        enum class subject_t {
            author,
            book
        };

        namespace arguments {
            /**
             * @brief Arguments expected for the addition
             * of an author.
             */
            struct author_addition_arg final {
                std::string email;
                std::string first_name;
                std::string last_name;
                std::string mobile;
                std::string address;
                std::string city;
                std::string birth_date;
            };

            /**
             * @brief Arguments expected when searching
             * for an author.
             */
            struct author_search_arg final {
                std::string book_title;
            };

            /**
             * @brief Arguments expected for the addition
             * of a book.
             */
            struct book_addition_arg final {
                std::string isbn;
                std::string title;
                std::string year;
                std::vector<std::string> author_emails;
            };

            /**
             * @brief Arguments expected when searching
             * for a book.
             */
            struct book_search_arg final {
                std::optional<std::string> author_email;
                std::optional<std::string> author_last_name;
            };
        }
    }
}