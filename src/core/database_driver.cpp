#include "database_driver.hpp"
#include <sqlite3.h>
#include <stdio.h>
#include <iostream>
#include <tuple>

namespace DatabaseDriver {
sqlite3* db;

void init(sqlite3* _db) {
  db = _db;
}

int open(const char* filename) {
  int rc = sqlite3_open(filename, &db);

  if (rc == SQLITE_ERROR) {
    fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(db));
  }

  return rc;
}

int close() {
  int rc = sqlite3_close(db);

  if (rc == SQLITE_ERROR) {
    fprintf(stderr, "Erro ao fechar o banco de dados: %s\n",
            sqlite3_errmsg(db));
  }

  return rc;
}

int execute(const char* sql) {
  int rc = sqlite3_exec(db, sql, NULL, NULL, NULL);

  if (rc == SQLITE_ERROR) {
    fprintf(stderr, "Erro ao executar o comando SQL: %s\n", sqlite3_errmsg(db));
  }

  return rc;
}

std::tuple<int, sqlite3_stmt*> prepare(const char* sql) {
  sqlite3_stmt* stmt;
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc == SQLITE_ERROR) {
    fprintf(stderr, "Erro ao preparar a consulta: %s\n", sqlite3_errmsg(db));
  }

  return std::make_tuple(rc, stmt);
}

int step(sqlite3_stmt* stmt) {
  int rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  if (rc == SQLITE_ERROR) {
    fprintf(stderr, "Erro ao executar o comando SQL: %s\n", sqlite3_errmsg(db));
  }

  return rc;
}

bool exists(const char* tableName) {
  std::string sql =
      "SELECT name FROM sqlite_master WHERE type='table' AND name='" +
      std::string(tableName) + "';";

  auto [_, stmt] = DatabaseDriver::prepare(sql.c_str());
  int rc = DatabaseDriver::step(stmt);

  return rc == SQLITE_ROW;
}
}