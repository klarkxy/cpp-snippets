#pragma once

template <typename T> class singleton {
public:
    static T *instance() {
        static T singleton;
        return &singleton;
    }

private:
    // ��ֹ����Ĺ���
    singleton() = default;
    singleton(const singleton &) = delete;
    singleton(singleton &&) = delete;
};