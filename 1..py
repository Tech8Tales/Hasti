class hashtable:
    def __init__(self):
        self.m = int(input("Enter size of hash table: "))
        self.hashTable = [None] * self.m
        self.elecount = 0
        print(self.hashTable)
    
    def hashFunction(self, key):
        return key % self.m
    
    def isfull(self):
        return self.elecount == self.m
    
    def linearprobr(self, key, data):
        index = self.hashFunction(key)
        compare = 0
        while self.hashTable[index] is not None:
            index = (index + 1) % self.m
            compare += 1
        self.hashTable[index] = [key, data]
        self.elecount += 1
        print("Data inserted at", index)
        print(self.hashTable)
        print("Number of comparisons:", compare)
    
    def getlinear(self, key):
        index = self.hashFunction(key)
        compare = 0
        while self.hashTable[index] is not None:
            compare += 1
            if self.hashTable[index][0] == key:
                print("Comparisons made:", compare)
                return index
            index = (index + 1) % self.m
        return None
    
    def quadraticprobr(self, key, data):
        index = self.hashFunction(key)
        compare = 0
        i = 0
        while self.hashTable[index] is not None:
            compare += 1
            i += 1
            index = (index + i*i) % self.m
        self.hashTable[index] = [key, data]
        self.elecount += 1
        print("Data inserted at", index)
        print(self.hashTable)
        print("Number of comparisons:", compare)
    
    def getQuadratic(self, key):
        index = self.hashFunction(key)
        i = 0
        compare = 0
        while self.hashTable[index] is not None:
            compare += 1
            if self.hashTable[index][0] == key:
                print("Comparisons made:", compare)
                return index
            i += 1
            index = (index + i*i) % self.m
        return None
    
    def insertvialinear(self, key, data):
        if self.isfull():
            print("Table is full")
            return False
        index = self.hashFunction(key)
        if self.hashTable[index] is None:
            self.hashTable[index] = [key, data]
            self.elecount += 1
            print("Data inserted at", index)
            print(self.hashTable)
        else:
            print("Collision occurred, applying Linear probing")
            self.linearprobr(key, data)
    
    def insertviaQuadratic(self, key, data):
        if self.isfull():
            print("Table is full")
            return False
        index = self.hashFunction(key)
        if self.hashTable[index] is None:
            self.hashTable[index] = [key, data]
            self.elecount += 1
            print("Data inserted at", index)
            print(self.hashTable)
        else:
            print("Collision occurred, applying Quadratic probing")
            self.quadraticprobr(key, data)

def menu():
    obj = hashtable()
    ch = 0
    while ch != 3:
        print("\n************************")
        print("1. Linear Probe       *")
        print("2. Quadratic Probe    *")
        print("3. Exit               *")
        print("************************")
        
        ch = int(input("Enter Choice: "))
        
        if ch == 1:
            ch2 = 0
            while ch2 != 3:
                print("\n** 1. Insert **")
                print("** 2. Search **")
                print("** 3. Exit   **")
                ch2 = int(input("Enter your choice: "))
                if ch2 == 1:
                    a = int(input("Enter phone number: "))
                    b = input("Enter name: ")
                    obj.insertvialinear(a, b)
                elif ch2 == 2:
                    k = int(input("Enter key to be searched: "))
                    f = obj.getlinear(k)
                    if f is None:
                        print("Key not found")
                    else:
                        print("Key found at index", f)
        
        elif ch == 2:
            ch2 = 0
            while ch2 != 3:
                print("\n** 1. Insert **")
                print("** 2. Search **")
                print("** 3. Exit   **")
                ch2 = int(input("Enter your choice: "))
                if ch2 == 1:
                    a = int(input("Enter phone number: "))
                    b = input("Enter name: ")
                    obj.insertviaQuadratic(a, b)
                elif ch2 == 2:
                    k = int(input("Enter key to be searched: "))
                    f = obj.getQuadratic(k)
                    if f is None:
                        print("Key not found")
                    else:
                        print("Key found at index", f)

menu()