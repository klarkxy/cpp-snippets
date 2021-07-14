#pragma once

#include <functional>

class defer_helper {
public:
    defer_helper(const defer_helper &cb) : m_cb(cb) {}
    defer_helper(defer_helper &&cb) : m_cb(std::move(cb)) {}
    virtual ~defer_helper() {
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
#define defer(code) defer_helper CONNECT_STR(defer, __LINE__)([&] { code; })