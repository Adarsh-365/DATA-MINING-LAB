import numpy as np
import pandas as pd

def kmeans(X, k, max_iters=100):
    # Randomly initialize centroids
    centroids = X.sample(n=k).values
    
    for i in range(max_iters):
        # Compute distances and assign clusters
        distances = np.linalg.norm(X.values[:, np.newaxis] - centroids, axis=2)
        labels = np.argmin(distances, axis=1)
        
        # Update centroids
        new_centroids = np.array([X.values[labels == j].mean(axis=0) for j in range(k)])
        
        # Check for convergence (if centroids do not change)
        if np.all(centroids == new_centroids):
            break
        centroids = new_centroids

    return centroids, labels


with open("k_data.txt","r")as f:
    data = f.readlines()
    
# print(data)

data1  = {'x1':[],'y1':[]}
Dict1 = {}
dict2 = {"Point":[],"X":[],"Y":[],"C1_D":[],"C2_D":[],"C3_D":[],"Prev_C":[],"New_clu":[]}
for item in data:
    item = item.strip().split(",")
    # print(item)
    Dict1[item[0][:2]] = [int(item[0][-1]),int(item[1])]
    dict2["Point"].append(item[0][:2])
    dict2["X"].append(int(item[0][-1]))
    data1["x1"].append(int(item[0][-1]))
    data1["y1"].append(int(item[1]))
    dict2["Y"].append(int(item[1]))
# Example usage with a simple dataset
# data = {'x1': [1, 2, 3, 8, 9, 10], 'x2': [1, 1, 2, 8, 8, 9]}

print(data1)
df = pd.DataFrame(data1)

centroids, labels = kmeans(df, k=3)
print("Centroids:\n", centroids)
print("Labels:", labels)
