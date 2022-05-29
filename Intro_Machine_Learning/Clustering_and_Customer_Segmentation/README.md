# Clustering and Customer Segmentation 

In this project I compared the results of using clustering algorithms to segment customers based on their purchasing data.

Experiments
Run the following experiments in a Jupyter notebook, performing actions in code cells and reporting results in Markdown cells.
1. Use read_csv() to load and examine the dataset.
2. Use sklearn.cluster.KMeans to cluster the dataset using the default parameters. Assign the labels_ attribute determined 
by the algorithm to a new column in your DataFrame. How many clusters are there?
3. Use pandas.DataFrame.groupby() to group the data by cluster assignment, then use the GroupBy object to examine descriptive 
statistics such as minimum, maximum, and mean. Describe any differences you see between the clusters.
Caution: don’t include the cluster number that you added in the previous experiment as one of the features to be clustered in 
later steps, or it will skew your results
4. There’s no particular reason to think that the default value of K is the correct one for this dataset. Let’s switch to hierarchical 
clustering to see if we can visualize how the data clusters together.
Plot a scipy.cluster.hierarchy.dendrogram() for the dataset using each of the types of linkage described in Table 10.2 of An 
Introduction to Statistical Learning.
Based on the dendrogram, how many clusters appear to be present in the dataset? You may need to plot several dendrograms before
 the answer becomes clear.
Caution: SciPy sets the colors for dendrograms using a default threshold. This may not correspond to the best location for a cut
 with your particular dataset.
5. Repeat experiment (2) using the number of clusters you determined to be present in experiment (4).
6. Now switch to sklearn.cluster.AgglomerativeClustering() and repeat for the same number of clusters. How do the label assignments 
compare for the two algorithms?
Caution: once again, don’t include the cluster number determined in the previous experiment as one of the features to be clustered, 
or it will skew your results.
7. Repeat experiment (3) with the clusters you obtained in experiment (5). How would you describe the various types of customers? 
What can you determine about them based on the data?
8. For each customer segment identified, suggest some other items they would and would not be likely to purchase in future shopping trips.. 
