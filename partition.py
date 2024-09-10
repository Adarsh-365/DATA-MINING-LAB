import numpy as np


def candidate_generate(Fk,k):
    candidate = []
    for i in range(len(Fk)-1):
        for j in range(1,len(Fk)):
            can =np.union1d(Fk[i],Fk[j])
            if not any(np.array_equal(can,arr)for arr in candidate):
                if len(can)==k+1:
                    candidate.append(can)
    return candidate
            


with open("data.txt","r") as f:
    data = f.readlines()

Dict1 ={}
for trans in data:
    trs = trans.strip().split(" ")
    Dict1[trs[0]]=[np.array(i)for i in trs][1:]

partision_dict = [key for key in Dict1]
min_sup = 4

local_min_sup = 1
a=0
b=2
Total_transaction=len(partision_dict)
count = 0
k=1
m=2

itemset_count = {}
Local_f_itemset = []

while(count<=Total_transaction):
    for key in partision_dict[a:b]:
        trans = Dict1[key]
        if k==1:
            for item in trans:
                if str(item) not in itemset_count:
                    itemset_count[str(item)]=1
                else:
                    itemset_count[str(item)]+=1
                if itemset_count[str(item)]>=local_min_sup:
                    if not  any(np.array_equal(item,arr)for arr in Local_f_itemset):
                        
                         Local_f_itemset.append(item)
            CK = trans
            p=k
            part_Can = []
            while(len(CK)!=0):
                CK =candidate_generate(CK,p)
                p+=1
                if len(CK):
                    part_Can+=CK
                # print(CK)
            # print("===================")
            # print(part_Can)
            for item in part_Can:
                if  np.all(np.isin(item,trans)):
                   
                    if str(item) not in itemset_count:
                        itemset_count[str(item)]=1
                    else:
                        itemset_count[str(item)]+=1
                    if itemset_count[str(item)]>=local_min_sup:
                        if not  any(np.array_equal(item,arr)for arr in Local_f_itemset):
                        
                         Local_f_itemset.append(item)
                    
        
    
                
                
                    
    count+=2
    a=b
    b=b+m

# print(DC)   
frequen_itemset= []     
for key in itemset_count:
       if itemset_count[key]>=min_sup:
           frequen_itemset.append(key)
           
print(frequen_itemset)
print(itemset_count)   
        
