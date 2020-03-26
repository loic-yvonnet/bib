# bib - book library management console application.

## Build

Docker is required to build this project.

In one shell:
```
./tools/shells/build_docker_image.sh
./tools/shells/start_container.sh
```

In another shell (while the first one is still running):
```
./tools/shells/gen_cmake.sh
./tools/shells/compile.sh
```

## Run

Addition of an author:
```
./tools/shells/run.sh add author --email brad.pit@gmail.com --first-name Brad --last-name Pit --mobile 01.02.03.04.05
```

Addition of a book:
```
./tools/shells/run.sh add book --isbn 02940239 --title "Danse with Wolves" --year 1970 --authors brad.pit@gmail.com
```

Search the author of a book:
```
./tools/shells/run.sh search author --title 02940239
```

Search the books written by an author:
```
./tools/shells/run.sh search book --author_email brad.pit@gmail.com
./tools/shells/run.sh search book --author_last_name Pit
```

## Test

The test suite may be run with:
```
./tools/shells/test.sh
```

## Work in Progress

The following things are pending:
* Add shells at the top of the solution for convenience.
* Support Windows (addition of batches, declspec, etc.).
* Check user inputs.
* Add logs (verbose mode).
* Troubleshoot the boost::program_options that truncs strings at the first space.
* Fix the help message.
* Fix the VS Code gdb issue.