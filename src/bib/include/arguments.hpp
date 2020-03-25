#pragma once

// STL
#include <optional>
#include <string>
#include <vector>

namespace bib {
    namespace front_end {
        enum class action_t {
            addition,
            search,
            help
        };

        enum class subject_t {
            author,
            book
        };

        namespace arguments {
            struct author_addition_arg final {
                std::string email;
                std::string first_name;
                std::string last_name;
                std::string mobile;
                std::string address;
                std::string city;
                std::string birth_date;
            };

            struct author_search_arg final {
                std::string book_title;
            };

            struct book_addition_arg final {
                std::string isbn;
                std::string title;
                std::string year;
                std::vector<std::string> author_emails;
            };

            struct book_search_arg final {
                std::optional<std::string> author_email;
                std::optional<std::string> author_last_name;
            };
        }
    }
}