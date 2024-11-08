class Node:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.degree = 0
        self.parent = None
        self.child = None
        self.marked = False
        self.next = None
        self.prev = None

class FibHeap:
    def __init__(self):
        self.min_node = None
        self.num_nodes = 0

    def insert(self, key, value):
        node = Node(key, value)
        if not self.min_node:
            self.min_node = node
        else:
            self._link(self.min_node, node)
            if node.key < self.min_node.key:
                self.min_node = node
        self.num_nodes += 1

    def decrease_key(self, node, new_key):
        if new_key > node.key:
            raise ValueError("New key is greater than current key")
        node.key = new_key
        parent = node.parent
        if parent and node.key < parent.key:
            self._cut(node, parent)
            self._cascading_cut(parent)
        if node.key < self.min_node.key:
            self.min_node = node

    def extract_min(self):
        min_node = self.min_node
        if min_node:
            if min_node.child:
                child = min_node.child
                while True:
                    next_child = child.next
                    self._link(self.min_node, child)
                    child.parent = None
                    if next_child == min_node.child:
                        break
                    child = next_child
            self._remove(min_node)
            if min_node == min_node.next:
                self.min_node = None
            else:
                self.min_node = min_node.next
                self._consolidate()
            self.num_nodes -= 1
        return min_node

    def _link(self, min_node, node):
        if not min_node.next:
            min_node.next = node
            node.prev = min_node
        else:
            node.next = min_node.next
            min_node.next.prev = node
            min_node.next = node
            node.prev = min_node

    def _cut(self, node, parent):
        if node.next == node:
            parent.child = None
        else:
            parent.child = node.next
        node.prev.next = node.next
        node.next.prev = node.prev
        node.parent = None
        node.marked = False
        self._link(self.min_node, node)

    def _cascading_cut(self, node):
        parent = node.parent
        if parent:
            if not node.marked:
                node.marked = True
            else:
                self._cut(node, parent)
                self._cascading_cut(parent)

    def _remove(self, node):
        if node == node.next:
            node.prev = None
            node.next = None
        else:
            node.prev.next = node.next
            node.next.prev = node.prev

    def _consolidate(self):
        max_degree = int(self.num_nodes ** 0.5) + 1
        buckets = [None] * (max_degree + 1)
        node = self.min_node
        nodes = []
        while True:
            nodes.append(node)
            node = node.next
            if node == self.min_node:
                break
        for node in nodes:
            degree = node.degree
            while buckets[degree]:
                other = buckets[degree]
                if other.key < node.key:
                    node, other = other, node
                self._link(node, other)
                buckets[degree] = None
                degree += 1
            buckets[degree] = node
        self.min_node = None
        for bucket in buckets:
            if bucket:
                if not self.min_node:
                    self.min_node = bucket
                elif bucket.key < self.min_node.key:
                    self.min_node = bucket