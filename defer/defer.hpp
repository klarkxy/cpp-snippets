#pragma once

#include <bits/stdc++.h>

class DeferHelper
{
public:
    DeferHelper(const DeferHelper& cb): m_cb(cb) {}
    DeferHelper(DeferHelper&& cb): m_cb(std::move(cb)) {}
    virtual ~DeferHelper() {
        if (m_cb) {
            m_cb();
        }
    }
private:
    std::function<void()> m_cb;
};

#ifndef CONNECTION
#define CONNECTION(text1, text2) text1##text2
#endif

#ifndef CONNECT_STR
#define CONNECT_STR(text1, text2) CONNECTION(text1, text2)
#endif

#undef defer
#define defer(code) DeferHelper CONNECT_STR(defer, __LINE__)([&]{code;})