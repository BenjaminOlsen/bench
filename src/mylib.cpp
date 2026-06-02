#include "mylib.h"

long long sum(const std::vector<int>& data) {
  long long total = 0;
  for (int v : data) {
    total += v;
  }
  return total;
}

bool has_duplicate(const std::vector<int>& data) {
  for (std::size_t i = 0; i < data.size(); ++i) {
    for (std::size_t j = i + 1; j < data.size(); ++j) {
      if (data[i] == data[j]) {
        return true;
      }
    }
  }
  return false;
}

int collatz(const std::vector<int>& data) {
    int cnt = 0;

    for (auto n : data) {
        while (n && n != 1) {
            if (n & 1) {
                n = (n << 1) + n + 1;
            } else {
                n >>= 1;
            }

            ++cnt;
        }
    }
    return cnt;
}

