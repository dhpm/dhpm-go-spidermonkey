#include <spidermonkey.h>

int fact(int n) {
    if (n <= 1) {
        return 1;
    }

    return n * fact(n - 1);
}

int my_mod(int x, int y) {
    return x % y;
}
