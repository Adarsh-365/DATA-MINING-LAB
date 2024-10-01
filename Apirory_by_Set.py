def UNION(A,B):
    union = set()
    for i in A:
        union.add(i)
    for j in B:
        union.add(j)
    return union

def is_subset(A,B):
    
    return A.issubset(B)


def candidate_gen(Fk,k):
    candidate = []
    for i in range(len(Fk)-1):
        for j in range(i+1,len(Fk)):
            C = UNION(Fk[i],Fk[j])
            if len(C)==k+1:
                if C not in candidate:
                  candidate.append(C)
    return candidate
                
            
            


with open("Td1.txt") as f:
    data = f.readlines()
    
Dict1 = {}
for item in data:
    item = item.strip().split(" ")
    Dict1[item[0]]= item[1:]
    

Result = []
itemset_count = {}
k =1
Ck = []
min_sup =2
while(len(Ck)!=0 or k==1):
    Frequent =[]
    if k==1:
        for key in Dict1:
            trans = Dict1[key]
            for item in trans:
                if item  not in itemset_count:
                    
                    itemset_count[item]=1
                else:
                    itemset_count[item]+=1
                if itemset_count[item]>=min_sup:
                    if set(item) not in Frequent:
                        Frequent.append(set(item))
    
    else:
        print("-----------")
        for key in Dict1:
            trans = Dict1[key]
            for item in Ck:
                
                if is_subset(item,trans):
                    print(item,trans)
                    if frozenset(item) not in itemset_count:
                          itemset_count[frozenset(item)] = 1
                    else:
                         itemset_count[frozenset(item)] += 1
                    if  itemset_count[frozenset(item)] >=min_sup:
                        if item not in Frequent:
                              Frequent.append(item)
            
    Ck = candidate_gen(Frequent,k)
    k=k+1
    
    Result = Result + Frequent
   
print(Result)      
print(itemset_count)    
                
                    
