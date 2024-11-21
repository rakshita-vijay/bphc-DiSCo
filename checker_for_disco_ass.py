import random
import subprocess
import os
import time

def generate_dag(n, m, filename="a.txt"):
    """Generates a Directed Acyclic Graph (DAG) with n nodes and m edges."""
    random.seed(n + m)  # Ensure reproducibility for different n and m

    edges = set()

    while len(edges) < m:
        a = random.randint(1, n - 1)  # Start node
        b = random.randint(a + 1, n)  # End node (ensure a < b)
        edges.add((a, b))

    with open(filename, "w") as f:
        f.write(f"{n} {m}\n")
        for a, b in edges:
            f.write(f"{a} {b}\n")

def expected_output(n, m, input_file, output_file):
    """Generates the expected output for a given input DAG."""
    with open(input_file, "r") as f:
        n, m = map(int, f.readline().strip().split())
        edges = [[] for _ in range(n)]
        in_degree = [0] * n

        for line in f:
            a, b = map(int, line.strip().split())
            edges[a - 1].append(b - 1)
            in_degree[b - 1] += 1

    rounds = []
    visited = [False] * n

    while True:
        current_round = []
        for i in range(n):
            if in_degree[i] == 0 and not visited[i]:
                current_round.append(i)
                visited[i] = True

        if not current_round:
            break

        current_round.sort()
        rounds.append(current_round)

        for node in current_round:
            for neighbor in edges[node]:
                in_degree[neighbor] -= 1

    with open(output_file, "w") as f:
        f.write(f"{len(rounds)}\n")
        for round_ in rounds:
            f.write(" ".join(str(x + 1) for x in round_) + "\n")

def compare_files(file1, file2):
    """Compares two files line by line and returns True if they match."""
    with open(file1, "r") as f1, open(file2, "r") as f2:
        lines1 = [line.rstrip() for line in f1]
        lines2 = [line.rstrip() for line in f2]

    if lines1 == lines2:
        return True
    else:
        print("Differences found:")
        for i, (line1, line2) in enumerate(zip(lines1, lines2), start=1):
            if line1 != line2:
                print(f"Line {i}:")
                print(f"  Output: {line1}")
                print(f"  Expected: {line2}")
        return False

def normalize_lines(file_path):
    """Normalizes line endings in a file to Unix-style."""
    with open(file_path, "r") as f:
        lines = f.readlines()
    with open(file_path, "w") as f:
        for line in lines:
            f.write(line.rstrip() + "\n")

def main():
    input_file = "a.txt"
    program_output = "b.txt"
    expected_output_file = "expected_b.txt"
    executable = "./Rakshita_20232010"  # Update this if your executable has a different name
    source_code = "Rakshita_20232010.c"  # Update this if your source code file has a different name

    print("Compiling the C program...")
    compile_result = subprocess.run(["gcc", "-o", "Rakshita_20232010", source_code])
    if compile_result.returncode != 0:
        print("Compilation failed!")
        return

    # Generate 1000 test cases
    for test_num in range(1, 1001):
        print(f"\nRunning test case {test_num}...")

        # Generate random n and m values
        if test_num <= 50:
            n = random.randint(2, 10)
            m = random.randint(1, min(20, n * (n - 1) // 2))
        elif test_num <= 200:
            n = random.randint(10, 100)
            m = random.randint(1, min(500, n * (n - 1) // 2))
        elif test_num <= 600:
            n = random.randint(100, 1000)
            m = random.randint(1, min(5000, n * (n - 1) // 2))
        elif test_num <= 900:
            n = random.randint(1000, 10000)
            m = random.randint(1, min(100000, n * (n - 1) // 2))
        else:
            n = random.randint(10000, 100000)
            m = random.randint(1, min(500000, n * (n - 1) // 2))

        generate_dag(n, m, input_file)

        start_time = time.time()
        run_result = subprocess.run([executable], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        end_time = time.time()
        c_program_time = end_time - start_time

        if run_result.returncode != 0:
            print("Error while running the C program:")
            print(run_result.stderr.decode())
            continue

        # Generate expected output using Python
        expected_output(n, m, input_file, expected_output_file)

        # Normalize line endings in output files
        normalize_lines(program_output)
        normalize_lines(expected_output_file)

        # Compare outputs
        outputs_match = compare_files(program_output, expected_output_file)

        if outputs_match:
            print(f"Test case {test_num} with n = {n} and m = {m}: Passed in {c_program_time:.4f} seconds")
        else:
            print(f"Test case {test_num} with n = {n} and m = {m}: Failed")
            break  # Stop on failure for debugging

if __name__ == "__main__":
    main()
