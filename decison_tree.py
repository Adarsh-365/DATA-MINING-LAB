import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

# Reading the dataset
df = pd.read_csv("data.csv")

# Result data for decision tree
result_data = np.array(df["Class"].to_list())
values, count = np.unique(result_data, return_counts=1)

# Entropy function
def Entropy(pos, neg, total):
    if pos == 0 or neg == 0:
        return 0
    return -(pos / total) * np.log2(pos / total) - (neg / total) * np.log2(neg / total)

# Initial entropy of the dataset (overall)
Entropy_of_table = Entropy(count[1], count[0], count[0] + count[1])

classes = df.columns.to_list()[1:-1]

# Track entropy changes for plotting
entropy_gains = []

# Decision tree function with entropy tracking
def Decision_tree(classes, df, level=0):
    Entropy_count = []
    if len(classes) == 0:
        return
    
    # Loop through the classes (features)
    for class1 in classes:
        set2 = [] 
        entropy_list = []
        item_data = np.array(df[class1].to_list())
        result_data = np.array(df["Class"].to_list())
        
        # Collect feature values and corresponding class results
        for i in range(len(item_data)):
            set2.append([item_data[i], result_data[i]])

        values, count = np.unique(item_data, return_counts=1)

        # Calculate entropy for each feature value
        for items in values:
            pos, neg, total = 0, 0, 0
            for it in set2:
                if it[0] == items:
                    if it[1] == 'yes':
                        pos += 1
                    else:
                        neg += 1
            total = pos + neg
            Entropy_of_item = (total / len(df)) * Entropy(pos + 0.000001, neg + 0.000001, total + 0.00001)
            entropy_list.append(Entropy_of_item)

        Entropy_count.append([class1, Entropy_of_table - sum(entropy_list)])

    # Find the feature with the highest information gain
    max1 = -100
    max_gain_col = None
    for set3 in Entropy_count:
        if set3[1] > max1:
            max1 = set3[1]
            max_gain_col = set3[0]
    
    print(f"Level {level}: Best split on '{max_gain_col}'")

    # Track information gain for plotting
    entropy_gains.append([level, max_gain_col, max1])

    # If the best feature is found, continue splitting
    if max_gain_col:
        demo = classes.copy()
        demo.remove(max_gain_col)
        item_data = np.array(df[max_gain_col].to_list())
        values = np.unique(item_data)
        
        # Recursively build the tree for each split
        for var in values:
            youth_data = df[df[max_gain_col] == var]
            Decision_tree(classes=demo, df=youth_data, level=level + 1)

# Build the decision tree
Decision_tree(classes=classes, df=df)

