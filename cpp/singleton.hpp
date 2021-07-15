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
    // ��ֹ����Ĺ���
    singleton(const singleton &) = delete;
    singleton(singleton &&) = delete;
    // ��ֹ����ĸ�ֵ
    singleton &operator=(const singleton &) = delete;
    singleton &operator=(singleton &&) = delete;
};