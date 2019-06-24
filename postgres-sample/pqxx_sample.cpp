#include <iostream>
#include <pqxx/pqxx>

/// Query employees from database.  Return result.
pqxx::result query()
{
    pqxx::connection c{"host=192.168.11.2 dbname=everydb2 user=postgres port=5433 password=password"};
    pqxx::work txn{c};

    pqxx::result r = txn.exec(
        "SELECT year, monthday, jyocd, kaiji, nichiji, racenum" 
        " FROM public.n_race"
        " WHERE datakubun = '7' AND year::int >= 2019"
        " ORDER BY year DESC, jyocd DESC, kaiji DESC, nichiji DESC, racenum DESC"
    );

    int row_count = 0;
    for (auto row: r) { 
        std::cout
            // Address column by name.  Use c_str() to get C-style string.
            << row["year"].c_str()
            << row["monthday"].c_str()
            << row["jyocd"].c_str()
            << row["kaiji"].c_str()
            << row["nichiji"].c_str()
            << row["racenum"].c_str()
            << " int "
            // Address column by zero-based index.  Use as<int>() to parse as int.
            << row["year"].as<int>()
            << std::endl;
            ++ row_count;
    }

    std::cout << "read: " << row_count << std::endl;

    // Not really needed, since we made no changes, but good habit to be
    // explicit about when the transaction is done.
    txn.commit();

    // Connection object goes out of scope here.  It closes automatically.
    return r;
}


/// Query employees from database, print results.
int main(int, char**)
{
    try
    {
        pqxx::result r = query();

        // Results can be accessed and iterated again.  Even after the connection
        // has been closed.

        int row_count = 0;
        for (auto row: r)
        {
            std::cout << "Row: ";
            // Iterate over fields in a row.
            for (auto field: row) std::cout << field.c_str() << " ";
            std::cout << std::endl;
            ++ row_count;
        }
        std::cout << "read: " << row_count << " race" << std::endl;
    }
    catch (const pqxx::sql_error &e)
    {
        std::cerr << "SQL error: " << e.what() << std::endl;
        std::cerr << "Query was: " << e.query() << std::endl;
        return 2;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
