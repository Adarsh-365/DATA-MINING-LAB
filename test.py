import numpy as np



def Candidate_generate(Fk,k):
    candidate_set = []
    for i in range(len(Fk)-1):
        for j in range(i+1,len(Fk)):
                k = len(Fk)
                set1 = np.union1d(np.array(Fk[i]),np.array(Fk[j]))
               
                if len(set1)==k+1:
                    
                    candidate_set.append(set1)
                
    
    return  candidate_set


with open("data.txt", "r") as f:
    data =   f.readlines()

Dict1 = {}
for tras in data:
    transc = tras.strip().split(" ")
    Dict1[str(transc[0])]=np.array(transc[1:])


# itemset = []
# itemset_count = {}
# freq_itemset = []
min_sup =4 
m = 2
total_trans =len(Dict1)


DC = []
SC =  []
DS = []
SS = []
count = 0
list_of_key = [key for key in Dict1]
a = 0
b = 2

itemset_count = {}

while(count!=total_trans):
    Dict2 = {}
    for key in list_of_key[a:b]:
        trans = Dict1[key]
        for item in trans:
            if item not in DC:
                DC.append(item)
                itemset_count[str(item)]=1
            else:
                itemset_count[str(item)]+=1
            
            if itemset_count[str(item)]>=min_sup:
                if item not in DS:
                    DS.append(item)
                    #DC.remove(item)
            
           
                
            
    count+=m
    a=b
    b=b+m

    if count==total_trans:
        for item in DC:
            if item not in DS:
                SC.append(item)
              #  DC.remove(item)
        for item in DS:
            SS.append(item)
        DC = []
        for i in range(len(SS)-1):
            for j in range(i+1,SS):
                set1 = np.union1d(SS[i],SS[j])
                DC.append()
                
            
print("==========")        
print("SC = ",SC)         


print("DC = ",DC)
print("DS = ",DS)
print("SS = ",SS)  
print(itemset_count)







# for key in Dict1:
#     trans = Dict1[key]
#     for item in trans:
#         if item not in itemset:
#             itemset.append(item)
#             itemset_count[str(item)]=1
#         else:
#             itemset_count[str(item)]+=1
            

# itemset_count = dict(sorted(itemset_count.items(),key=lambda item:item[1],reverse=1))

# print(itemset_count)




# for key in itemset_count:
#     if itemset_count[key] >= min_sup:
#         SS.append(np.array([key]))
# print(SS)


# for key in itemset_count:
#     if itemset_count[key]>2:
#         freq_itemset.append(np.array([key]))



# C1 = itemset
# Result = []

# k = 1 

# while(len(C1) !=0):
#     itemset_count = {}
#     itemset = []
#     Fk = []
#     if k==1:
       
#         Fk = freq_itemset
#     else:
#         for key in Dict1:
#             for item in C1:
#                 subset =np.all(np.isin(np.array(item),np.array(Dict1[key])))
#                 if subset:
#                     if str(item) not in itemset_count:
#                         itemset_count[str(item)]=1
#                         itemset.append(np.array(item))
#                     else:
#                         itemset_count[str(item)]+=1
#         for i,item in enumerate(itemset_count):
#             if itemset_count[str(item)]>=min_sup:
#                 Fk.append(np.array(itemset[i]))
    
   
#     C1 = Candidate_generate(Fk,k)
   
#     if len(Fk):
#         Result.append(Fk)
#     k=k+1

# print(Result)