import random
import tkinter as tk
import lab_08 as lab
import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors

def special_rand(a):
    return random.choice([*[0 for _ in range(a - 1)], 1])

def separate_function(matrix):

    print('-'*30)

    colors_list = list(mcolors.CSS4_COLORS.values())
    colors_num = len(colors_list)

    chromo_num, color_pallet = lab.MyGraph(matrix).color()

    translated_color_pallet = [0] * len(matrix)

    for i, a in color_pallet:
        translated_color_pallet[i] = a[0]

    for i, c in enumerate(translated_color_pallet):
        print(vertex_entries[i].get(), "-", colors_list[(c * 3) % colors_num])

    print(chromo_num)

    plt.close()

    G = nx.Graph(name="ASD")

    path_matrix = []

    for i, a in enumerate(matrix):
        for j, b in enumerate(a):
            if b > 0:
                path_matrix.append((i, j))

    routes = [path_matrix]

    G.add_nodes_from(range(len(matrix)))

    edges = []
    for r in routes:
        # route_edges = [(r[n],r[n+1]) for n in range(len(r)-1)]
        for e in r:
            G.add_edge(e[0], e[1], w=matrix[e[0]][e[1]])
        # G.add_edges_from(r)
        edges.append(r)


    # mapping = {a: vertex_entries[a].get() for a in range(len(matrix))}
    # G = nx.relabel_nodes(G, mapping)

    pos = nx.spring_layout(G)

    color_map = [colors_list[(translated_color_pallet[a] * 3) % colors_num] for a in range(len(matrix))]

    nx.draw_networkx_nodes(G, pos=pos, node_color = color_map)
    nx.draw_networkx_labels(G, pos=pos, labels={a: vertex_entries[a].get() for a in range(len(matrix))})

    colors = ['gray']
    linewidths = [5]
    for ctr, edgelist in enumerate(edges):
        nx.draw_networkx_edges(G, pos=pos, edgelist=edgelist, edge_color=colors[ctr], width=linewidths[ctr])
    # edgelist = nx.get_edge_attributes(G, 'w')

    # nx.draw_networkx_edge_labels(G, pos=pos, edge_labels=edgelist, verticalalignment="bottom")

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
    for a in vertex_labels:
        a.grid_forget()
    for a in vertex_entries:
        a.grid_forget()

    size = int(matrix_size.get())

    matrix_entries.clear()
    matrix_labels.clear()
    vertex_labels.clear()
    vertex_entries.clear()


    for i in range(size):
        labelV = tk.Label(
            root,
            text = i + 1,
            width=1,
            height=1
        )
        labelH = tk.Label(
            root,
            text = i + 1,
            width=1,
            height=1
        )

        entryVertx = tk.Entry(
            root
        )
        labelVertx = tk.Label(
            root,
            text=i + 1,
            width=1,
            height=1
        )

        entryVertx.insert(0, chr(i + ord("A")))

        entryVertx.grid(row = i+offsetY + 1, column = 1)
        labelVertx.grid(row = i+offsetY + 1, column = 0)

        labelH.grid(row=offsetY, column=i + offsetX + 1)
        labelV.grid(row=i + offsetY + 1, column=offsetX)
        matrix_labels.append(labelH)
        matrix_labels.append(labelV)
        vertex_labels.append(labelVertx)
        vertex_entries.append(entryVertx)

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
            matrix_entries[i][j].insert(0, special_rand(2) if j > i else 0)


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
vertex_labels = []
vertex_entries = []
update_table()

root.mainloop()
