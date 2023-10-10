#include <core/database_driver.hpp>
#include <iostream>
#include <modules/auth/auth_module.hpp>

void init() {
  char* err;
  if (!DatabaseDriver::exists("users")) {
    DatabaseDriver::execute(
        "CREATE TABLE users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL,"
        "password TEXT NOT NULL"
        ");", &err);

    DatabaseDriver::execute(
        "INSERT INTO users ("
        "username, password"
        ")"
        "VALUES ('admin', 'admin');", &err);
  }

  if (!DatabaseDriver::exists("drivers")) {
    DatabaseDriver::execute(
        "CREATE TABLE drivers ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "cnh TEXT NOT NULL,"
        "marital_status TEXT NOT NULL,"
        "criminal TEXT NOT NULL,"
        "address TEXT NOT NULL,"
        "license_plate TEXT NOT NULL,"
        "phone1 TEXT NOT NULL,"
        "phone2 TEXT NOT NULL"
        ");", &err);

    DatabaseDriver::execute(
        "INSERT INTO drivers ("
        "name,"
        "cnh,"
        "marital_status,"
        "criminal,"
        "address,"
        "license_plate,"
        "phone1,"
        "phone2"
        ")"
        "VALUES ("
        "'João Sereia',"
        "'0000000000',"
        "'Solteiro',"
        "'Nada',"
        "'Av. Principal',"
        "'abc123',"
        "'47991385666',"
        "'47991255214');", &err);

    DatabaseDriver::execute(
        "INSERT INTO drivers ("
        "name,"
        "cnh,"
        "marital_status,"
        "criminal,"
        "address,"
        "license_plate,"
        "phone1,"
        "phone2"
        ")"
        "VALUES ("
        "'Guilherme Maffei',"
        "'0000000000',"
        "'Solteiro',"
        "'Nada',"
        "'Av. Principal',"
        "'abc123',"
        "'47991385666',"
        "'47991255214');", &err);
  }

  if (!DatabaseDriver::exists("customers")) {
    DatabaseDriver::execute(
        "CREATE TABLE customers ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "email TEXT NOT NULL,"
        "address TEXT NOT NULL,"
        "phone1 TEXT NOT NULL,"
        "phone2 TEXT NOT NULL"
        ");", &err);

    DatabaseDriver::execute(
        "INSERT INTO customers ("
        "name,"
        "email,"
        "address,"
        "phone1,"
        "phone2"
        ")"
        "VALUES ("
        "'João Sereia',"
        "'joao.lo.sereia@gmail.com',"
        "'Av. Principal',"
        "'(47) 9 9611-8078',"
        "'(47) 9 9139-1097');", &err);

    DatabaseDriver::execute(
        "INSERT INTO customers ("
        "name,"
        "email,"
        "address,"
        "phone1,"
        "phone2"
        ")"
        "VALUES ("
        "'Guilherme Maffei',"
        "'email@email.com',"
        "'Av. Principal',"
        "'abc123',"
        "'(47) 9 9138-5666',"
        "'(47) 9 9125-5214');", &err);
  }
}

int main(void) {
  init();

  AuthModule::main();

  exit(EXIT_SUCCESS);
  return EXIT_SUCCESS;
}