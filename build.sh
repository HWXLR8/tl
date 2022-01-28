#!/bin/bash

make clean && make -j32 && ./game "$@"
