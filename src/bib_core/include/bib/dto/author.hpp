#pragma once

// STL
#include <string>
#include <vector>

namespace bib {
    namespace dto {
        /**
         * @brief Author instance in the Sqlite authors table.
         * It follows the Data Transfer Object design pattern.
         * @param email - the email address of the author.
         * @param first_name - the first name of the author.
         * @param mobile - the mobile phone number of the author.
         * @param address - the address of the author.
         * @param city - the city of the author.
         * @param birth_date - the birth date of the author.
         */
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