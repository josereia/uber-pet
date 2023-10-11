#!/bin/bash

mkdir build
cd build
cmake ..
make -j

cd ..
mkdir target
cp ./build/uber-pet ./target/uber-pet
cp ./build/uber-pet-tests ./target/uber-pet-tests
