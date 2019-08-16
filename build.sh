#!/bin/bash

clang++ -std=c++11 -Isrc/ test/test_scope_guard.cpp

clang++ -std=c++11 -Isrc/ src/background_pthread.cpp
