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
        ");",
        &err);

    DatabaseDriver::execute(
        "INSERT INTO users ("
        "username, password"
        ")"
        "VALUES ('admin', 'admin');",
        &err);
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
        ");",
        &err);

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
        "'47991255214');",
        &err);

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
        "'47991255214');",
        &err);
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
        ");",
        &err);

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
        "'(47) 9 9139-1097');",
        &err);

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
        "'(47) 9 9125-5214');",
        &err);
  }

  if (!DatabaseDriver::exists("pets")) {
    DatabaseDriver::execute(
        "CREATE TABLE pets ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "breed TEXT NOT NULL,"
        "sex TEXT NOT NULL,"
        "size TEXT NOT NULL,"
        "weight TEXT NOT NULL,"
        "observation TEXT NOT NULL"
        ");",
        &err);

    DatabaseDriver::execute(
        "INSERT INTO pets ("
        "name,"
        "breed,"
        "sex,"
        "size,"
        "weight,"
        "observation"
        ")"
        "VALUES ("
        "'Lua',"
        "'Shih-tzu',"
        "'Fêmea',"
        "'Pequeno',"
        "'7,2',"
        "'Muito bagunceira');",
        &err);
  }

  if (!DatabaseDriver::exists("services")) {
    DatabaseDriver::execute(
        "CREATE TABLE services ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "description TEXT NOT NULL,"
        "price TEXT NOT NULL"
        ");",
        &err);

    DatabaseDriver::execute(
        "INSERT INTO services ("
        "name,"
        "description,"
        "price"
        ")"
        "VALUES ("
        "'Vacinação(Gripe canina)',"
        "'A partir de 8 semanas; 1 ano após a última dose',"
        "'70,00');",
        &err);
  }

  if (!DatabaseDriver::exists("sales")) {
    DatabaseDriver::execute(
        "CREATE TABLE sales ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "service TEXT NOT NULL,"
        "pet TEXT NOT NULL,"
        "customer TEXT NOT NULL,"
        "driver TEXT NOT NULL,"
        "payment_method TEXT NOT NULL,"
        "total TEXT NOT NULL"
        ");",
        &err);

    DatabaseDriver::execute(
        "INSERT INTO sales ("
        "service,"
        "pet,"
        "customer,"
        "driver,"
        "payment_method,"
        "total"
        ")"
        "VALUES ("
        "'Vacinação(Gripe canina)',"
        "'Lua',"
        "'João Sereia',"
        "'Guilherme Maffei',"
        "'PIX',"
        "'70,00');",
        &err);
  }

  if (!DatabaseDriver::exists("payments")) {
    DatabaseDriver::execute(
        "CREATE TABLE payments ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "tax_type TEXT NOT NULL,"
        "tax TEXT NOT NULL"
        ");",
        &err);

    DatabaseDriver::execute(
        "INSERT INTO payments ("
        "name,"
        "tax_type,"
        "tax"
        ")"
        "VALUES ("
        "'Cartão de crédito',"
        "'Porcentagem',"
        "'3');",
        &err);

    DatabaseDriver::execute(
        "INSERT INTO payments ("
        "name,"
        "tax_type,"
        "tax"
        ")"
        "VALUES ("
        "'PIX',"
        "'Bruto',"
        "'0');",
        &err);

    DatabaseDriver::execute(
        "INSERT INTO payments ("
        "name,"
        "tax_type,"
        "tax"
        ")"
        "VALUES ("
        "'A vista',"
        "'Bruto',"
        "'0');",
        &err);
  }
}

int main(void) {
  init();

  AuthModule::main();

  exit(EXIT_SUCCESS);
  return EXIT_SUCCESS;
}