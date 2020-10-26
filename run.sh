#!/bin/bash

# A little script for a faster use of cmake & conan

BUILDPATH=cmake-build-debug

mkdir -p $BUILDPATH && cd $BUILDPATH && conan install .. -b missing && cmake .. && cmake --build .;