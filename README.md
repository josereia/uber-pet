# Uber PET

#### Credentials
* username: admin
* password: admin

### How to build
* Manually
  ~~~bash
  mkdir build
  cd build
  cmake ..
  make -j
  ~~~
* Script(Linux and MacOS)
  ~~~bash
  chmod +x ./scripts/build.sh
  ./scripts/build.sh
  ~~~

### How to run app
* Manually
  ~~~bash
  ./build/uber-pet
  ~~~
* Script(Linux and MacOS)
  ~~~bash
  chmod +x ./scripts/run_app.sh
  ./scripts/run_app.sh
  ~~~

### How to run tests
* Manually
  ~~~bash
  ./build/uber-pet-tests
  ~~~
* Script(Linux and MacOS)
  ~~~bash
  chmod +x ./scripts/run_tests.sh
  ./scripts/run_tests.sh
  ~~~
