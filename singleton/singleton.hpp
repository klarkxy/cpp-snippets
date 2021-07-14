#pragma once

template <typename T> class singleton {
public:
    static T *instance() {
        static T singleton;
        return &singleton;
    }

private:
    // 禁止额外的构造
    singleton() = default;
    singleton(const singleton &) = delete;
    singleton(singleton &&) = delete;
};