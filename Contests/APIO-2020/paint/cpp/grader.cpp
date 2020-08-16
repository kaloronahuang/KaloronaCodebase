#include "paint.h"

#include <cassert>
#include <cstdio>

#include <string>
#include <vector>

int main() {
  int N, M, K;
  assert(3 == scanf("%d %d %d", &N, &M, &K));
  
  std::vector<int> C(N);
  for (int i = 0; i < N; ++i) {
    assert(1 == scanf("%d", &C[i]));
  }

  std::vector<int> A(M);
  std::vector<std::vector<int>> B(M);
  for (int i = 0; i < M; ++i) {
    assert(1 == scanf("%d", &A[i]));
    B[i].resize(A[i]);
    for (int j = 0; j < A[i]; ++j) {
      assert(1 == scanf("%d", &B[i][j]));
    }
  }

  int minimum_instructions = minimumInstructions(N, M, K, C, A, B);
  printf("%d\n", minimum_instructions);
  
  return 0;
}
