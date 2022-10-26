#!/bin/bash

if [ ! -f "pa1" ]; then
    make
fi

./pa1 <test/test.in >test/test_your.out # output your answer
diff test/test.out test/test_your.out