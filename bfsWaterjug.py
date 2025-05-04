from collections import deque

def solveWaterJugProblem(capacity_jug1, capacity_jug2, desired_quantity):
    queue = deque()
    queue.append((0, 0, []))  # Initial state: both jugs empty, with an empty path
    visited = set()

    print("\nAll the traversed States")
    while queue:
        current_state = queue.popleft()  # BFS uses queue: pop from front
        jug1, jug2, path = current_state

        # Print current state
        print(f"Current State: Jug A = {jug1}, Jug B = {jug2}")

        if jug1 == desired_quantity or jug2 == desired_quantity:
            path.append((jug1, jug2))
            print("Solution found:")
            for state in path:
                print(f"Jug A = {state[0]}, Jug B = {state[1]}")
            return

        if (jug1, jug2) in visited:
            continue

        visited.add((jug1, jug2))
        path.append((jug1, jug2))

        next_states = generateNextStates((jug1, jug2), capacity_jug1, capacity_jug2)
        for state in next_states:
            queue.append((state[0], state[1], path.copy()))  # Add new state to queue

    print("No solution found")

def generateNextStates(state, capacity_jug1, capacity_jug2):
    next_states = []
    jug1, jug2 = state

    # Fill Jug 1
    next_states.append((capacity_jug1, jug2))

    # Fill Jug 2
    next_states.append((jug1, capacity_jug2))

    # Empty Jug 1
    next_states.append((0, jug2))

    # Empty Jug 2
    next_states.append((jug1, 0))

    # Pour water from Jug 1 to Jug 2
    pour_amount = min(jug1, capacity_jug2 - jug2)
    next_states.append((jug1 - pour_amount, jug2 + pour_amount))

    # Pour water from Jug 2 to Jug 1
    pour_amount = min(jug2, capacity_jug1 - jug1)
    next_states.append((jug1 + pour_amount, jug2 - pour_amount))

    return next_states

if __name__ == "__main__":
    a = int(input("Enter jug A capacity: "))
    b = int(input("Enter jug B capacity: "))
    t = int(input("Enter target capacity: "))

    solveWaterJugProblem(a, b, t)
