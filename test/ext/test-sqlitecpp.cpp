#include <gtest/gtest.h>

#include <SQLiteCpp/Database.h>
#include <boost/filesystem/path.hpp>
#include <system/path.h>
#include <thread>
#include <sqlite3.h>

namespace
{
  GTEST_TEST(TestSqliteCpp, test_base_ops) {
    auto const cur_path = path::get_exe_dir().value.append("example.db3");

    try {
      // Open a database file
      SQLite::Database db(cur_path.string());

      // Compile a SQL query, containing one parameter (index 1)
      SQLite::Statement query(db, "select * from test");

      // Bind the integer value 6 to the first parameter of the SQL query
      // query.bind(1, 6);

      // Loop to execute the query step by step, to get rows of result
      while (query.executeStep()) {
        int const id = query.getColumn(0);
        char const* value = query.getColumn(1);
        double const weight = query.getColumn(2);

        std::cout
          << "id: " << id
          << ", value: " << value
          << ", weight: " << weight << std::endl;
      }
    } catch (std::exception& e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  int fetch_max_id(SQLite::Database& db) {
    SQLite::Statement query(db, "SELECT MAX(id) FROM test");
    if (query.executeStep())
      return query.getColumn(0);
    throw std::runtime_error("Fail to fetch max id!");
  }

  GTEST_TEST(TestSqliteCpp, test_multithread_mode) {
    std::cout << "Thread Mode: " << sqlite3_threadsafe() << std::endl;
  }

  GTEST_TEST(TestSqliteCpp, test_multithread) {
    auto const cur_path = path::get_exe_dir().value.append("example.db3");

    auto const writer = [&cur_path]() {
      std::cout << std::endl << "writer:" << std::endl;
      try {
        SQLite::Database db(cur_path.string(), SQLite::OPEN_READWRITE);
        SQLite::Statement query(db, "INSERT INTO test VALUES (:id, :value, :weight)");

        auto const max_id = fetch_max_id(db);
        std::cout << "curr max id: " << max_id << std::endl;

        // Loop to execute the query step by step, to get rows of result
        for (auto i = 1; i < 200; ++i) {
          query.bind(":id", max_id + i);
          query.bind(":value", std::string("Word").append(std::to_string(max_id + 1)));
          query.bind(":weight", 1.0);

          assert(query.exec() > 0);
          query.reset();
        }
      } catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
      }
    };

    auto const reader = [&cur_path]() {
      std::cout << std::endl << "reader:" << std::endl;
      try {
        // Open a database file
        SQLite::Database db(cur_path.string());

        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement query(db, "SELECT * FROM test LIMIT 100");

        // Bind the integer value 6 to the first parameter of the SQL query
        // query.bind(1, 6);

        // Loop to execute the query step by step, to get rows of result
        while (query.executeStep()) {
          // Demonstrate how to get some typed column value
          const int   id = query.getColumn(0);
          const char* value = query.getColumn(1);

          std::cout << "row: " << id << ", " << value << std::endl;
        }
      } catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
      }
    };

    auto const reseter = [&cur_path]() {
      std::cout << std::endl << "reseter:" << std::endl;
      try {
        SQLite::Database db(cur_path.string(), SQLite::OPEN_READWRITE);
        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement query(db, "DELETE FROM test WHERE id>4");
        std::cout << "delete rows: " << query.exec() << std::endl;
      } catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
      }
    };

    auto wtd = std::thread(writer);
    auto rtd = std::thread(reader);
    wtd.join();
    rtd.join();

    reseter();
  }
}
