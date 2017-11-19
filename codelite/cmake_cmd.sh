#!/bin/sh

cd ../build

echo Trying to cmake and build...

cmake -DPROJECT_NAME=uxvbase .. && cmake --build .

cd ../codelite

