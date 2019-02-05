import pandas as pd
import tensorflow as tf

from tensorflow.python.client import device_lib

tf.reset_default_graph()

# from google.colab import files

# files.upload()

# Train Data
dataframe = pd.read_csv("data.csv")

dataframe.loc[:, ("setosa")] = dataframe.loc[:, ("class")] == "Iris-setosa"
dataframe.loc[:, ("versicolor")] = dataframe.loc[:, ("class")] == "Iris-versicolor"
dataframe.loc[:, ("virginica")] = dataframe.loc[:, ("class")] == "Iris-virginica"

dataframe.loc[:, ("setosa")] = dataframe.loc[:, ("setosa")].astype(float)
dataframe.loc[:, ("versicolor")] = dataframe.loc[:, ("versicolor")].astype(float)
dataframe.loc[:, ("virginica")] = dataframe.loc[:, ("virginica")].astype(float)
dataframe = dataframe.drop(["class"], axis=1)

inputX = dataframe.loc[:, ("sepal length", "sepal width", "petal length", "petal width")].as_matrix()
inputY = dataframe.loc[:, ("setosa", "versicolor", "virginica")].as_matrix()

# Test Data
test_dataframe = pd.read_csv("test_data.csv")

test_dataframe.loc[:, ("setosa")] = test_dataframe.loc[:, ("class")] == "Iris-setosa"
test_dataframe.loc[:, ("versicolor")] = test_dataframe.loc[:, ("class")] == "Iris-versicolor"
test_dataframe.loc[:, ("virginica")] = test_dataframe.loc[:, ("class")] == "Iris-virginica"

test_dataframe.loc[:, ("setosa")] = test_dataframe.loc[:, ("setosa")].astype(float)
test_dataframe.loc[:, ("versicolor")] = test_dataframe.loc[:, ("versicolor")].astype(float)
test_dataframe.loc[:, ("virginica")] = test_dataframe.loc[:, ("virginica")].astype(float)
test_dataframe = test_dataframe.drop(["class"], axis=1)

inputX_test = test_dataframe.loc[:, ("sepal length", "sepal width", "petal length", "petal width")].as_matrix()
inputY_test = test_dataframe.loc[:, ("setosa", "versicolor", "virginica")].as_matrix()

print("InputX      :", len(inputX))
print("InputY      :", len(inputY))
print("InputX_test :", len(inputX_test))
print("InputY_test :", len(inputY_test))

# Model
n_samples = inputY.size
learning_rate = 0.0037
epochs = 100000 #@param
display_rate = int( epochs / 10 )


x = tf.placeholder(tf.float32, [None, 4], name="input_ph")

# Input
weights_input = tf.Variable(tf.truncated_normal([4, 3]), name="w_input")
biases_input = tf.Variable(tf.zeros([1, 3]), name="b_input")
preactivation_input = tf.add( tf.matmul(x, weights_input) , biases_input )
activation_input = tf.sigmoid(preactivation_input)

# Output
weights_output = tf.Variable(tf.truncated_normal([3, 3]), name="w_output")
biases_output = tf.Variable(tf.zeros([1, 3]), name="b_output")
preactivation_output = tf.add( tf.matmul(activation_input, weights_output) , biases_output )
guess = tf.sigmoid(preactivation_output)

y = tf.placeholder(tf.float32, [None, 3], name="output_ph")

loss = tf.reduce_sum( tf.pow(y - guess, 2) ) / ( 2 * n_samples )

optimizer = tf.train.GradientDescentOptimizer(learning_rate).minimize(loss)

init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)

saver = tf.train.Saver(max_to_keep=5)

if input("[?] Restore? (y/n): ").lower() == "y":
    saver.restore(sess, "tmp/irys")
    print("[+] Restored")

for epoch_it in range(epochs):
    sess.run( optimizer, feed_dict={ x:inputX, y:inputY } )
    if epoch_it % display_rate == 0:
        saver.save(sess, "tmp/irys")
        print("Saved")
        cost = sess.run( loss, feed_dict={ x:inputX, y:inputY } )
        print("- Cost:", cost)
        print("-"*32)

answer_train_data = tf.equal(tf.floor(guess + 0.5), y)
accuracy_train_data = tf.reduce_mean( tf.cast(answer_train_data, "float") )
accuracy_result_train_data = accuracy_train_data.eval({ x:inputX, y:inputY }, session=sess)
print("[TRAIN DATA] Accuracy: %2.f%%" % (accuracy_result_train_data*100) )
        
answer_test = tf.equal(tf.floor(guess + 0.5), y)
accuracy_test = tf.reduce_mean( tf.cast(answer_test, "float") )
accuracy_result_test = accuracy_test.eval({ x:inputX_test, y:inputY_test }, session=sess)
print("[TEST SAMPLE] Accuracy: %2.f%%" % (accuracy_result_test*100) )

cost = sess.run( loss, feed_dict={ x:inputX, y:inputY } )
print("Cost:", cost)
print("[+] Done training")