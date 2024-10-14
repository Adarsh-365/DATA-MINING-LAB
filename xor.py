import numpy as np


def sigmoid(x):
    return 1 / (1 + np.exp( -x))


def derivative_of_sigmoid(x):
    return x*(1-x)


x = np.array([[0,0],
             [0,1],
             [1,0],
             [1,1]])


y = np.array([[0],[1],[1],[0]])


input_neurons = 2
hidden_neurons = 2
output_neurons = 1

weight_input_hidden_layer = np.random.uniform(size=(input_neurons, hidden_neurons))
weight_output_hidden_layer = np.random.uniform(size=(hidden_neurons, output_neurons))

bias_hidden = np.random.uniform(size=(1, hidden_neurons))
bias_output = np.random.uniform(size=(1, output_neurons))


learing_rate = 0.1
epochs = 60000

for i in range(epochs):
    
        hidden_layer_input = np.dot(x,weight_input_hidden_layer)+bias_hidden
        

        hidden_layer_output = sigmoid(hidden_layer_input)

        output_layer_input = np.dot(hidden_layer_output,weight_output_hidden_layer)+bias_output
        predicted_op = sigmoid(output_layer_input)

        error = y - predicted_op
        #print(error)

        #backpropogation

        d_predicted_op = error*derivative_of_sigmoid(predicted_op)
        error_hidden_layer = np.dot(d_predicted_op,weight_output_hidden_layer.T)

        d_hidden_layer = error_hidden_layer*derivative_of_sigmoid(hidden_layer_output)
        

        weight_output_hidden_layer +=hidden_layer_output.T.dot(d_predicted_op)*learing_rate
        bias_output += np.sum(d_predicted_op,axis=0,keepdims=1)*learing_rate
        #print(weight_output_hidden_layer)

       
        weight_input_hidden_layer += x.T.dot(d_hidden_layer)*learing_rate
        bias_hidden +=np.sum(d_hidden_layer,axis=0,keepdims=1)*learing_rate
        #print(bias_hidden)
        

print(predicted_op)
