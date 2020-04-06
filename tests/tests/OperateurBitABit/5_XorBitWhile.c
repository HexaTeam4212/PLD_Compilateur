int main() {
      int i,a,b,c;
      a = 20;
      b = 0;
      i = 0;
      while(i < 10) {
            if(a^b) {
                  c = c + 1;
            }
            i = i + 1;
      }

      return c;
}