#pragma once

// Bib
#include "arguments.hpp"
#include "command.hpp"
#include "parser.hpp"

// STL
#include <string>

namespace bib {
    namespace front_end {
        template <typename TData>
        [[nodiscard]] std::string parse_and_execute(parser& deserializer) {
            const auto data = deserializer.parse<TData>();
            const command<TData> cmd(data);

            return cmd.execute();
        }

        std::string process_arguments_and_dispatch_command(int argc, char** argv);
    }
}