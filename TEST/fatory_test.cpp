#include <iostream>
#include "../factory/factory.hpp"

using namespace std;

struct a {
    void do_func() { 
        cout << "a:" << endl;
    }
};
struct b {
    b(int x = 0) : m_x(x) {}
    void do_func() { cout << "b:" << m_x << endl; }
    int m_x;
};
factory::register_t<a> reg_a("a");
factory::register_t<b> reg_b("b");

int main() { 
    auto xa = factory::instance()->produce("a");
    auto xb0 = factory::instance()->produce("b");
    auto xb1 = factory::instance()->produce("b", 10086);
    xa->do_func();
    xb0->do_func();
    xb1->do_func();
    return 0;
}