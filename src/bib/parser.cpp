#include "parser.hpp"

// STL
#include <sstream>
#include <string_view>
#include <stdexcept>

namespace {
    bib::front_end::action_t deserialize_action(std::string_view selected_action)
    {
        if (selected_action == "add") {
            return bib::front_end::action_t::addition;
        }
        if (selected_action == "search") {
            return bib::front_end::action_t::search;
        }
        if (selected_action == "-h" or selected_action == "--help" or selected_action == "help") {
            return bib::front_end::action_t::help;
        }
        throw std::invalid_argument("Invalid action. Supported actions: add, search.");
    }

    bib::front_end::subject_t deserialize_subject(std::string_view selected_subject)
    {
        if (selected_subject == "author") {
            return bib::front_end::subject_t::author;
        }
        if (selected_subject == "book") {
            return bib::front_end::subject_t::book;
        }
        throw std::invalid_argument("Invalid subject. Supported subjects: author, book.");
    }
}

namespace bib {
    namespace front_end {
        parser::parser(int argc, char** argv) :
            argc{ argc }, argv{ argv }, action{ action_t::addition }, subject{ subject_t::author },
            variables{}, parsed_options{ nullptr }
        {
            parse_action_and_subject();
        }

        std::string parser::get_help() const
        {
            std::stringstream ss;
            ss 
                << get_global_options()
                << get_author_addition_options()
                << get_author_search_options()
                << get_book_addition_options()
                << get_book_search_options();

            return ss.str();
        }

        void parser::parse_action_and_subject()
        {
            auto global = get_global_options();

            po::positional_options_description pos;
            pos.add("action", 1).
                add("subject", 2).
                add("subargs", -1);

            parsed_options = po::command_line_parser(argc, argv).
                options(global).
                positional(pos).
                allow_unregistered().
                run();

            po::store(parsed_options, variables);

            if (!variables.count("action")) { throw std::invalid_argument("Unspecified action"); }
            const auto selected_action = variables["action"].as<std::string>();
            action = deserialize_action(selected_action);
            
            if (action != action_t::help) {
                if (!variables.count("subject")) { throw std::invalid_argument("Unspecified subject"); }
                const auto selected_subject = variables["subject"].as<std::string>();
                subject = deserialize_subject(selected_subject);
            }
        }

        po::options_description parser::get_global_options() const
        {
            po::options_description global("Global options");
            global.add_options()
                ("action", po::value<std::string>(), "Action to execute (add or search)")
                ("subject", po::value<std::string>(), "Subject of the action (author or book)")
                ("subargs", po::value<std::vector<std::string>>(), "Arguments for command");
            
            return global;
        }

        po::options_description parser::get_author_addition_options() const
        {
            po::options_description options("Author addition options");
            options.add_options()
                ("email", po::value<std::string>(), "Email address of the author (mandatory)")
                ("first-name", po::value<std::string>(), "First name of the author")
                ("last-name", po::value<std::string>(), "First name of the author")
                ("mobile", po::value<std::string>(), "Mobile phone number of the author")
                ("address", po::value<std::string>(), "Address of the author")
                ("city", po::value<std::string>(), "City of the author")
                ("birth-date", po::value<std::string>(), "Birth date of the author");

            return options;
        }

        po::options_description parser::get_author_search_options() const
        {
            po::options_description options("Author search options");
            options.add_options()
                ("book", po::value<std::string>(), "The book title whose author(s) is(are) requested");

            return options;
        }

        po::options_description parser::get_book_addition_options() const
        {
            po::options_description options("Book addition options");
            options.add_options()
                ("isbn", po::value<std::string>(), "International Standard Book Number")
                ("title", po::value<std::string>(), "Title of the book")
                ("year", po::value<std::string>(), "Publication year of the book")
                ("authors", po::value<std::string>(), "Email addresses of the authors of the book");

            return options;
        }

        po::options_description parser::get_book_search_options() const
        {
            po::options_description options("Book search options");
            options.add_options()
                ("email", po::value<std::string>(), "Email address of the author of the book(s)")
                ("last-name", po::value<std::string>(), "Last name of the author of the book(s)");

            return options;
        }

        void parser::collect_extra_arguments(const po::options_description& options)
        {
            // Collect all the unrecognized options from the first pass. This will include the
            // (positional) action and subject, so we need to erase them.
            std::vector<std::string> args = po::collect_unrecognized(parsed_options.options, po::include_positional);
            args.erase(std::begin(args), std::begin(args) + 1);

            // Parse again
            po::store(po::command_line_parser(args).options(options).run(), variables);
        }
    }
}