import random
import tkinter as tk
import lab_04
import networkx as nx
import matplotlib.pyplot as plt

def special_rand(a):
    return random.choice([*[0 for _ in range(a)], *list(range(a))])

def separate_function(matrix):
    MST = IP24_Razbeiko_04.boruvkaMST(matrix)

    weight = 0

    for a, b, w in MST:
        print(chr(a + ord("A")), "-", chr(b + ord("A")), w)
        weight += w

    print("Weight:", weight)


    plt.close()

    G = nx.Graph(name="ASD")

    path_matrix = []

    for i, a in enumerate(matrix):
        for j, b in enumerate(a):
            if b > 0:
                path_matrix.append((chr(i + ord("A")), chr(j + ord("A"))))

    path_MST = []

    for i, a in enumerate(MST):
        path_MST.append((chr(a[0] + ord("A")), chr(a[1] + ord("A"))))

    routes = [path_matrix, path_MST]

    G.add_nodes_from(range(len(matrix)))
    mapping = {a: chr(a + ord("A")) for a in range(len(matrix))}
    G = nx.relabel_nodes(G, mapping)

    edges = []
    for r in routes:
        # route_edges = [(r[n],r[n+1]) for n in range(len(r)-1)]
        for e in r:
            G.add_edge(e[0], e[1], w=matrix[ord(e[0]) - ord("A")][ord(e[1]) - ord("A")])
        # G.add_edges_from(r)
        edges.append(r)

    pos = nx.spring_layout(G)
    nx.draw_networkx_nodes(G, pos=pos)
    nx.draw_networkx_labels(G, pos=pos)
    colors = ['b', 'r', 'y']
    linewidths = [10, 5, 5]
    for ctr, edgelist in enumerate(edges):
        nx.draw_networkx_edges(G, pos=pos, edgelist=edgelist, edge_color=colors[ctr], width=linewidths[ctr])

    edgelist = nx.get_edge_attributes(G, 'w')

    nx.draw_networkx_edge_labels(G, pos=pos, edge_labels=edgelist, verticalalignment="bottom")

    plt.show()

def get_matrix():
    size = int(matrix_size.get())

    matrix = [[0 for _ in range(size)] for _ in range(size)]

    for i in range(size):
        for j in range(size):
            matrix[i][j] = (int(matrix_entries[i][j].get())) if j > i else (int(matrix_entries[j][i].get()))

    separate_function(matrix)


def update_table():

    offsetX = 5
    offsetY = 1

    for i in range(len(matrix_entries)):
        for j in range(len(matrix_entries)):
            matrix_entries[i][j].grid_forget()

    for a in matrix_labels:
        a.grid_forget()

    size = int(matrix_size.get())

    matrix_entries.clear()
    matrix_labels.clear()


    for i in range(size):
        labelV = tk.Label(
            text = chr(ord("A") + i),
            width=1,
            height=1
        )
        labelH = tk.Label(
            text = chr(ord("A") + i),
            width=1,
            height=1
        )
        labelH.grid(row=offsetY, column=i + offsetX + 1)
        labelV.grid(row=i + offsetY + 1, column=offsetX)
        matrix_labels.append(labelH)
        matrix_labels.append(labelV)

    for i in range(size):
        row_entries = []
        for j in range(size):

            entry = tk.Entry(root, width = 3)
            entry.grid(
                row=i + offsetY + 1,
                column=j + offsetX + 1
            )
            entry.insert(0, "0")
            if j <= i: entry.config(state = "disabled")
            row_entries.append(entry)
        matrix_entries.append(row_entries)

def set_rand():
    size = int(matrix_size.get())

    for i in range(size):
        for j in range(size):
            matrix_entries[i][j].delete(0, tk.END)
            matrix_entries[i][j].insert(0, special_rand(30) if j > i else 0)


root = tk.Tk()
root.title("Matrix Input")

matrix_size_label = tk.Label(root, text="Matrix size:")
matrix_size_label.grid(row=0, column=0)

matrix_size = tk.Entry(root)
matrix_size.grid(row=0, column=1)
matrix_size.insert(0, "7")

update_button = tk.Button(root, text="Update Table", command=update_table)
update_button.grid(row=0, column=2)

submit_button = tk.Button(root, text="Submit", command=get_matrix)
submit_button.grid(row=0, column=3)

submit_button = tk.Button(root, text="Rand", command=set_rand)
submit_button.grid(row=0, column=4)

matrix_entries = []
matrix_labels = []
update_table()

root.mainloop()
