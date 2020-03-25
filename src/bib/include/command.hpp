#pragma once

#include "arguments.hpp"

namespace bib {
    namespace front_end {
        template <typename TData>
        class command final {
        public:
            explicit command(const TData& data) :
                data{ data } {}

            std::string execute() const;

        private:
            TData data;
        };

        template <>
        inline std::string command<arguments::author_addition_arg>::execute() const
        {
            return "author_addition_arg";
        }

        template <>
        inline std::string command<arguments::author_search_arg>::execute() const
        {
            return "author_search_arg";
        }

        template <>
        inline std::string command<arguments::book_addition_arg>::execute() const
        {
            return "book_addition_arg";
        }

        template <>
        inline std::string command<arguments::book_search_arg>::execute() const
        {
            return "book_search_arg";
        }
    }
}