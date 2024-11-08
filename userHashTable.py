class UserHashTable:
    def _init_(self, size=100):
        self.size = size
        self.table = [[] for _ in range(size)]

    def _hash(self, username):
        return hash(username) % self.size

    def add_user(self, username, profile_data):
        index = self._hash(username)
        for entry in self.table[index]:
            if entry[0] == username:
                entry[1] = profile_data
                return
        self.table[index].append([username, profile_data])

    def get_user(self, username):
        index = self._hash(username)
        for entry in self.table[index]:
            if entry[0] == username:
                return entry[1]
        return None