#pragma once

#include <cstddef>
#include <vector>

// Sum of all elements in a vector. O(n)
long long sum(const std::vector<int>& data);

// Naive check for whether the vector contains a duplicate value.
// O(n^2) — 
bool has_duplicate(const std::vector<int>& data);

int collatz(const std::vector<int>& data);
