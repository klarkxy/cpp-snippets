#pragma once

// 这个有点问题

#include <atomic>

template <typename T>
class nolock_queue {
public:
    nolock_queue(size_t size = 2048);
    virtual ~nolock_queue();

    nolock_queue(const nolock_queue &) = delete;
    nolock_queue(nolock_queue &&);

    virtual bool push(T &&val);
    virtual bool pop(T &val);

protected:
    size_t succ_idx(size_t idx);

private:
    template <typename T>
    struct node {
        node() : data(), stage(0) {}
        node(T &&val) : data(val), stage(0) {}

        T data;
        std::atomic<int> stage;
    };

    node<T> *m_queue;
    size_t m_size;

    std::atomic<size_t> m_head;
    std::atomic<size_t> m_tail;
};

template <typename T>
inline nolock_queue<T>::nolock_queue(size_t size = 2048) {
    m_size = size;
    m_queue = new node<T>[size];
    m_head = 0;
    m_tail = 0;
}
template <typename T>
inline nolock_queue<T>::~nolock_queue() {
    if (m_queue) {
        delete[] m_queue;
    }
}
template <typename T>
inline nolock_queue<T>::nolock_queue(nolock_queue &&other) {
    m_head = other.m_head;
    m_tail = other.m_tail;
    if (m_queue) {
        delete[] m_queue;
    }
    m_queue = other.m_queue;
    m_size = other.m_size;
    other.m_head = 0;
    other.m_tail = 0;
    other.m_queue = nullptr;
    other.m_size = 0;
}

template <typename T>
inline size_t nolock_queue<T>::succ_idx(size_t idx) {
    return (idx + 1) % m_size;
}

template <typename T>
inline bool nolock_queue<T>::push(T &&val) {
    size_t idx = m_tail;
    do {
        if (succ_idx(idx) == m_head) {
            return false;
        }
    } while (!m_tail.compare_exchange_weak(idx, succ_idx(idx)));
    auto &nd = m_queue[idx];
    for (int tmp = 0; !nd.stage.compare_exchange_weak(tmp, 1); tmp = 0)
        ;
    nd.data = std::move(val);
    for (int tmp = 1; !nd.stage.compare_exchange_weak(tmp, 2); tmp = 1)
        ;
    return true;
}
template <typename T>
inline bool nolock_queue<T>::pop(T &val) {
    size_t idx = m_head;
    do {
        if (idx == m_tail) {
            return false;
        }
    } while (!m_head.compare_exchange_weak(idx, succ_idx(idx)));
    auto &nd = m_queue[idx];
    for (int tmp = 2; !nd.stage.compare_exchange_weak(tmp, 3); tmp = 2)
        ;
    nd.data = std::move(val);
    for (int tmp = 3; !nd.stage.compare_exchange_weak(tmp, 0); tmp = 3)
        ;
    return true;
}