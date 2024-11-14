import networkx as nx
import matplotlib.pyplot as plt

def load_graph_from_file(filename):
    G = nx.DiGraph()
    with open(filename, 'r') as f:
        num_vertices = int(f.readline().strip())
        G.add_nodes_from(range(num_vertices))
        for line in f:
            u, v = map(int, line.strip().split())
            G.add_edge(u, v)
    
    return G

def visualize_graph(G):
    pos = nx.spring_layout(G)
    plt.figure(figsize=(8, 6))
    nx.draw(G, pos, with_labels=True, node_size=500, node_color="white", edgecolors="black", font_weight="bold", font_size=10, arrows=True)
    nx.draw_networkx_edges(G, pos, edge_color="black", arrows=True, arrowstyle='->', arrowsize=20)
    plt.show()

# filename = "output.txt"
filename = "input2.txt"
G = load_graph_from_file(filename)
visualize_graph(G)
print(f"Graph loaded from {filename} and visualized")



# 10
# 1 2
# 2 3
# 3 5
# 5 4
# 5 6
# 4 8
# 7 8
# 6 9
# 9 10
# 10 10