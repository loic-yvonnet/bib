#include "bib/database.hpp"

namespace bib {
    database::database(std::string_view db_name) :
        db{ bib::make_storage(db_name) }
    {
        db.sync_schema();
    }
}