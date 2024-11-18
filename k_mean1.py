import numpy as np
import pandas as pd

# Simulate data
with open("db.txt", "w") as f:
    for i in range(20):
        f.write(f"A{i+1} {np.random.randint(1, 10)},{np.random.randint(1, 10)}\n")
         

with open("db.txt","r")as f:
    data= f.readlines()

dataset = {}
# print(data)
for item in data:
    item = item.strip().split(",")
    dataset[item[0][:-2]]= [int(item[0][-2:]),int(item[1])]
    
print(dataset)

def k_mean1(k):
    K_means_table = {}
    K_means_table["Points"] = []
    K_means_table["X"] = []
    K_means_table["Y"] = []
    for i in range(k):
        K_means_table["C"+str(i+1)] = []
    K_means_table["PrevCluster"] = []
    K_means_table["NewCluster"] = []
    return K_means_table
    
k =10
K_means_table  = k_mean1(k)


for key in dataset:
    K_means_table["Points"].append(key)
    K_means_table["X"].append(dataset[key][0])
    K_means_table["Y"].append(dataset[key][1])
print(K_means_table)



Centriod = {}
list_of_points = [key for key in dataset]
# for i in range(k):
#    n = np.random.randint(0,20)
#    print(dataset[list_of_points[n]])
#    Centriod[list_of_points[n]]
cen =  np.random.choice(list_of_points,k,replace=0)
print(cen)
for p in cen:
    Centriod[str(p)] = dataset[p]
print(Centriod)

def eulcidean_dist(x1,x2,y1,y2):
    return ((x2-x1)**2 + (y2-y1)**2)**0.5

def K_means_clustring(K_means_table,Centriod,itern):
    lsit_of_cen = []
    for i in range(k):
        lsit_of_cen.append("C"+str(i+1))
    
    # print(lsit_of_cen)
    print(f"----------------{itern}------------------")
    print(Centriod)
    for i in range(len(K_means_table["Points"])):
        x1 = K_means_table["X"][i]
        y1 = K_means_table["Y"][i]
        cen_id = 0
        for cen in Centriod:
            x2 = Centriod[cen][0]
            y2 = Centriod[cen][1]
            K_means_table[lsit_of_cen[cen_id]].append(round(eulcidean_dist(x1=x1,x2=x2,y1=y1,y2=y2),2))
            cen_id+=1
    
        
    for i in range(len(K_means_table["Points"])):
        
        cen_id = 0
        dist_ = []
        for cen in lsit_of_cen:
            dist_.append(K_means_table[cen][i])
        minimum = min(dist_)
        
        K_means_table["NewCluster"].append(lsit_of_cen[dist_.index(minimum)])
        if itern==1:
             K_means_table["PrevCluster"] = -1
   
    
    df = pd.DataFrame().from_dict(K_means_table)
    print(df)
    
    if K_means_table["PrevCluster"]==K_means_table["NewCluster"]:
        return
    new_cluster = {}
    for cen in lsit_of_cen:
        new_cluster[cen] = {"x":[],"y":[]}
    # print(new_cluster)
    for i in range(len(K_means_table["Points"])):
        #  print(K_means_table["NewCluster"][i])
         new_cluster[K_means_table["NewCluster"][i]]["x"].append(K_means_table["X"][i])
         new_cluster[K_means_table["NewCluster"][i]]["y"].append(K_means_table["Y"][i])
    #create new cluster
    # print(new_cluster)
    # print(Centriod)
    new_cluster_ = {}
    for cen in new_cluster:
        # print(cen)
        if len(new_cluster[cen]["x"])>2:
            new_cluster_[cen] = [float(round(np.sum(new_cluster[cen]["x"])/len((new_cluster[cen]["x"])),2)),
                                float(round(np.sum(new_cluster[cen]["y"])/len((new_cluster[cen]["y"])),2))
                                ]
        else:
             new_cluster_[cen] = [new_cluster[cen]["x"][0],new_cluster[cen]["y"][0] ]
   
    for i in range(k):
        K_means_table["C"+str(i+1)] = []
    K_means_table["PrevCluster"] = K_means_table["NewCluster"]
    K_means_table["NewCluster"] = []
    K_means_clustring(K_means_table,new_cluster_,itern=itern+1)










K_means_clustring(K_means_table,Centriod,itern = 1)
