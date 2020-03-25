#pragma once

// STL
#include <string>

namespace bib {
    namespace dto {
        struct book final {
            std::string isbn;
            std::string title;
            std::string year;
        };
    }
}