int main() {
      int a;
      a = 0;
      if(a) {
            a = 3;
      }
      else {
            a = 5;
            if(a) {
                  a = a + 1;
            }
      }
      return a;
}