import random
import networkx as nx

def generate_strongly_connected_graph_with_limited_successors(num_vertices):
    G = nx.DiGraph()
    G.add_nodes_from(range(1, num_vertices + 1))

    # Create a directed cycle to ensure strong connectivity
    for i in range(num_vertices):
        G.add_edge(i + 1, (i + 1) % num_vertices + 1)

    # Randomize edges while ensuring each vertex has at most 1 successor
    for u in range(1, num_vertices + 1):
        successors = list(G.successors(u))
        while len(successors) < 1:
            v = random.randint(1, num_vertices)
            if v != u and not G.has_edge(u, v) and v not in successors:
                G.add_edge(u, v)
                successors.append(v)

    # Randomize the edges in the graph
    edges = list(G.edges())
    random.shuffle(edges)
    G = nx.DiGraph()
    G.add_nodes_from(range(1, num_vertices + 1))
    G.add_edges_from(edges)

    return G

def save_graph_as_edge_list(G, filename):
    with open(filename, 'w') as f:
        f.write(f"{G.number_of_nodes()}\n")
        for u, v in G.edges():
            f.write(f"{u} {v}\n")

num_vertices = random.randint(10, 20)
G = generate_strongly_connected_graph_with_limited_successors(num_vertices)
save_graph_as_edge_list(G, "input.txt")

print("Strongly connected graph with limited successors and randomized edges saved to input.txt")
