#pragma once

// Bib
#include "arguments.hpp"
#include "bib.hpp"

// STL
#include <algorithm>
#include <iterator>
#include <sstream>

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
            bib::dto::author auth{
                data.email,
                data.first_name,
                data.last_name,
                data.mobile,
                data.address,
                data.city,
                data.birth_date
            };

            bib::database db;
            bib::dao::author dao(db);
            dao.insert_author(auth);

            return "Insertion successful";
        }

        template <>
        inline std::string command<arguments::author_search_arg>::execute() const
        {
            bib::database db;
            bib::dao::author dao(db);
            
            const auto result = dao.search_authors(data.book_title);

            std::stringstream ss;
            for (const auto& current_author : result) {
                ss << current_author.email;
            }

            return ss.str();
        }

        template <>
        inline std::string command<arguments::book_addition_arg>::execute() const
        {
            bib::dto::book bk{
                data.isbn,
                data.title,
                data.year
            };

            bib::database db;
            bib::dao::book dao(db);
            dao.insert_book(bk);

            for (const auto& current_email : data.author_emails) {
                dao.add_author(data.isbn, current_email);
            }

            return "Insertion successful";
        }

        template <>
        inline std::string command<arguments::book_search_arg>::execute() const
        {
            const auto result = [this] {
                bib::database db;
                bib::dao::book dao(db);
                if (data.author_email) {
                    return dao.search_books_by_email(*data.author_email);
                }
                if (data.author_last_name) {
                    return dao.search_books_by_name(*data.author_last_name);
                }
                throw std::invalid_argument("An author email or an author last name must be specified.");
            }();

            std::stringstream ss;
            for (const auto& current_book : result) {
                ss << current_book.isbn << ' ' << current_book.title << '\n';
            }

            return ss.str();
        }
    }
}