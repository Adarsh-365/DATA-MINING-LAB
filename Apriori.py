import numpy as np



def Candidate_generate(Fk,k):
    candidate_set = []
    for i in range(len(Fk)-1):
        for j in range(i+1,len(Fk)):
            if k==1:
                set1 = np.union1d(np.array(Fk[i]),np.array(Fk[j]))
                candidate_set.append(set1)
    
    return  candidate_set


with open("td.txt", "r") as f:
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
            

itemset_count = dict(sorted(itemset_count.items(),key=lambda item:item[1],reverse=1))
for key in itemset_count:
    if itemset_count[key]>2:
        freq_itemset.append(np.array([key]))



C1 = itemset
Result = []

k = 1 

while(len(C1) !=0):
    itemset_count = {}
    Fk = []
    if k==1:
       
        Fk = freq_itemset
    else:
        for key in Dict1:
            for item in C1:
                subset =np.all(np.isin(np.array(item),np.array(Dict1[key])))
                if subset:
                    if str(item) not in itemset_count:
                        itemset_count[str(item)]=1
                    else:
                        itemset_count[str(item)]+=1
        for item in itemset_count:
            if itemset_count[str(item)]>=min_sup:
                Fk.append(np.array(item))
    

    C1 = Candidate_generate(Fk,k)
    Result.append(Fk)
    k=k+1

print(Result)
















