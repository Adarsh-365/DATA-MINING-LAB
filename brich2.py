import numpy as np
import pandas as pd

class BirchCluster:
    def __init__(self, threshold, branching_factor):
        self.threshold = threshold  # Distance threshold for merging
        self.branching_factor = branching_factor  # Maximum number of child nodes
        self.cf_tree = []  # List of cluster features (each is a ClusterFeature)
        self.tree_structure = []  # To store the tree structure for printing
    
    def add_point(self, point):
        """Adds a point to the CF tree"""
        point = np.array(point)
        for idx, cluster in enumerate(self.cf_tree):
            if np.linalg.norm(cluster['LS'] - point) <= self.threshold:
                # Update existing cluster feature if point is within threshold
                cluster['N'] += 1
                cluster['LS'] += point
                cluster['SS'] += point ** 2
                return
        
        # If no cluster found within the threshold, create a new one
        new_idx = len(self.cf_tree)
        self.cf_tree.append({
            'N': 1,
            'LS': point,
            'SS': point ** 2
        })
        
        # Add to tree structure (parent-child relationship)
        if len(self.cf_tree) > 1:
            parent_idx = np.random.choice(len(self.cf_tree) - 1)
            self.tree_structure.append((parent_idx, new_idx))
        
        # If CF tree exceeds branching factor, perform clustering on leaf nodes
        if len(self.cf_tree) > self.branching_factor:
            self._cluster_leaf_nodes()
    
    def _cluster_leaf_nodes(self):
        """Clusters the leaf nodes using a basic placeholder method"""
        print("Clustering CFs: ", self.cf_tree)
    
    def get_clusters(self):
        """Returns the final clusters"""
        return self.cf_tree
    
    def print_tree(self, node_idx=0, level=0):
        """Prints the CF Tree in the console"""
        if node_idx >= len(self.cf_tree):
            return
        
        # Print the current node (Cluster Feature)
        print("  " * level + f"Node {node_idx}: N={self.cf_tree[node_idx]['N']}, LS={self.cf_tree[node_idx]['LS']}, SS={self.cf_tree[node_idx]['SS']}")
        
        # Recursively print children nodes
        children = [child for parent, child in self.tree_structure if parent == node_idx]
        for child in children:
            self.print_tree(child, level + 1)


# Example usage:
data = {'x1': [1, 2, 3, 8, 9, 10], 'x2': [1, 1, 2, 8, 8, 9]}
df = pd.DataFrame(data)

birch = BirchCluster(threshold=2.0, branching_factor=3)

for _, row in df.iterrows():
    birch.add_point(row)

# Print the tree structure
print("Final BIRCH CF Tree Structure:")
birch.print_tree()
