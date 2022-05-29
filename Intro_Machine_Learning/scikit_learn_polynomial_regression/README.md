In this project I used scikit-learn, which is a higher-level machine learning library that 
works with NumPy, to compare the performance of linear and polynomial regression models.

Experiments<p>
Run the following experiments in a Jupyter notebook, performing actions in code cells and reporting results in 
Markdown cells.<p>
1.Use the NumPy load() method to read the dataset. The data contains two arrays: 'features', which contains 
the variables CRIM through LSTAT, and 'target', which contains the variable MEDV.<p>
2.Use sklearn.model_selection.train_test_split() to split the features and target values into separate training 
and test sets. Use 80% of the original data as a training set, and 20% for testing. To make sure that your results
 are reproducible, pass random_state=(2021-3-11).<p>
3.Create a scatterplot of the training data showing the relationship between the percentage of the population 
that is lower status and the median value of a home. Does the relationship appear to be linear?
(Note that “status” here refers to socioeconomic status and is not a value judgement on the residents.)<p>
4.With LSTAT as X and MEDV as y, create and fit() an sklearn.linear_model.LinearRegression model. Using the 
coef_ and intercept_ attributes of the model, what is the equation for MEDV as a linear function of LSTAT?<p>
5.Use the coef_ and intercept_ attributes of the model to add a line representing the least squares fit to 
your scatter plot from experiment (3). How well does the model appear to fit the training data?<p>
6.Use the predict() method of the model to find the response for each value of the LSTAT attribute in the
 training set. Using sklearn.metrics.mean_squared_error(), find the average loss 𝓛 for the training set.<p>
7.Repeat experiment (6) for the test set. How do the training and test MSE values compare?<p>
8.Let’s see if we can fit the data better with a more flexible model. Use np.hstack() to add a degree-2 
polynomial feature to X, then fit a new linear model. How do the training and test MSE values for this
 model compare to the previous model?<p>
9.Repeat experiment (5) for your polynomial model.<p>
10.Repeat experiments (4), (6), and (7) using all 13 input features as X. How do the training and test 
MSEs for this model (which is a linear model including all features) compare to the values you found for
 experiment (8) (which was a degree-2 polynomial model including a single feature)? What accounts for 
the difference?<p>
11.Combine experiments (8) and (10), using np.hstack() to add the squares of all 13 input features to X. 
How do this model’s training and test MSE scores compare to the previous model using all 13 features?<p>
12.Scikit-learn is also capable of constructing polynomial features for us using sklearn.preprocessing.
PolynomialFeatures, but those features also include interaction features, where the feature terms are 
multiplied together.
Use the fit_transform() method to create degree-2 polynomial and interaction terms for the original set 
of 13 features, then fit a new linear model. Compare the training and test MSE to the previous model. What is the effect of adding interaction terms in this case? Do we seem to be overfitting?<p>
