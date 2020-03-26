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
        /**
         * @brief Command design pattern.
         * A command here represents an action to be executed
         * on a subject with strongly-typed argument TData.
         * @param TData - the command arguments.
         */
        template <typename TData>
        class command final {
        public:
            /**
             * @brief Constructor.
             */
            explicit command(const TData& data) :
                data{ data } {}

            /**
             * @brief Execute the command.
             * This method is meant to be specialized for each
             * concrete command.
             * @return an execution report.
             */
            std::string execute() const;

        private:
            TData data;
        };

        /**
         * @brief Author addition command.
         */
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
            
            return dao.insert_author(auth);
        }

        /**
         * @brief Author search command.
         */
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

        /**
         * @brief Book addition command.
         */
        template <>
        inline std::string command<arguments::book_addition_arg>::execute() const
        {
            std::stringstream ss;

            bib::dto::book bk{
                data.isbn,
                data.title,
                data.year
            };

            bib::database db;
            bib::dao::book dao(db);
            ss << dao.insert_book(bk);

            for (const auto& current_email : data.author_emails) {
                ss << '\n' << dao.add_author(data.isbn, current_email);
            }

            return ss.str();
        }

        /**
         * @brief Book search command.
         */
        template <>
        inline std::string command<arguments::book_search_arg>::execute() const
        {
            const auto result = [this] {
                bib::database db;
                bib::dao::book dao(db);
                if (data.author_email && !data.author_email->empty()) {
                    return dao.search_books_by_email(*data.author_email);
                }
                if (data.author_last_name && !data.author_last_name->empty()) {
                    return dao.search_books_by_name(*data.author_last_name);
                }
                throw std::invalid_argument("Either --email or --last-name must be specified.");
            }();

            std::stringstream ss;
            for (const auto& current_book : result) {
                ss << current_book.isbn << " - " << current_book.title << '\n';
            }

            return ss.str();
        }
    }
}