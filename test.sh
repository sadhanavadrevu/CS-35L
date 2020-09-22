#!/bin/bash

passed=0
touch file.txt

./lab0 --hello
if [ $? -ne 1 ]; then
    passed=1
fi

./lab0 -h
if [ $? -ne 1 ]; then
    passed=1
fi

./lab0 --input=unreadable.txt 
if [ $? -ne 2 ]; then
    passed=1
fi

touch unwritable.txt
chmod oug-w unwritable.txt
./lab0 --output=unwritable.txt
if [ $? -ne 3 ]; then
    passed=1
fi

./lab0 --segfault
if [ $? -ne 139 ]; then
    passed=1
fi

./lab0 --segfault --catch
if [ $? -ne 4 ]; then
    passed=1
fi

echo "hello world!" | ./lab0
if [ $? -ne 0 ]; then
    pwassed=1
fi


touch readable.txt
echo "testing again" > readable.txt
./lab0 --input=readable.txt
if [ $? -ne 0 ]; then
    passed=1
fi

touch writable.txt
echo "hello again" | ./lab0 --output=writable.txt
if [ $? -ne 0 ]; then
    passed=1
fi

./lab0 --input=readable.txt --output=writable.txt
if [ $? -ne 0 ]; then
    passed=1
fi

./lab0 --output=writable.txt --input=readable.txt
if [ $? -ne 0 ]; then
    passed=1
fi

./lab0 --input=readable.txt --output=writable.txt --catch
if [ $? -ne 0 ]; then
    passed=1
fi

./lab0 --input=readable.txt --output=writable.txt --catch --segfault
if [ $? -ne 4 ]; then
    passed=1
fi

./lab0 --input=readable.txt --output=writable.txt --segfault
if [ $? -ne 139 ]; then
    passed=1
fi

./lab0 --input=unreadable.txt --output=writable.txt --segfault
if [ $? -ne 2 ]; then
    passed=1
fi

./lab0 --input=readable.txt --output=unwritable.txt --segfault
if [ $? -ne 3 ]; then
    passed=1
fi

if [ $passed == 1 ]; then
    echo "smoke tests failed"
else
    echo "smoke tests passed"
fi

exit 0
