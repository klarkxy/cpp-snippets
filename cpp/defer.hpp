#pragma once

#include "macro.h"
#include <functional>

class defer_helper {
public:
    defer_helper(const std::function<void()> &cb) : m_cb(cb) {}
    defer_helper(std::function<void()> &&cb) : m_cb(std::move(cb)) {}
    virtual ~defer_helper() {
        if (m_cb) {
            m_cb();
        }
    }

private:
    std::function<void()> m_cb;
};


#undef defer
#define defer(code) defer_helper CONNECT_STR(defer, __LINE__)([&] { code; })