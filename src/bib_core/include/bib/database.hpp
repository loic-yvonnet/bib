#pragma once

// Bib
#include "bib/dto/author.hpp"
#include "bib/dto/authors_of_books.hpp"
#include "bib/dto/book.hpp"

// Sqlite
#include <sqlite_orm/sqlite_orm.h>

// STL
#include <string>
#include <string_view>

namespace bib {
    constexpr const char* default_database = ".database.sqlite";

    namespace sql = sqlite_orm;

    inline auto make_storage(std::string_view db_name) {
        return sql::make_storage(
            db_name.data(),
            sql::make_table(
                "authors",
                sql::make_column("email", &dto::author::email, sql::unique()),
                sql::make_column("first_name", &dto::author::first_name),
                sql::make_column("last_name", &dto::author::last_name),
                sql::make_column("mobile", &dto::author::mobile),
                sql::make_column("address", &dto::author::address),
                sql::make_column("city", &dto::author::city),
                sql::make_column("birth_date", &dto::author::birth_date)
            ),
            sql::make_table(
                "books",
                sql::make_column("isbn", &dto::book::isbn, sql::unique()),
                sql::make_column("title", &dto::book::title),
                sql::make_column("year", &dto::book::year)
            ),
            sql::make_table(
                "authors_of_books",
                sql::make_column("author_email", &dto::authors_of_books::author_email),
                sql::make_column("book_isbn", &dto::authors_of_books::book_isbn)
            )
        );
    }

    using storage = decltype(make_storage(default_database));

    class [[nodiscard]] database final {
    public:
        explicit database(std::string_view db_name = default_database);

        database(const database&) = delete;
        database(database&&) = default;
        database& operator=(const database&) = delete;
        database& operator=(database&&) = delete;
    
        const storage& get() const noexcept { return db; }
        storage& get() noexcept { return db; }

        const storage* operator->() const noexcept { return &db; }
        storage* operator->() noexcept { return &db; }

    private:
        storage db;
    };
}