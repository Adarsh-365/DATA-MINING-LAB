class Node:
    def __init__(self,data):
        self.data = data
        self.parent = None
        self.children = {}
        self.count = 1
        
    def add(self,nodes):
        current_node = self
        for node in nodes:
            if node.data in current_node.children:
                current_node.children[node.data].count +=1
            else:
                current_node.children[node.data] = node
                node.parent = current_node
            current_node = current_node.children[node.data]
    
    def find_all(self,target):
        all_nodes  = []
        
        if self.data == target:
            all_nodes.append(self)
        
        for child in self.children.values():
            all_nodes.extend(child.find_all(target)) 
        
        return all_nodes
    
    
    def get_parent_list(self):
        parent_list = []
        current_node = self
        
        while(current_node.parent is not None):
            parent_list.append(current_node.parent.data)
            current_node = current_node.parent
        return parent_list
    
    def display(self,level = 0):
        print("-"*level+str(self.data)+"  count: "+str(self.count))
        for child in self.children.values():
            child.display(level+1)

with open("Td1.txt",'r')as f:
    data = f.readlines()

Dict1 = {}
for item in data:
    item = item.strip().split(" ")
    Dict1[item[0]] = item[1:]
    
itemset_count = {}

for key in Dict1:
    trans = Dict1[key]
    for item in trans:
        if item not in itemset_count:
            itemset_count[item] = 1
        else:
            itemset_count[item] += 1
        

# print(itemset_count)
sorted_dict = dict(sorted(itemset_count.items(),key = lambda item:item[1],reverse=1))
# print(sorted_dict)


root  = Node("NULL")


for key in Dict1:
    trans = Dict1[key]
    Nodes_list = []
    for item in sorted_dict:
        if item  in trans:
            Nodes_list.append(Node(item))
    
    root.add(Nodes_list)
            
root.display()
        
list_of_key = [key for key in sorted_dict]
list_of_key.reverse()
# print(list_of_key)  
for  key in list_of_key:
    find_nodes = root.find_all(key)
    
    for node1 in find_nodes:
        parent = node1.get_parent_list()
        print(key,parent,node1.count)    
        
        
# [{'b'}, {'a'}, {'d'}, {'c'}, {'e'}, {'a', 'b'}, {'c', 'b'},
# {'c', 'a'}, {'d', 'a'}, {'d', 'c'}, {'e', 'c'}, {'c', 'a', 'b'}]
