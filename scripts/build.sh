#!/bin/bash

mkdir build
cd build
cmake ..
make -j

cd ..
mkdir target
cp ./build/uber-pet ./target/uber-pet
