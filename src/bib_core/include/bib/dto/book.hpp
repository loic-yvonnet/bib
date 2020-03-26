#pragma once

// STL
#include <string>

namespace bib {
    namespace dto {
        /**
         * @brief Book instance in the Sqlite books table.
         * It follows the Data Transfer Object design pattern.
         * @param isbn - the Internal Standard Book number.
         * @param title - the title of the book.
         * @param year - the publicatio year of the book.
         */
        struct book final {
            std::string isbn;
            std::string title;
            std::string year;
        };
    }
}