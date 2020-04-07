int f(int alpha, int beta) {
      int res;
      int i;
      i = 0;
      while(i < 27) {
            res = res + (alpha+i) ^ (beta * 5);
            i = i + 1;
      }
      return res;
}

int main() {
      int alpha,b,c,d;
      alpha = 4;
      b = 8;
      c = f(alpha,b);
      d = c * alpha + 2;
      return d;
}