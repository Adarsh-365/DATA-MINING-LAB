
#2. Read Transactions from file using only file operations 

with open("Td1.txt","r")as f:
    data = f.readlines()
    
for item in data:
    print(item,end="")