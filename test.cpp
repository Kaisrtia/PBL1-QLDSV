#include<bits/stdc++.h>
using namespace std;

struct a {
    a* next;
    string name;
};
a *x = (a *)malloc(sizeof(a));
struct b {
    b *next;
    a *par;
    b(a *xx) {
        par = xx;
    }
};
b *c = new b(x);
b *d = new b(x);
int main() {
    cout << 1 << '\n';
    x->name = "Hoang Trung";
    c->par->name = "Haha";
    cout << c->par->name << '\n';
    cout << d->par->name << '\n';
    d->par->name = "Yeu em";
    cout << c->par->name;
    return 0;
}