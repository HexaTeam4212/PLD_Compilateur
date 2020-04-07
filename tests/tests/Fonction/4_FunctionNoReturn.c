int fonction1(int a, int b, int c, int d, int e, int f) {
	a=2;
    b=3;
    c=4;
    d=5;
    e=6;
    f=7;
}

int main() {
    int a, b, c, d, e, f;
    a = 1;
    b = 2;
    c = 3;
    d = 4;
    e = 5;
    f = 6;
    fonction1(a, b, c, d, e, f);
    return a + b + c + d + e + f;
}