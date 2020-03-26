#pragma once

// STL
#include <string>

namespace bib {
    namespace dto {
        /**
         * @brief Author of a book instance in the Sqlite authors_of_books table.
         * @param book_isbn - the International Standard Book Number.
         * @param author_email - the email of the author of that book.
         */
        struct authors_of_books final {
            std::string book_isbn;
            std::string author_email;
        };
    }
}