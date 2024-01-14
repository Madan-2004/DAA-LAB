import random

def generate_random_graph(num_nodes, max_edge_weight):
    # Initialize an empty adjacency matrix
    adjacency_matrix = [[0 for _ in range(num_nodes)] for _ in range(num_nodes)]

    # Populate the upper triangle of the matrix with random weights
    for i in range(num_nodes):
        for j in range(i + 1, num_nodes):
            edge_weight = random.randint(1, max_edge_weight)
            adjacency_matrix[i][j] = edge_weight
            adjacency_matrix[j][i] = edge_weight  # Since it's an undirected graph

    return adjacency_matrix

def write_graph_to_file(adjacency_matrix, filename):
    with open(filename, 'w') as file:
        for row in adjacency_matrix:
            file.write(' '.join(map(str, row)) + '\n')

def print_graph(adjacency_matrix):
    for row in adjacency_matrix:
        print(row)

# Example usage
num_nodes = 10
max_edge_weight = 100
output_filename = 'input_Q3.txt'

random_graph = generate_random_graph(num_nodes, max_edge_weight)
print("Random Weighted Graph (Adjacency Matrix):")
print_graph(random_graph)

# Write the graph to a file
write_graph_to_file(random_graph, output_filename)
print(f"Graph written to {output_filename}")
