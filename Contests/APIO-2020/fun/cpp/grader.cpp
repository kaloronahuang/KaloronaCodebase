#include "fun.h"

#include <cassert>
#include <cstdio>

#include <algorithm>
#include <string>
#include <vector>

static void wrongAnswer(std::string message) {
  printf("WA: %s\n", message.c_str());
  exit(0);
}

namespace tree_helper {

static int N;
static int logN;
static std::vector<std::vector<int>> parent;
static std::vector<int> depth;
static std::vector<int> subtree_size;

static void dfs(
    const std::vector<std::vector<int>>& adj_list,
    int current_node, int parent_node) {
  parent[0][current_node] = parent_node;
  subtree_size[current_node] = 1;
  for (int i = 0; i < static_cast<int>(adj_list[current_node].size()); ++i) {
    const int next_node = adj_list[current_node][i];
    if (next_node != parent_node) {
      depth[next_node] = depth[current_node] + 1;
      dfs(adj_list, next_node, current_node);
      subtree_size[current_node] += subtree_size[next_node];
    }
  }
}

static void initializeTree(const std::vector<std::vector<int>>& adj_list) {
  N = static_cast<int>(adj_list.size());

  depth = std::vector<int>(N, 0);
  subtree_size = std::vector<int>(N, 0);
  for (logN = 0; (1 << logN) < N; ++logN) {}
  parent = std::vector<std::vector<int>>(logN, std::vector<int>(N, 0));

  dfs(adj_list, 0, 0);
  for (int i = 1; i < logN; ++i) {
    for (int j = 0; j < N; ++j) {
      parent[i][j] = parent[i - 1][parent[i - 1][j]];
    }
  }
}

static int getLowestCommonAncestor(int X, int Y) {
  if (depth[X] < depth[Y]) {
    std::swap(X, Y);
  }
  for (int i = logN - 1; i >= 0; --i) {
    if (depth[parent[i][X]] >= depth[Y]) {
      X = parent[i][X];
    }
  }
  if (X == Y) {
    return X;
  }
  for (int i = logN - 1; i >= 0; --i) {
    if (parent[i][X] != parent[i][Y]) {
      X = parent[i][X];
      Y = parent[i][Y];
    }
  }
  return parent[0][X];
}

static int getDistance(int X, int Y) {
  return depth[X] + depth[Y] - 2 * depth[getLowestCommonAncestor(X, Y)];
}

static int attractionsBehind(int X, int Y) {
  if (X == Y) {
    return N;
  }
  for (int i = logN - 1; i >= 0; --i) {
    if (depth[parent[i][X]] > depth[Y]) {
      X = parent[i][X];
    }
  }
  if (Y == parent[0][X]) {
    return N - subtree_size[X];
  }
  return subtree_size[Y];
}

static void checkFunTour(const std::vector<int>& fun_tour) {
  if (static_cast<int>(fun_tour.size()) != N) {
    wrongAnswer("Invalid size");
  }

  std::vector<bool> visited_attractions(N, false);
  for (int i = 0; i < N; ++i) {
    if (fun_tour[i] < 0 || fun_tour[i] >= N) {
      wrongAnswer("Invalid index");
    }
    if (visited_attractions[fun_tour[i]]) {
      wrongAnswer("Repeated index");
    }
    visited_attractions[fun_tour[i]] = true;
  }

  int last_travel_time = getDistance(fun_tour[0], fun_tour[1]);
  for (int i = 2; i < N; ++i) {
    int travel_time = getDistance(fun_tour[i - 1], fun_tour[i]);
    if (travel_time > last_travel_time) {
      wrongAnswer("Tour is not fun");
    }
    last_travel_time = travel_time;
  }
}

}  // namespace tree_helper

static int N, Q;

int hoursRequired(int X, int Y) {
  if (--Q < 0) {
    wrongAnswer("Too many queries");
  }
  if (X < 0 || X >= N || Y < 0 || Y >= N) {
    wrongAnswer("Invalid index");
  }
  return tree_helper::getDistance(X, Y);
}

int attractionsBehind(int X, int Y) {
  if (--Q < 0) {
    wrongAnswer("Too many queries");
  }
  if (X < 0 || X >= N || Y < 0 || Y >= N) {
    wrongAnswer("Invalid index");
  }
  return tree_helper::attractionsBehind(X, Y);
}

int main() {
  assert(2 == scanf("%d %d", &N, &Q));

  std::vector<std::vector<int>> adj_list(N);
  for (int i = 0; i < N - 1; ++i) {
    int A, B;
    assert(2 == scanf("%d %d", &A, &B));
    adj_list[A].push_back(B);
    adj_list[B].push_back(A);
  }
  tree_helper::initializeTree(adj_list);

  std::vector<int> fun_tour = createFunTour(N, Q);
  tree_helper::checkFunTour(fun_tour);

  for (int i = 0; i < N; ++i) {
    printf("%d%c", fun_tour[i], " \n"[i == N - 1]);
  }
  return 0;
}
