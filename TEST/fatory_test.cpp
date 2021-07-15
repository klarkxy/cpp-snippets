#include "../cpp/factory.hpp"
#include <iostream>

using namespace std;

struct base {
    base() { cout << "construct base" << endl; }
    virtual void do_func() { cout << "base:" << endl; }
};
struct a : public base {
    a() { cout << "construct a" << endl; }
    virtual void do_func() { cout << "a:" << endl; }
};
struct b : public a {
    b() { cout << "construct b" << endl; }
    b(int x) : m_x(x) { cout << "construct b(" << x << ")" << endl; }
    virtual void do_func() { cout << "b:" << m_x << endl; }
    int m_x;
};

factory<base>::register_t<a> reg_a("a");
factory<base>::register_t<b> reg_b("b", 10086);
factory<base>::register_t<b> reg_b2("b2", 10087);

int main() {

    auto xa = factory<base>::instance()->produce("a");
    auto xb0 = factory<base>::instance()->produce("b");
    auto xb2 = factory<base>::instance()->produce("b2");

    xa->do_func();
    xb0->do_func();
    xb2->do_func();
    return 0;
}

// ./../cpp/factory.hpp:18:13: warning: use of member 'instance' found via unqualified lookup into dependent bases of class templates is a Microsoft       
//      extension [-Wmicrosoft-template]