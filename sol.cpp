#include <bits/stdc++.h>

using namespace std;

class Player1 {
public:
    pair<int,int> flip(const vector<vector<int>> & board, const pair<int,int> & target) {
        int total_xor = 0;
        for (int i = 0 ; i < board.size() ; ++i) for (int j = 0 ; j < board.size() ; ++j) {
            if (board[i][j]) {
                total_xor ^= i * board.size() + j;
            }
        }
        total_xor ^= target.first * board.size() + target.second;
        return make_pair(total_xor / board.size(), total_xor % board.size());
    }
};

class Player2 {
public:
    pair<int,int> solve(const vector<vector<int>> & board) {
        int total_xor = 0;
        for (int i = 0 ; i < board.size() ; ++i) for (int j = 0 ; j < board.size() ; ++j) {
            if (board[i][j]) {
                total_xor ^= i * board.size() + j;
            }
        }

        return make_pair(total_xor / board.size(), total_xor % board.size());
    }
};


class Host {
public:
    void init(int n) { // board_edge = (1<<n)
        srand(time(0));

        board_edge = 1<<n;

        board = vector<vector<int>>(board_edge, vector<int>(board_edge));
        for (int i = 0 ; i < board_edge ; ++i) for (int j = 0 ; j < board_edge ; ++j) {
            board[i][j] = rand() % 2;
        }

        target = make_pair(rand() % board_edge, rand() % board_edge);

    }

    void print_board() const {
        cout << "board size: " << board_edge << " x " << board_edge << "\n\n";
        
        for (int i = 0 ; i < board_edge ; ++i) {
            for (int j = 0 ; j < board_edge ; ++j) {
                cout << board[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";

        cout << "target: (" << target.first << ", " << target.second << ")\n\n";

    }

    void print_flipped_board() const {
        cout << "board size: " << board_edge << " x " << board_edge << "\n\n";
        
        for (int i = 0 ; i < board_edge ; ++i) {
            for (int j = 0 ; j < board_edge ; ++j) {
                if (board[i][j] != flipped_board[i][j])
                    cout << "\033[31m"  << flipped_board[i][j] << "\033[0m ";
                else
                    cout << flipped_board[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    void setTarget(int x, int y) {
        target.first = x;
        target.second = y;
    }

    const vector<vector<int>> & get_board() const {
        return board;
    }

    const vector<vector<int>> & get_flipped_board() const {
        return flipped_board;
    }

    bool check(const pair<int,int> & solution) const {
        return solution == target;
    }

    Host(int n) {
        init(n);
    }

    const pair<int,int> & getTarget() const {
        return target;
    }

    void flip() {
        flipped_board = board;
        auto flipped = player1.flip(board, target);
        if (flipped.first < 0 || flipped.first >= board_edge || flipped.second < 0 || flipped.second >= board_edge) return ;
        flipped_board[flipped.first][flipped.second] ^= 1;
    }

    pair<int,int> solve() {
        return player2.solve(flipped_board);
    }

private:
    int board_edge;
    vector<vector<int>> board;
    vector<vector<int>> flipped_board;
    pair<int,int> target;
    Player1 player1;
    Player2 player2;
};

void visualize(int n) {
    Host host(n);
    host.print_board();
    host.flip();
    host.print_flipped_board();
    auto solution = host.solve();
    cout << "solution: (" << solution.first << ", " << solution.second << ")\n\n";
}

void complete_test(int n, int iterations = 1000) {
    for (int x = 0 ; x < 1000 ; ++x) {
        Host host(n);
        for (int i = 0 ; i < (1<<n) ; ++i) for (int j = 0 ; j < (1<<n) ; ++j) {
            host.setTarget(i, j);
            host.flip();
            if (!host.check(host.solve())) {
                cout << "Fail\n";
                exit(EXIT_FAILURE);
            }
        }
    }
    cout << "Passed all tests !\n";
}

int main() {
    int n = 3; // board size would be (1<<n) * (1<<n)
    visualize(n);

    complete_test(n);
    

    return 0;
}