#include <iostream>
#include <vector>
#include <list>
#include <string>

class UserHashTable {
private:
    std::vector<std::list<std::pair<std::string, std::string>>> table;
    int size;

    int hashFunction(const std::string& username) {
        std::hash<std::string> hashFn;
        return hashFn(username) % size;
    }

public:
    UserHashTable(int size = 100) : size(size) {
        table.resize(size);
    }

    void addUser(const std::string& username, const std::string& profileData) {
        int index = hashFunction(username);
        for (auto& entry : table[index]) {
            if (entry.first == username) {
                entry.second = profileData;
                return;
            }
        }
        table[index].emplace_back(username, profileData);
    }

    std::string getUser(const std::string& username) {
        int index = hashFunction(username);
        for (const auto& entry : table[index]) {
            if (entry.first == username) {
                return entry.second;
            }
        }
        return "User not found";
    }
};
