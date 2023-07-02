def set_vals(a, b):
    for c in range(len(a)):
        a[c] = b[c]

def my_min(l):
    m = 0
    for a in range(1, len(l)):
        if (l[m] == 0) or (l[m] > l[a] != 0): m = a

    return m

def print_m(m):
    print("   ", end="")

    for a in range(len(m)):
        print(chr(ord("A") + a), end="   ")

    for a, b in enumerate(m):
        print("\n"+chr(ord("A") + a) + ": ", end="")
        for c in b:
            print(c, end="   ")

    print()

def find_tree(matrix):
    trees = []
    MST = []

    def append_to_tree(a, b, w):
        for tree in trees:
            if a in tree or b in tree:
                if a not in tree:
                    tree.append(a)
                if b not in tree:
                    tree.append(b)

                break

        else:
            trees.append([a, b])

        MST.append([a, b, w])

    for i, row in enumerate(matrix):
        min_index = my_min(row)

        append_to_tree(i, min_index, row[min_index])

    return trees, MST

def unite_trees(trees, matrix):

    MST = []

    def find_easy_path(_paths):
        m = _paths[0]
        for i in range(1, len(_paths)):
            if (m[2] == 0) or (m[2] > _paths[i][2] > 0):
                m = _paths[i]

        return m

    def merge_trees(tree1, tree2):
        tree1.extend(tree2)

    while len(trees) > 1:

        print(trees)

        paths = []

        for i, a in enumerate(trees[0]):
            for j, b in enumerate(trees[1]):
                paths.append([a, b, matrix[a][b]])

        best_p = find_easy_path(paths)

        MST.append(best_p)

        merge_trees(trees[0], trees.pop(1))

    print(trees, MST)

    return MST

def boruvkaMST(matrix):

    trees, MST = find_tree(matrix)

    print(trees, MST)

    MST.extend(unite_trees(trees, matrix))

    for way in MST:
        if [way[1], way[0], way[2]] in MST:
            MST.remove([way[1], way[0], way[2]])

    print(MST)

    return MST

if __name__ == "__main__":
    res = boruvkaMST([[0, 7, 0, 4, 0, 0, 0], [7, 0, 11, 9, 10, 0, 0], [0, 11, 0, 0, 5, 0, 0], [4, 9, 0, 0, 15, 6, 0], [0, 10, 5, 15, 0, 12, 8], [0, 0, 0, 6, 12, 0, 13], [0, 0, 0, 0, 8, 13, 0]])
    print(res)
