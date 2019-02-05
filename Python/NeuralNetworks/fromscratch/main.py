import numpy as np
import math

def activation(x, c = 1.0):
    return 1./(1. + math.pow(math.e, -x*c))
activation_v = np.vectorize(activation)

learning_rate = 0.5

w1 = .15
w2 = .2
w3 = .25
w4 = .3
w5 = .4
w6 = .45
w7 = .5
w8 = .55

epochs = 10

# Hidden Layer 1 : weights and biases
l1w = np.array([[w1, w3],[w2, w4]])
l1b = np.array([[.35, .35]])
# Output Layer : weights and biases
l2w = np.array([[w5, w7],[w6, w8]])
l2b = np.array([[.6, .6]])

for i in range(epochs):

    ### Feed forward
    ideal = np.array([[.01, .99]]) # labels, ideal output
    input_ = np.array([[.05, .1]]) # features, input

    # Hidden Layer 1 : net/out Values
    h_net = np.dot(input_, l1w) + l1b
    h_out = activation_v(h_net)

    # Output Layer : net/out Values
    o_net = np.dot(h_out, l2w) + l2b
    o_out = activation_v(o_net)

    total_error = (1./2.) * (o_out - ideal)**2;

    print(round(total_error.sum(), 9))

    ### Backpropagation

    # Output layer
    delta_o = (o_out-ideal) * (o_out*(1. - o_out))

    El2 = delta_o * h_out.T

    # Hidden layer
    delta_h = np.dot(delta_o,l2w.T) * (h_out*(1. - h_out))
    El1 = delta_h * input_.T


    l2w = l2w - El2 * learning_rate
    l1w = l1w - El1 * learning_rate
