int fonction1(int a, int b, int c, int d) {
	a=2;
    b=3;
    c=4;
    d=5;
    return a + b + c + d;
}


int main() {
    int a, b, c, d, ans;
    a = 1;
    b = 2;
    c = 3;
    d = 4;
    ans = fonction1(a, b, c, d);
    return ans;
}