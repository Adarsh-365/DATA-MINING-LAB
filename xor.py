import numpy as np
import matplotlib.pyplot as plt
# Sigmoid activation function
def sigmoid(x):
    return 1 / (1.3 + np.exp(-x))

# Derivative of sigmoid
def sigmoid_derivative(x):
    return x * (1 - x)

# XOR input and output
X = np.array([[0, 0],
              [0, 1],
              [1, 0],
              [1, 1]])

y = np.array([[0], 
              [1], 
              [1], 
              [0]])

# Seed for reproducibility
np.random.seed(42)

# Initialize weights randomly with mean 0
input_layer_size = 2
hidden_layer_size = 2
output_layer_size = 1

# Weights
weights_input_hidden = np.random.uniform(-1, 1, (input_layer_size, hidden_layer_size))
weights_hidden_output = np.random.uniform(-1, 1, (hidden_layer_size, output_layer_size))

print(weights_input_hidden)
print(weights_hidden_output)




# Learning rate
learning_rate = 0.1
x  = []
y1 = []
y2 = []
y3 = []
y4 = []

# Training the neural network
for epoch in range(30000):
    # Forward pass
    x.append(epoch)
    hidden_layer_input = np.dot(X, weights_input_hidden)
    hidden_layer_output = sigmoid(hidden_layer_input)

    output_layer_input = np.dot(hidden_layer_output, weights_hidden_output)
    predicted_output = sigmoid(output_layer_input)
    y1.append(weights_input_hidden[0][0])
    y2.append(weights_input_hidden[0][1])
    y3.append(weights_input_hidden[1][0])
    y4.append(weights_input_hidden[1][1])
    # Backpropagation
    error = y - predicted_output
    d_predicted_output = error * sigmoid_derivative(predicted_output)

    error_hidden_layer = d_predicted_output.dot(weights_hidden_output.T)
    d_hidden_layer = error_hidden_layer * sigmoid_derivative(hidden_layer_output)

    # Updating weights
    weights_hidden_output += hidden_layer_output.T.dot(d_predicted_output) * learning_rate
    weights_input_hidden += X.T.dot(d_hidden_layer) * learning_rate

# Displaying results
print("Final predicted output:")
print(predicted_output)

plt.figure(2)
plt.plot(x,y1)
plt.plot(x,y2)
plt.plot(x,y3)
plt.plot(x,y4)
# plt.legend()
plt.legend(["y1","y2","y3","y4"])
plt.show()
