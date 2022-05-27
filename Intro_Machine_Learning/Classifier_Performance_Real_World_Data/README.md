In this project I ran into a new set of challenges when working with a “real-world” dataset, and see how an imbalanced dataset can
 influence classifier performance.

Experiments
Run the following experiments in a Jupyter notebook, performing actions in code cells and reporting results in Markdown cells.
1.Download bank-additional.zip and extract its contents. Since the dataset is large and some of the algorithms we will use 
can be time-consuming, we will train with bank-additional.csv, which is a subset of the original dataset.
Once our models are trained, we will test against the full dataset, which is in bank-additional-full.csv.
The archive also contains a text file, bank-additional-names.txt, which describes the dataset and what each column represents.
2.Use read_csv() to load and examine the training and test sets. Unlike most CSV files, the separator is actually ';' rather than ','.
3.The training and test DataFrames will need some significant preprocessing before they can be used:
a.Several of the features are categorical variables and will need to be turned into numbers before they can be used by ML 
algorithms. The simplest way to accomplish this is to use dummy coding using the Pandas get_dummies() method.
Note: some algorithms (e.g. logistic regression) have problems with collinear features. If you use one-hot encoding, one 
dummy variable will be a linear combination of the other dummy variables, so be sure to pass drop_first=True.
b.Two features should be removed from the dataset:
i.Per bank-additional-names.txt, the duration “should be discarded if the intention is to have a realistic predictive model.”
ii.The feature y (or y_yes after dummy coding) is the target.
c.Some algorithms (e.g. KNN and SVM) require non-categorical features to be standardized. 
4.Fit Naive Bayes, KNN, and SVM classifiers to the training set, then score each classifier on the test set. Which classifier 
has the highest accuracy?
5.These numbers look pretty good, but let’s take another look at the data. How many values in the training set have y_yes = 0,
 and how many have y_yes = 1? What would be the accuracy if we simply assumed that no customer ever subscribed to the product?
6.Use np.zeros_like() to create a target vector representing the output of the “dumb” classifier of experiment (5), then create
 a confusion matrix and find its AUC.
7.Create a confusion matrix and find the AUC for each of the classifiers of experiment (4). Is the best classifier the one with
 the highest accuracy?
8.One of the easiest ways to deal with an unbalanced dataset is random oversampling. This can be done with an 
imblearn.over_sampling.RandomOverSampler object. Use fit_resample() to generate a balanced training set. To make sure that 
your results are reproducible, pass random_state=(2021-4-22).
9.Repeat experiments (4) and (7) on the balanced training set of experiment (8). Which classifier performs the best, and how 
much better is its performance?
