int main() {
      int a,b,c,d;
      a = 4;
      b = 1;
      while ( a != 0 ) {
            b = b * ( b + 1 );
            a = a - 1;
      }
      return b;
}