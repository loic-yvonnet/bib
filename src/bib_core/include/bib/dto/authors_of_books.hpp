#pragma once

// STL
#include <string>

namespace bib {
    namespace dto {
        struct authors_of_books final {
            int id;
            std::string author_email;
            std::string book_isbn;
        };
    }
}