#pragma once

template <typename T>
class singleton {
public:
    static T *instance() {
        static T singleton;
        return &singleton;
    }
protected:
    singleton() {}
private:
    // 禁止额外的构造
    singleton(const singleton &) = delete;
    singleton(singleton &&) = delete;
    // 禁止额外的赋值
    singleton &operator=(const singleton &) = delete;
    singleton &operator=(singleton &&) = delete;
};