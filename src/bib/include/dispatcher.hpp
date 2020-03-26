#pragma once

// Bib
#include "arguments.hpp"
#include "command.hpp"
#include "parser.hpp"

// STL
#include <string>

namespace bib {
    namespace front_end {
        /**
         * @brief Once the action and the subject are known, it is possible
         * to parse the remaining specific arguments, create the related
         * command, and execute it.
         * @param deserializer - the deserializer/parser/formatter.
         * @return an execution report.
         * @throw an exception if an error occurs.
         */
        template <typename TData>
        [[nodiscard]] std::string parse_and_execute(parser& deserializer) {
            const auto data = deserializer.parse<TData>();
            const command<TData> cmd(data);

            return cmd.execute();
        }

        /**
         * @brief Parse the input arguments, create the related command
         * and execute it.
         * @param argc - the number of command line arguments.
         * @param argv - the array of arguments.
         */
        std::string process_arguments_and_dispatch_command(int argc, char** argv);
    }
}