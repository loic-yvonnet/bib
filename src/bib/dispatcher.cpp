#include "dispatcher.hpp"

namespace bib {
    namespace front_end {
        std::string process_arguments_and_dispatch_command(int argc, char** argv)
        {
            parser deserializer(argc, argv);

            switch (deserializer.get_action()) {
                case action_t::addition:
                    switch (deserializer.get_subject()) {
                        case subject_t::author: return parse_and_execute<arguments::author_addition_arg>(deserializer);
                        case subject_t::book: return parse_and_execute<arguments::book_addition_arg>(deserializer);
                        default: throw std::invalid_argument("Invalid subject.");
                    }
                case action_t::search:
                    switch (deserializer.get_subject()) {
                        case subject_t::author: return parse_and_execute<arguments::author_search_arg>(deserializer);
                        case subject_t::book: return parse_and_execute<arguments::book_search_arg>(deserializer);
                        default: throw std::invalid_argument("Invalid subject.");
                    }
                case action_t::help: return deserializer.get_help();
                default: throw std::invalid_argument("Invalid action");
            }
        }
    }
}