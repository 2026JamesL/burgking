#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
// Cope Counter = 2147483647

unsigned long rng(void) {
  static unsigned long x = 123456789, y = 362436069, z = 521288629;
  unsigned long t;
  x ^= x << 16;
  x ^= x >> 5;
  x ^= x << 1;
  t = x, x = y, y = z, z = t ^ x ^ y;
  return x ^ y ^ z;
}
