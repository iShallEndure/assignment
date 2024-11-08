class PatientQueue:
    def _init_(self):
        self.queue = []
    
    def enqueue(self, patient):
        self.queue.append(patient)
    
    def dequeue(self):
        if not self.queue:
            return None
        return self.queue.pop(0)

class EmergencyStack:
    def _init_(self):
        self.stack = []
    
    def push(self, emergency_patient):
        self.stack.append(emergency_patient)
    
    def pop(self):
        if not self.stack:
            return None
        return self.stack.pop()