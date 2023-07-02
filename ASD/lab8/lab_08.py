def partition(A, start_i, end_i, pivot):

    x = pivot
    i = start_i - 1
    j = start_i

    while j < end_i:

        if len(A[j][1]) <= len(x[1]):
            i += 1
            A[i], A[j] = A[j], A[i]

        j += 1

    A[i + 1], A[j] = A[j], A[i + 1]

    return i + 1

def QuickSortNorm(A, p = 0, r = None):

    if r is None:
        r = len(A)-1

    if p < r:
        q = partition(A, p, r, A[r])
        QuickSortNorm(A, p, q - 1)
        QuickSortNorm(A, q + 1, r)


class MyGraph:
    def __init__(self, matrix = None):
        if isinstance(matrix, int):
            self.matrix = [[0] * matrix for _ in range(matrix)]
        else:
            self.matrix = matrix

    def add_edge(self, u, v):
        self.matrix[u][v] = 1
        self.matrix[v][u] = 1

    def solve_vertex(self, vertex, color_pallet, v_i):
        assigned_color = color_pallet[v_i][1].pop(0)

        for i, data in enumerate(color_pallet):
            if self.matrix[vertex][data[0]] == 1:
                try:
                    color_pallet[i][1].remove(assigned_color)
                except ValueError: pass

        color_pallet[v_i][1] = [assigned_color]

        return assigned_color

    def color(self):
        color_pallet = [[a, list(range(len(self.matrix)))] for a in range(len(self.matrix))]
        color_num = -1

        i = 0

        while i < len(self.matrix):

            if len(color_pallet[i][1]) > 1:

                c = self.solve_vertex(color_pallet[i][0], color_pallet, i)

                QuickSortNorm(color_pallet, i)

                if len(color_pallet[0][1]) == 0: return -1, []

            else: c = color_pallet[i][1][0]

            if c > color_num: color_num = c

            i+=1

        return color_num + 1, color_pallet

if __name__ == "__main__":
    # Приклад використання
    graph = MyGraph(5)
    graph.add_edge(0, 1)
    graph.add_edge(0, 2)
    graph.add_edge(0, 3)
    graph.add_edge(0, 4)
    graph.add_edge(1, 2)
    graph.add_edge(1, 3)
    graph.add_edge(1, 4)
    graph.add_edge(2, 3)
    graph.add_edge(2, 4)
    graph.add_edge(3, 4)

    chromatic_number = graph.color()
    print("Хроматичне число графа:", chromatic_number)
