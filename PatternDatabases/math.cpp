#include "math.h"

uint32_t factorial(uint32_t n) {
  if (n <= 1) return 1;

  return n * factorial(n - 1);
}

uint32_t pick(uint32_t n, uint32_t k) {
  return factorial(n) / factorial(n - k);
}

uint32_t choose(uint32_t n, uint32_t k) {
  if (n < k) return 0;

  return factorial(n) / (factorial(k) * factorial(n - k));
}