In this project I used NumPy to implement vectorized linear and polynomial regression 
models and compare their performance using separate training and test sets.<p>

Experiments<p>
Run the following experiments in a Jupyter notebook, performing actions in code cells and reporting results in 
Markdown cells.<p>
1.Use the NumPy load() method to read the dataset. The data contains two arrays: 'features', which contains the 
variables CRIM through LSTAT, and 'target', which contains the variable MEDV.<p>
2.Set aside the first 102 items (20% of the total) as a validation set, and the remaining 404 items for training.<p>
3.Create a scatterplot of the training data showing the relationship between the number of rooms and the median 
value of a home. Does the relationship appear to be linear?<p>
4.With RM as X and MEDV as t, use np.linalg.inv() to compute w for the training set. What is the equation for MEDV 
as a linear function of RM?<p>
5.Use w to add a line representing the least squares fit to your scatter plot from experiment (3). How well does 
the model appear to fit the training set?<p>
6.Use w to find the predicted response for each value of the RM attribute in the training set, then compute the 
average loss 𝓛 for the model.<p>
7.Repeat experiment (6) for the validation set. How do the training and validation MSE values compare? What 
accounts for the difference?<p>
8.Repeat experiments (4), (6), and (7) using all 13 input features as X. How do the training and validation 
MSEs for this model compare to the values you found for experiment (7). What accounts for the difference?<p>
9.Based on the value you found for w for this new model, how much does a one unit increase in each feature 
change the median value of the home? Based on the description of the dataset provided by StatLib, convert your answer to dollars.<p>
10.Based on the amount of change in the value of a home, which features are most important?<p>
