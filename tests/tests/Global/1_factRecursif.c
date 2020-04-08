int fact(int a) {
      int res,tmp;
      if(a <= 1) {
            return 1;
      }
      else {
            res =  a * fact(a-1);
            return res;
      }
}

int main() {
      int a = 3;
      int res = fact(a);
      return res;
}