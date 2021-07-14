#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include "../singleton/singleton.hpp"

class factory : public singleton<factory> {
protected:
    // 生成器
    template <typename T> 
    struct procude_t {
        auto operator() { return make_shared<T>(); }
        template <typename... Args> auto operator(const Args &...args) {
            return make_shared<T>(args...);
        }
    };

public:
    // 注册器
    template <typename T> 
    struct register_t {
        register_t(const std::string &key) {
            Instance()->m_map.emplace(std::make_pair(key, procude_t<T>()));
        }
    };

public:
    // 生产函数
    auto produce(const std::string &key) { return m_Map.at(key)(); }
    template <typename... Args>
    auto produce(const std::string &key, const Args &...args) {
        return m_Map.at(key)(args...);
    }

private:
    std::unordered_map<std::string, procude_t> m_map;
};
