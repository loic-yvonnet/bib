# bib - book library management console application.

## Build

Docker is required to build this project.

In one shell:
```
./start.sh
```

In another shell (while the first one is still running):
```
./compile.sh
```

## Run

Addition of an author:
```
./bib.sh add author --email brad.pit@gmail.com --first-name Brad --last-name Pit --mobile 01.02.03.04.05
```

Addition of a book:
```
./bib.sh add book --isbn 02940239 --title Bovary --year 1970 --authors brad.pit@gmail.com
```

Search the author of a book:
```
./bib.sh search author --book 02940239
```

Search the books written by an author:
```
./bib.sh search book --email brad.pit@gmail.com
./bib.sh search book --last-name Pit
```

## Test

The test suite may be run with:
```
./tools/shells/test.sh
```

## Work in Progress

The following things are pending:
* Support Windows (addition of batches, declspec, etc.).
* Check user inputs.
* Add logs (verbose mode).
* Troubleshoot the boost::program_options that truncs strings at the first space.
* Fix the help message.
* Fix the VS Code gdb issue.
* Setup Travis CI or Jenkins.