import numpy as  np
import pandas as pd
np.random.seed(42)
dict1 = {}
dataset = []
def check_all_true(status_list):
    status = False
    for item in status_list:
        if item == False:
            status = True
    return status
        


for i in range(20):
    x = np.random.uniform(1,5)
    y = np.random.uniform(1,5)
    s1 = []
    s1.append(x)
    s1.append(y)
    dataset.append(s1)
    dict1["p"+str(i)] = {"point":s1,"status":False} 
    
# print(dict1)
list_of_points = [p for p in dict1]
status_list = [dict1[p]["status"] for p in dict1]
print(status_list)

def eulcidean_distance(x1,y1,x2,y2):
    return ((x2-x1)**2 + (y2-y1)**2)**0.5
    

distance_table = {}
Er = 1
minpts = 2
for item1 in list_of_points:
    distance_table[item1] = []
    for item2 in list_of_points:
        # print(item1,item2)
        x1 = dict1[item1]["point"][0]
        y1 = dict1[item1]["point"][1]
        x2 = dict1[item2]["point"][0]
        y2 = dict1[item2]["point"][1]
        dist = round(eulcidean_distance(x1=x1,y1=y1,x2=x2,y2=y2),2)
        distance_table[item1].append(dist)
distance_table["points"] = list_of_points



Eneibothood_points = {}

for i,item1 in enumerate(list_of_points):
    list1 = distance_table[item1]
    item_lsit = []
    for j,dist in enumerate(list1):
        if dist < Er:
            print(i)
            item_lsit.append(distance_table["points"][j])
            
    Eneibothood_points[item1] = item_lsit

# print(Eneibothood_points)    
            
df = pd.DataFrame().from_dict(distance_table)
# print(df)

cluster1 =[]
cluster_all = []
while(check_all_true(status_list)):
    c1 = np.random.choice(list_of_points)
    # print(c1)
    if dict1[c1]["status"]==False:
        dict1[c1]["status"] = True
        if len(Eneibothood_points[c1])+1 >=minpts:
            cluster = []
            cluster_all.append(c1)
            cluster.append(c1)
            N = Eneibothood_points[c1]
            N.remove(c1)
            for p1 in N:
                # print("p1",p1)
                if dict1[p1]["status"]==False:
                    dict1[p1]["status"] = True
                    if len(Eneibothood_points[p1]) >=minpts:
                        N1 = Eneibothood_points[p1]
                        N1.remove(p1)
                        N.extend(N1)
                        
                if p1 not in cluster_all:
                    cluster_all.append(p1)
                    cluster.append(p1)
            cluster1.append(cluster)
    status_list = [dict1[p]["status"] for p in dict1]
    
print(cluster1)              
            
            
       
