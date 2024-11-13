# Flip Coin Game

## Acknowledgments

Special thanks to [RBrossard](https://github.com/RBrossard) for not inventing this well-known problem.

## Problem Overview

This game involves two players who can strategize before it starts but cannot communicate once the game begins. The goal is for Player 2 to identify a specific "target" coin on an `n x n` board based on Player 1’s actions.

### Game Rules

1. The game board is an `n x n` grid, where `n` is a power of 2 (e.g., 1, 2, 4, 8, ...).
2. Each cell on the board contains a coin.
3. Player 1 is informed by the host of a specific "target" coin on the board.
4. Player 1 must flip exactly one coin on the board to provide a clue to Player 2 about the target coin.
5. Player 2, upon seeing the board with the flipped coin, must identify the target coin based on the pre-agreed strategy.

## Your Task

Implement two classes, `Player1` and `Player2`, each with a specific function:

### Player1 Class

The `Player1` class simulates the first player's actions.

```cpp
class Player1 {
public:
    pair<int, int> flip(const vector<vector<int>>& board, const pair<int, int>& target);
};
```

- **flip**: Given the `board` and the `target` coordinates, this function returns the coordinates of the coin that Player 1 chooses to flip. The flipped coin is intended to communicate the location of the target coin to Player 2.

### Player2 Class

The `Player2` class simulates the second player's actions.

```cpp
class Player2 {
public:
    pair<int, int> solve(const vector<vector<int>>& board);
};
```

- **solve**: Given the `board` with one coin already flipped by Player 1, this function identifies the target coin's coordinates based on the pre-discussed strategy.

## Example Usage

The `main.cpp` file demonstrates the game flow:

```cpp
#include <bits/stdc++.h>
using namespace std;

// Definitions for Player1 and Player2 classes...

class Host {
    // Host class definition...
};

void visualize(int n) {
    Host host(n);
    host.print_board();
    host.flip();
    host.print_flipped_board();
    auto solution = host.solve();
    cout << "Solution: (" << solution.first << ", " << solution.second << ")\n\n";
}

void complete_test(int n, int iterations = 1000) {
    for (int x = 0; x < iterations; ++x) {
        Host host(n);
        for (int i = 0; i < (1 << n); ++i)
            for (int j = 0; j < (1 << n); ++j) {
                host.setTarget(i, j);
                host.flip();
                if (!host.check(host.solve())) {
                    cout << "Test failed\n";
                    exit(EXIT_FAILURE);
                }
            }
    }
    cout << "All tests passed!\n";
}

int main() {
    int n = 3;  // Example board size: 8x8 (2^3 x 2^3)
    visualize(n);
    complete_test(n);
    return 0;
}
```

### Explanation

- **Host Class**: Manages the board, sets up the game, and validates solutions.
- **visualize**: Prints the board and displays the flipped board to simulate Player 1's and Player 2's actions.
- **complete_test**: Runs multiple iterations to test all possible target positions on the board.

This example illustrates how `Player1` flips a coin to encode the target location, while `Player2` decodes this to identify the target based on the shared strategy.

