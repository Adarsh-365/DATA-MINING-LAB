import numpy as np



with open("data.txt", "r") as f:
    data =   f.readlines()

Dict1 = {}
for tras in data:
    transc = tras.strip().split(" ")
    Dict1[str(transc[0])]=np.array(transc[1:])



min_sup = 2
m = 2
total_trans =len(Dict1)


DC = []
SC = []
DS = []
SS = []
count = 0
list_of_key = [key for key in Dict1]
a = 0
b = 2
k = 1
itemset_count = {}

frequent_itemset = []

while(len(DC)!=0 or k==1):
    
    while(count<=total_trans):
        
        if k==1:
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
        
        else:
           
            for item in DC:
                for key in list_of_key[a:b]:
                    trans = Dict1[key]
                    sbc = np.all(np.isin(item,trans))
                    
                    if sbc:
                    # print(itemset_count)
                        if str(item) not in itemset_count:
                            itemset_count[str(item)]=1
                        else:
                            itemset_count[str(item)]+=1
                # for item in DC:
                    
                        
                        if itemset_count[str(item)]>=min_sup:
                            
                                if not any(np.array_equal(item,arr) for arr in DS):
                                
                                    DS.append(item)
                            
                    
                
                    
                    
                
                    
                
                        
                 
        count+=m
        a=b
        
        if (count+m)>total_trans:
            b = b+total_trans-count
        else:
            b = b+m
        print(b)
    
    k = k+1   
    count = 0
    
    a = 0
     
    b = 2
    
    SC =  []
    
    SS = []
    
    for item in DC:
        
        try:
             if item not in DS:
            
                SC.append(item)
        except:
            is_y_in_x = any(np.array_equal(item, arr) for arr in DC)
            if not is_y_in_x:
                print("a====>",item)
                SC.append(item)
           

        #  DC.remove(item)
    for item in DS:
        SS.append(item)
    if len(SS):
        frequent_itemset.append(SS)
    DC = []
    DS = []
    itemset_count = {}
    for i in range(len(SS)-1):
        for j in range(i+1,len(SS)):
            set1 = np.union1d(SS[i],SS[j])
            if not any(np.array_equal(set1,arr)for arr in DC):
                 DC.append(set1)

                    
            


print("frequent_itemset = ",frequent_itemset)




