# 3. Find the support/count of items 
import numpy as np

with open("Apriori.txt", "r") as f:
    data =   f.readlines()

Dict1 = {}
for tras in data:
    transc = tras.strip().split(" ")
    Dict1[str(transc[0])]=np.array(transc[1:])


itemset = []
itemset_count = {}
freq_itemset = []
min_sup = 2
for key in Dict1:
    trans = Dict1[key]
    for item in trans:
        if item not in itemset:
            itemset.append(item)
            itemset_count[str(item)]=1
        else:
            itemset_count[str(item)]+=1
            
data =  []           
for key in itemset_count:
    data.append([key, itemset_count[key]])

with open("td_lab3.txt","w") as f:
    for item in data:
        f.write(str(item[0])+" "+str(item[1])+"\n")