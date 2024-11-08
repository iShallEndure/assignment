#include <iostream>
#include <queue>
#include <stack>

class PatientQueue {
public:
    void enqueue(int patient) {
        queue.push(patient);
    }
    
    int dequeue() {
        if (queue.empty()) {
            return -1; // Assuming -1 indicates an empty queue
        }
        int patient = queue.front();
        queue.pop();
        return patient;
    }
private:
    std::queue<int> queue;
};

class EmergencyStack {
public:
    void push(int emergency_patient) {
        stack.push(emergency_patient);
    }
    
    int pop() {
        if (stack.empty()) {
            return -1; // Assuming -1 indicates an empty stack
        }
        int emergency_patient = stack.top();
        stack.pop();
        return emergency_patient;
    }
private:
    std::stack<int> stack;
};