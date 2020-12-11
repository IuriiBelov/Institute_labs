#include <cassert>
#include <iostream>

class Fibonacci {
 public:
  static int get_remainder(long long n, int m) {
    assert(n >= 1);
    assert(m >= 2);
    
    int r1 = 0;
    int r2 = 1;
    int temp;
    int p;
    for (p = 1; p <= 6 * m; p++) {
        temp = r2;
        r2 = (r1 + r2) % m;
        r1 = temp;
        if (r1 == 0 && r2 == 1)
            break;
    }
    
    n = (n + 1) % p;
    int * R = new int[p];
    R[0] = 0;
    R[1] = 1;
    for (int i = 2; i < p; i++)
        R[i] = (R[i - 1] + R[i - 2]) % m;
    int result;
    if (n == 0)
        result = R[p - 1];
    else
        result = R[n - 1];
    delete [] R;
    return result;
  }
};

int main(void) {
  long long n;
  int m;
  std::cin >> n >> m;
  std::cout << Fibonacci::get_remainder(n, m) << std::endl;
  return 0;
}