int fonction1(int a, int b, int c, int d, int e, int f) {
    return (a + b* c + d + e + f);
}

int main() {
    int a, b, c, d, e, f, ans;
    a = 1;
    b = 2;
    c = 3;
    d = 4;
    e = 5;
    f = 6;
    ans = fonction1(a,fonction1(1,2,3,4,5,6),c,d,e,f);
    return ans;
}