#pragma once

// STL
#include <string>

namespace bib {
    namespace dto {
        struct authors_of_books final {
            std::string book_isbn;
            std::string author_email;
        };
    }
}