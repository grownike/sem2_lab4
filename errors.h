#include <iostream>

#pragma once
#define WrongIndex 1
using namespace std;

class IndexOutOfRange : exception {
public:
    static const char *IndexErrorList(int msg) {
        if (msg == WrongIndex) {

            auto string = "Wrong Index\n";
            return string;
        }
        auto string = "Error\n";
        return string;
    }

private:
    int errorCode;
    const char *msg;
public:
    explicit IndexOutOfRange(int msgCode) :
            exception(),
            errorCode(msgCode),
            msg(IndexErrorList(msgCode)) {
    }
};