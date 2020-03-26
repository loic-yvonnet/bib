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
    /**
     * @brief Default hidden Sqlite DB file name.
     */
    constexpr const char* default_database = ".database.sqlite";

    /**
     * @brief Simpler Sqlite alias.
     */
    namespace sql = sqlite_orm;

    /**
     * @brief Definition of the Sqlite schema.
     * @param db_name - the Sqlite database filename.
     * @return the associated DB storage.
     */
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

    /**
     * @brief Alias the storage type.
     */
    using storage = decltype(make_storage(default_database));

    /**
     * @brief This class represents a Sqlite database.
     */
    class [[nodiscard]] database final {
    public:
        /**
         * @brief Constructor.
         */
        explicit database(std::string_view db_name = default_database);

        /**
         * @brief Movable, non-copyable type.
         */
        database(const database&) = delete;
        database(database&&) = default;
        database& operator=(const database&) = delete;
        database& operator=(database&&) = default;

        /**
         * @brief Get the underlying storage.
         * @return the underlying storage.
         */
        const storage& get() const noexcept { return db; }
        storage& get() noexcept { return db; }

        /**
         * @brief Syntactic sugar to manipulate the
         * underlying storage directly from an instance
         * of this class.
         * @return a not null pointer to the storage.
         */
        const storage* operator->() const noexcept { return &db; }
        storage* operator->() noexcept { return &db; }

    private:
        storage db;
    };
}