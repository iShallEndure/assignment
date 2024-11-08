class BTreeNode:
    def __init__(self, t, leaf=False):
        self.t = t
        self.leaf = leaf
        self.keys = []
        self.children = []

class BTree:
    def __init__(self, t):
        self.root = BTreeNode(t, True)
        self.t = t

    def search(self, node, file_name):
        i = 0
        while i < len(node.keys) and file_name > node.keys[i]:
            i += 1
        if i < len(node.keys) and file_name == node.keys[i]:
            return node.children[i]
        if node.leaf:
            return None
        return self.search(node.children[i], file_name)

    def insert(self, file_name, location):
        root = self.root
        if len(root.keys) == (2 * self.t - 1):
            new_node = BTreeNode(self.t, False)
            new_node.children.append(self.root)
            self.split(new_node, 0)
            self.root = new_node
        self.insert_non_full(self.root, file_name, location)

    def insert_non_full(self, node, file_name, location):
        i = len(node.keys) - 1
        if node.leaf:
            while i >= 0 and file_name < node.keys[i]:
                i -= 1
            node.keys.insert(i + 1, file_name)
            node.children.insert(i + 1, location)
        else:
            while i >= 0 and file_name < node.keys[i]:
                i -= 1
            i += 1
            if len(node.children[i].keys) == (2 * self.t - 1):
                self.split(node, i)
                if file_name > node.keys[i]:
                    i += 1
            self.insert_non_full(node.children[i], file_name, location)

    def split(self, parent, index):
        node = parent.children[index]
        new_node = BTreeNode(self.t, node.leaf)
        parent.keys.insert(index, node.keys[self.t - 1])
        parent.children.insert(index + 1, new_node)

        new_node.keys = node.keys[self.t:]
        node.keys = node.keys[:self.t - 1]

        if not node.leaf:
            new_node.children = node.children[self.t:]
            node.children = node.children[:self.t]
