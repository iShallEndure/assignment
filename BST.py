class Node:
    def __init__(self, isbn, book_data):
        self.isbn = isbn
        self.book_data = book_data
        self.left = None
        self.right = None

class BST:
    def __init__(self):
        self.root = None

    def insert(self, isbn, book_data):
        if self.root is None:
            self.root = Node(isbn, book_data)
        else:
            self._insert(self.root, isbn, book_data)

    def _insert(self, current_node, isbn, book_data):
        if isbn < current_node.isbn:
            if current_node.left is None:
                current_node.left = Node(isbn, book_data)
            else:
                self._insert(current_node.left, isbn, book_data)
        elif isbn > current_node.isbn:
            if current_node.right is None:
                current_node.right = Node(isbn, book_data)
            else:
                self._insert(current_node.right, isbn, book_data)
        else:
            current_node.book_data = book_data

    def search(self, isbn):
        return self._search(self.root, isbn)

    def _search(self, current_node, isbn):
        if current_node is None:
            return None
        elif isbn == current_node.isbn:
            return current_node.book_data
        elif isbn < current_node.isbn:
            return self._search(current_node.left, isbn)
        else:
            return self._search(current_node.right, isbn)

    def delete(self, isbn):
        self.root = self._delete(self.root, isbn)

    def _delete(self, current_node, isbn):
        if current_node is None:
            return current_node
        if isbn < current_node.isbn:
            current_node.left = self._delete(current_node.left, isbn)
        elif isbn > current_node.isbn:
            current_node.right = self._delete(current_node.right, isbn)
        else:
            if current_node.left is None:
                return current_node.right
            elif current_node.right is None:
                return current_node.left
            temp = self._min_value_node(current_node.right)
            current_node.isbn = temp.isbn
            current_node.book_data = temp.book_data
            current_node.right = self._delete(current_node.right, temp.isbn)
        return current_node

    def _min_value_node(self, node):
        current = node
        while current.left is not None:
            current = current.left
        return current