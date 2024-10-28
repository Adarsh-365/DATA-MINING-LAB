import numpy as np
import pandas as pd


with open("data_kmean.txt","r")as f:
    data = f.readlines()
    
# print(data)
Dict1 = {}
dict2 = {"Point":[],"X":[],"Y":[],"C1_D":[],"C2_D":[],"C3_D":[],"Prev_C":[],"New_clu":[]}
for item in data:
    item = item.strip().split(",")
    # print(item)
    Dict1[item[0][:2]] = [int(item[0][-1]),int(item[1])]
    dict2["Point"].append(item[0][:2])
    dict2["X"].append(int(item[0][-1]))
    dict2["Y"].append(int(item[1]))


cluster = {"C1":{"X":"","Y":""},"C2":{"X":"","Y":""},"C3":{"X":"","Y":""}}
# print(dict2)
def Set_cluster(cluster_name):
    cluster__id = ["C1","C2","C3"]
    for i,pair in enumerate(cluster_name):
        # print(a)
        row_number = dict2["Point"].index(pair[0])
        cluster[cluster__id[i]]["X"] =  dict2["X"][row_number]
        cluster[cluster__id[i]]["Y"] =  dict2["Y"][row_number]
        cluster[pair[0]]  = cluster.pop(cluster__id[i])
       
        
def Eucliden_distance(x1,y1,x2,y2):
    
    return ((x2-x1)**2 + (y2-y1)**2)**0.5

def cal_new_centriod(store_cluster,clusterR,dict2):
        for oldc in store_cluster:
            if len(store_cluster[oldc])>1:
                x =0 
                y = 0
                for i in store_cluster[oldc]:
                    x += dict2["X"][i]
                    y += dict2["Y"][i]
                
                x = round(x/len(store_cluster[oldc]),2)
                y = round(y/len(store_cluster[oldc]),2)
                    
                clusterR[oldc] = {'X': x, 'Y': y}
        return clusterR
    

iteration = 0
def k_mean_cluster(cluster_name,clusterR,dict2):
    global iteration
    lengrh = len(dict2["Point"])
    iteration = iteration+1
    print("____________Iteration "+str(iteration)+"________________")
    for pair in cluster_name:
        for i in range(lengrh):
            x1 = dict2["X"][i]
            y1 = dict2["Y"][i]
            x2 = clusterR[pair[0]]["X"]
            y2 = clusterR[pair[0]]["Y"]
            dist = round(Eucliden_distance(x1=x1,y1=y1,x2=x2,y2=y2),2)
            dict2[pair[1]].append(dist)
    for i in range(lengrh):
        if iteration==1:
            dict2["Prev_C"].append(-1)
    store_cluster  = {}
   
    for i in range(lengrh):
        distance = []
        for cluster in cluster_name:
            distance.append(dict2[cluster[1]][i])
        minimun = min(distance)
        new_clutser_id = distance.index(minimun)
        dict2["New_clu"].append(cluster_name[new_clutser_id][0])
        if cluster_name[new_clutser_id][0] not in store_cluster:
             store_cluster[cluster_name[new_clutser_id][0]] = [i]
        else:
             store_cluster[cluster_name[new_clutser_id][0]].append(i)
    # print(dict2)
    cluster2 = pd.DataFrame.from_dict(dict2)
    clusterR_pd = pd.DataFrame.from_dict(clusterR)
    
    print(clusterR_pd) 
    
    print("")
    print("")
    print(cluster2)
    print("")
    print("")
    print("")
    if dict2["Prev_C"]==dict2["New_clu"]:
        return
    # print(store_cluster)
    # print(clusterR)
    clusterR = cal_new_centriod(store_cluster,clusterR,dict2=dict2)
    dict2["C1_D"] = []
    dict2["C2_D"] = []
    dict2["C3_D"] = []
    dict2["Prev_C"]  =  dict2["New_clu"] 
    dict2["New_clu"]  = []
    k_mean_cluster(cluster_name,clusterR,dict2=dict2)
    #update centriod
    
              
    
cluster_name = [["A1","C1_D"],["B1","C2_D"],["C1","C3_D"]]
Set_cluster(cluster_name)
k_mean_cluster(cluster_name,cluster,dict2)
# cluster_naem = ["A1","B1","C1"]



# print(dict2)

