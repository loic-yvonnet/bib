// Bib
#include "dispatcher.hpp"

// FMT
#include "fmt/format.h"

// STL
#include <stdexcept>

int main(int argc, char** argv) {
    try {
        const auto report = bib::front_end::process_arguments_and_dispatch_command(argc, argv);
        fmt::print("{}\nExecution successful.\n", report);
    }
    catch (const std::exception& e) {
        fmt::print("Error: {}\nRun bib help to get more information.\n", e.what());
    }
}