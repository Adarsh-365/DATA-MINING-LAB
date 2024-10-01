def uninon_set(A,B):
    un = set()
    for i in A:
        un.add(i)
    for i in B:
        un.add(i)
    return un



def candidate_gen(Fk,k):
    candidate = []
    for i in range(len(Fk)-1):
        for j in range(i+1,len(Fk)):
            c = uninon_set(Fk[i],Fk[j])
            if len(c)==k+1:
                if c not in candidate:
                    candidate.append(c)
    
    return candidate


with open("Td1.txt") as f:
    data = f.readlines()
    
Dict1 = {}
for item in data:
    item = item.strip().split(" ")
    Dict1[item[0]]= item[1:]

# for key in Dict1:
list_of_key = [key for key in Dict1]
array_of_array = []
min_local_sup = 1
Frequent = []
itemset_count = {}
count = 0
total_trans = len(list_of_key)
a = -2
b = 0

while(count<=total_trans):
    a = a+2
    b = b+2
    count += 2
    for key in list_of_key[a:b]:
        trans = Dict1[key]
        array_of_array.append(trans)
    possible_subset = []
    for single_trans in array_of_array:
        Ck = single_trans.copy()
        k = 1
        for item in Ck:
            if set(item) not in possible_subset:
            
               possible_subset.append(set(item))
        while(len(Ck)!=0):
            Ck = candidate_gen(Ck,k)
            k+=1
            if len(Ck):
                for item in Ck:
                    if item not in possible_subset: 
                                possible_subset.append(item)
                


    for single_trans in array_of_array:
        for sub in possible_subset:
            trans = set(single_trans)
            if sub.issubset(trans):
                # print(sub ," is sub set of",trans)
                if frozenset(sub) not in itemset_count:
                    itemset_count[frozenset(sub)] = 1
                else:
                    itemset_count[frozenset(sub)] += 1
                if itemset_count[frozenset(sub)]>=min_local_sup:
                    Frequent.append(sub)
                    
                    
        
    print(itemset_count)
    print(Frequent)
