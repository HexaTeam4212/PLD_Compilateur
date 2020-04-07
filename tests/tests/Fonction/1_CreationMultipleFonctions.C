int fonction1() {
	int a;
	a=2;
      return a;
}

int fonction2(){
      int b;
      b=3;
      return b;
}

int main() {
      int a, b, ans;
      a = fonction1();
      b = fonction2();
      ans = a + b;
      return ans;
}