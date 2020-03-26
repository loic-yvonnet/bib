#pragma once

// Bib
#include "arguments.hpp"

// Boost
#include <boost/program_options.hpp>

// STL
#include <string>
#include <vector>

namespace bib {
    namespace front_end {
        /**
         * @brief Shorter namespace alias for program options management.
         */
        namespace po = boost::program_options;

        /**
         * @brief The parser is responsible for deserializing the command
         * line arguments.
         */
        class parser final {
        public:
            /**
             * @brief Constructor.
             * It starts parsing the action of subject.
             */
            explicit parser(int argc, char** argv);

            /**
             * @brief Get the parsed action.
             * @return the action.
             */
            action_t get_action() const noexcept { return action; }

            /**
             * @brief Get the parsed subject.
             * @return the subject.
             */
            subject_t get_subject() const noexcept { return subject; }

            /**
             * @brief Get the help message.
             * @return the help message.
             */
            std::string get_help() const;

            /**
             * @brief Parse the remaining specific arguments.
             * These arguments depend on the selected action and subject.
             * This method is meant to be specialized.
             * @return the strongly-typed argument from the selected
             * action and subject, and remaining arguments.
             */
            template <typename TArgument>
            TArgument parse();

        private:
            void parse_action_and_subject();

            [[nodiscard]] po::options_description get_global_options() const;
            [[nodiscard]] po::options_description get_author_addition_options() const;
            [[nodiscard]] po::options_description get_author_search_options() const;
            [[nodiscard]] po::options_description get_book_addition_options() const;
            [[nodiscard]] po::options_description get_book_search_options() const;
            void collect_extra_arguments(const po::options_description& options);

            int argc;
            char** argv;
            action_t action;
            subject_t subject;
            po::variables_map variables;
            po::parsed_options parsed_options;
        };

        /**
         * @brief Author addition argument parser.
         */
        template <>
        inline arguments::author_addition_arg parser::parse<arguments::author_addition_arg>()
        {
            const auto options = get_author_addition_options();
            collect_extra_arguments(options);

            return {
                variables["email"].as<std::string>(),
                (variables.count("first-name")) ? variables["first-name"].as<std::string>() : "",
                (variables.count("last-name")) ? variables["last-name"].as<std::string>() : "",
                (variables.count("mobile")) ? variables["mobile"].as<std::string>() : "",
                (variables.count("address")) ? variables["address"].as<std::string>() : "",
                (variables.count("city")) ? variables["city"].as<std::string>() : "",
                (variables.count("birth-date")) ? variables["birth-date"].as<std::string>() : ""
            };
        }

        /**
         * @brief Author search argument parser.
         */
        template <>
        inline arguments::author_search_arg parser::parse<arguments::author_search_arg>()
        {
            const auto options = get_author_search_options();
            collect_extra_arguments(options);

            return {
                variables["book"].as<std::string>()
            };
        }

        /**
         * @brief Book addition argument parser.
         */
        template <>
        inline arguments::book_addition_arg parser::parse<arguments::book_addition_arg>()
        {
            const auto options = get_book_addition_options();
            collect_extra_arguments(options);

            return {
                variables["isbn"].as<std::string>(),
                variables["title"].as<std::string>(),
                variables["year"].as<std::string>(),
                variables["authors"].as<std::vector<std::string>>()
            };
        }

        /**
         * @brief Book search argument parser.
         */
        template <>
        inline arguments::book_search_arg parser::parse<arguments::book_search_arg>()
        {
            const auto options = get_book_search_options();
            collect_extra_arguments(options);

            arguments::book_search_arg arg;
            if (variables.count("email")) {
                arg.author_email = variables["email"].as<std::string>();
            }
            if (variables.count("last-name")) {
                arg.author_last_name = variables["last-name"].as<std::string>();
            }

            return arg;
        }
    }
}