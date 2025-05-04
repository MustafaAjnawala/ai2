#include <iostream>
#include <queue>
#include <set>

using namespace std;

struct State {
    int jugA, jugB;
    string path;

    State(int a, int b, string p) : jugA(a), jugB(b), path(p) {}

    bool operator==(const State& other) const {
        return jugA == other.jugA && jugB == other.jugB;
    }
};

int main() {
    int capacityA, capacityB, target;

    cout << "Enter capacity of jug A: ";
    cin >> capacityA;
    cout << "Enter capacity of jug B: ";
    cin >> capacityB;
    cout << "Enter target amount: ";
    cin >> target;

    queue<State> q;
    set<pair<int, int>> visited; // Keep track of visited states

    q.push(State(0, 0, "")); // Initial state: both jugs empty
    visited.insert({0, 0});

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        cout << "Current State: Jug A = " << current.jugA << ", Jug B = " << current.jugB << endl; // Print current state
        if (current.jugA == target || current.jugB == target) {
            cout << "Solution found:\n" << current.path;
            cout << "Final State: Jug A = " << current.jugA << ", Jug B = " << current.jugB << endl;
            return 0;
        }

        // Possible actions:

        // 1. Fill jug A
        if (current.jugA < capacityA) {
            State next(capacityA, current.jugB, current.path + "Fill A\nState: Jug A = " + to_string(capacityA) + ", Jug B = " + to_string(current.jugB) + "\n");
            if (visited.find({next.jugA, next.jugB}) == visited.end()) {
                q.push(next);
                visited.insert({next.jugA, next.jugB});
            }
        }

        // 2. Fill jug B
        if (current.jugB < capacityB) {
            State next(current.jugA, capacityB, current.path + "Fill B\nState: Jug A = " + to_string(current.jugA) + ", Jug B = " + to_string(capacityB) + "\n");
            if (visited.find({next.jugA, next.jugB}) == visited.end()) {
                q.push(next);
                visited.insert({next.jugA, next.jugB});
            }
        }

        // 3. Empty jug A
        if (current.jugA > 0) {
            State next(0, current.jugB, current.path + "Empty A\nState: Jug A = 0, Jug B = " + to_string(current.jugB) + "\n");
            if (visited.find({next.jugA, next.jugB}) == visited.end()) {
                q.push(next);
                visited.insert({next.jugA, next.jugB});
            }
        }

        // 4. Empty jug B
        if (current.jugB > 0) {
            State next(current.jugA, 0, current.path + "Empty B\nState: Jug A = " + to_string(current.jugA) + ", Jug B = 0\n");
            if (visited.find({next.jugA, next.jugB}) == visited.end()) {
                q.push(next);
                visited.insert({next.jugA, next.jugB});
            }
        }

        // 5. Pour from A to B
        int pourAmount = min(current.jugA, capacityB - current.jugB);
        if (pourAmount > 0) {
            State next(current.jugA - pourAmount, current.jugB + pourAmount, current.path + "Pour A to B\nState: Jug A = " + to_string(current.jugA - pourAmount) + ", Jug B = " + to_string(current.jugB + pourAmount) + "\n");
            if (visited.find({next.jugA, next.jugB}) == visited.end()) {
                q.push(next);
                visited.insert({next.jugA, next.jugB});
            }
        }

        // 6. Pour from B to A
        pourAmount = min(current.jugB, capacityA - current.jugA);
        if (pourAmount > 0) {
            State next(current.jugA + pourAmount, current.jugB - pourAmount, current.path + "Pour B to A\nState: Jug A = " + to_string(current.jugA + pourAmount) + ", Jug B = " + to_string(current.jugB - pourAmount) + "\n");
            if (visited.find({next.jugA, next.jugB}) == visited.end()) {
                q.push(next);
                visited.insert({next.jugA, next.jugB});
            }
        }
    }

    cout << "No solution found." << endl;
    return 0;
}