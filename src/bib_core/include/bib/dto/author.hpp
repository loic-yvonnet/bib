#pragma once

// STL
#include <string>
#include <vector>

namespace bib {
    namespace dto {
        struct author final {
            std::string email;
            std::string first_name;
            std::string last_name;
            std::string mobile;
            std::string address;
            std::string city;
            std::string birth_date;
        };
    }
}