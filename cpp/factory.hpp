#pragma once

#include "macro.h"
#include "singleton.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <utility>

template <typename base>
class factory : public singleton<factory<base>> {
public:
    // ×¢²áÆ÷
    template <typename impl>
    struct register_t {
        register_t(const std::string &key) {
            factory<base>::instance()->m_map.emplace(std::make_pair(key, []() {
                return std::static_pointer_cast<base>(std::make_shared<impl>());
            }));
        }
        template <typename... Args>
        register_t(const std::string &key, Args &&...args) {
            factory<base>::instance()->m_map.emplace(std::make_pair(key, [=]() mutable {
                return std::static_pointer_cast<base>(std::make_shared<impl>(std::forward<Args>(args)...));
            }));
        }
    };

public:
    // Éú²úº¯Êý
    std::shared_ptr<base> produce(const std::string &key) { return m_map.at(key)(); }

private:
    std::unordered_map<std::string, std::function<std::shared_ptr<base>()>> m_map;
};

#define FACTORY_REGISTERED(base, impl, ...) factory<base>::register_t<impl> CONNECT_STR3(base, impl, __LINE__, ##__VA_ARGS__);