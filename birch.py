import numpy as np
import pandas as pd

class BirchCluster:
    def __init__(self, threshold, branching_factor):
        self.threshold = threshold  # Distance threshold for merging
        self.branching_factor = branching_factor  # Maximum number of child nodes
        self.cf_tree = []  # List of cluster features (each is a ClusterFeature)
    
    def add_point(self, point):
        """Adds a point to the CF tree"""
        # Convert point to numpy array if not already
        point = np.array(point)
        for cluster in self.cf_tree:
            if np.linalg.norm(cluster['LS'] - point) <= self.threshold:
                # Update existing cluster feature if point is within threshold
                cluster['N'] += 1
                cluster['LS'] += point
                cluster['SS'] += point ** 2
                return
        
        # If no cluster found within the threshold, create a new one
        self.cf_tree.append({
            'N': 1,
            'LS': point,
            'SS': point ** 2
        })
        
        # If CF tree exceeds branching factor, perform clustering on leaf nodes
        if len(self.cf_tree) > self.branching_factor:
            self._cluster_leaf_nodes()
    
    def _cluster_leaf_nodes(self):
        """Clusters the leaf nodes using k-means or similar (this is a simple placeholder for clustering)"""
        # In a full implementation, you would apply k-means on the current CFs
        # Here, we just print the CFs for simplicity
        print("Clustering CFs: ", self.cf_tree)
        # Perform clustering on the CFs (e.g., k-means) and reset the tree after pruning
        # For simplicity, let's just leave the clustering as is in this example.
    
    def get_clusters(self):
        """Returns the final clusters (simple version without re-clustering)"""
        return self.cf_tree


# Example usage:
data = {'x1': [1, 2, 3, 8, 9, 10], 'x2': [1, 1, 2, 8, 8, 9]}
df = pd.DataFrame(data)

birch = BirchCluster(threshold=2.0, branching_factor=3)

for _, row in df.iterrows():
    birch.add_point(row)

clusters = birch.get_clusters()
print("Final clusters:", clusters)
