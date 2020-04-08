int fact(int a) {
      int res,resF,tmp;
      if(a <= 1) {
            return 1;
      }
      else {
            tmp = a - 1;
            resF = fact(tmp);
            res =  a * resF;
            return res;
      }
}

int main() {
      int res;
      int a = 3;
      res = fact(a);
      return res;
}