In this project we will see some of the challenges of working with a “real-world” dataset, 
see the importance of exploratory data analysis to understand the features, and experiment 
with regularization.

Experiments
Run the following experiments in a Jupyter notebook, performing actions in code cells and reporting results in Markdown cells.
1.Load the California Housing dataset as a Pandas DataFrame and examine its features, target values, and description. Tips:
You can call the head() method on a DataFrame to examine only its first few rows.
If you evaluate a DataFrame (by including it as the last item in a code cell) rather than passing it to the print() function, 
it will be displayed in an easier-to-read HTML table format.
2.Use sklearn.model_selection.train_test_split() to split the features and target values into separate training and test sets.
 Use 80% of the original data as a training set, and 20% for testing. To make sure that your results are reproducible, pass 
random_state=(2021-3-25).
3.Recall that when we originally discussed housing prices, we suggested that the price of a house might depend on how many 
bedrooms it has. Create and fit() an sklearn.linear_model.LinearRegression model using AveBedrms as a predictor of MedHouseVal.
Use the predict() method of the model to find the response for each value in the test set, and sklearn.metrics.mean_squared_error(),
 to find the training and test MSE.
4.By itself, the MSE doesn’t tell us much. Use the score() method of the model to find the R2 values for the training and test sets.
R2, the coefficient of determination, measures the proportion of variability in the target t that can be explained using the features
 in X. A value near 1 indicates that most of the variability in the response has been explained by the regression, while a value near
 0 indicates that the regression does not explain much of the variability. See Section 3.1.3 of An Introduction to Statistical 
Learning for details.
Given the R2 scores, how well did our model do?
5.Let’s take a closer look at the data. Use pandas.plotting.scatter_matrix() to plot each pair of features. Note that you will probably
 want to use the optional figsize parameter to enlarge the plot. Examine the row (or column) for MedHouseVal to see how it varies with
 each of the other features.
6.The graphs are rather crowded because of the size of the dataset. Try the plot again using a sample() of 1%. How does the AveBedrms
 feature appear to affect MedHouseVal? How does this explain the value of R2 you found in experiment (4)?
7.Which features seem to have the strongest linear relationship with MedHouseVal?
8.What relationship do you see between MedHouseVal and the Latitude and Longitude features? Look these values up on a map of the
 state and explain what you see.
(If you are feeling particularly ambitious, you might try plotting the values on a map.)
9.Covariance is difficult to interpret because the various features are on very different scales. While you could standardize the 
features yourself, the correlation matrix is the covariance matrix of the standardized variables. Based on the correlation matrix, 
which feature is the strongest predictor of MedHouseVal? Does this match your answer in experiment (7)?
10.Repeat experiment (4) using the feature you found in the last experiment instead of AveBedrms. How well does this model score?
11.Repeat experiment (10) using all 8 input features. How do the training and test MSEs for this model compare to that experiment?
12.Scikit-learn is capable of constructing polynomial features for us using sklearn.preprocessing.PolynomialFeatures. Use the 
fit_transform() method to create degree-2 polynomial and interaction terms for the entire set of 8 features, then fit a new 
linear model. Compare the training and test MSE to the previous model. Does adding polynomial terms lead to overfitting?
13.Regularization would allow us to construct a model of intermediate complexity (i.e. between linear and quadratic) by penalizing
 large values for the coefficients. Scikit-learn provides this L2-regularization as sklearn.linear_model.Ridge. The parameter
 alpha corresponds to 𝜆 as shown in the textbook.
For now, leave 𝜆 set to the default value of 1.0, and fit the model to the degree-2 polynomial features. Recall that regularization
 requires all the same features to be on the same scale, so pass normalize=True.
Once again, compare the training and test MSE and R2 scores to the previous model. Does this model perform better?
