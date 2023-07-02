class BinaryTreeNode:
    def __init__(self, data):
        self.data = data
        self.leftChild = None
        self.rightChild = None

def calculate(pre_arr: [BinaryTreeNode], _target):

    chains = []

    i = 1

    while i < len(pre_arr) - 1:
        if pre_arr[i].data == pre_arr[i + 1].data == 0:

            j = i - 1

            _sum = pre_arr[j].data

            j -= 1

            while _sum < _target and j >= 0:
                _sum += pre_arr[j].data
                j -= 1

            if _sum == _target:
                chains.append(parce_order(pre_arr[j+1:i]))

            pre_arr.pop(i - 1)
            pre_arr.pop(i - 1)

            i = 1

        i+=1

    return chains



def fillin(_root: BinaryTreeNode, _arr):

    _i = 0

    node_list = inorder(_root)

    while _i < len(_arr):
        node = node_list.pop(0)

        if node.data != 0:
            node.data = _arr[_i]
            _i += 1

def preorder(_root: BinaryTreeNode):

    _res = []

    _res.append(_root)
    if _root.leftChild is not None: _res.extend(preorder(_root.leftChild))
    if _root.rightChild is not None: _res.extend(preorder(_root.rightChild))

    return _res

def inorder(_root: BinaryTreeNode):
    _res = []

    if _root.leftChild is not None: _res.extend(inorder(_root.leftChild))
    _res.append(_root)
    if _root.rightChild is not None: _res.extend(inorder(_root.rightChild))

    return _res

def build_from_arr(_arr):

    if len(_arr) == 0:
        return BinaryTreeNode(None)

    res = BinaryTreeNode(_arr.pop(0))

    if res.data == 0: return res

    res.leftChild = build_from_arr(_arr)
    res.rightChild = build_from_arr(_arr)

    return res

def print_order(l):
    print(list(map(get_data, l)))
def parce_order(l):
    return list(map(get_data, l))

def get_data(a: BinaryTreeNode): return a.data

if __name__ == "__main__":
    import sys, os

    file_name = ".".join(sys.argv[1].split(".")[:-1])
    find = int(sys.argv[2])

    with open(file_name+".txt", "r") as f:
        data = f.readline()

    arr = list(map(int, data.split()))

    root = build_from_arr(arr)

    res = list(map(get_data, inorder(root)))

    res.sort()

    new_res = res[len(res) - res[::-1].index(0):]

    fillin(root, new_res)

    chains = calculate(preorder(root), find)

    for a in chains:
        while 0 in a:
            a.remove(0)

    str_meds = "\n".join([" ".join(list(map(str, a))) for a in chains])

    with open("_".join(["output", *file_name.split("_")[1:], str(find)]) + ".txt", "w") as f_o_m:
        f_o_m.write(str_meds)
