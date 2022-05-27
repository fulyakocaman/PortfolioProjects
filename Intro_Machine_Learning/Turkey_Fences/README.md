In this project I familiarized myself with Python and Jupyter by implementing a rudimentary outlier detection algorithm.

Dataset: The file participants.csv contains meeting attendance data reported by Zoom for the first three weeks of a course. Each
row contains the name of a student along with the number of minutes that the student was logged in to the course Zoom meeting. 
(The names of students have been changed to protect the innocent.)

Experiments:
Run the following experiments in a Jupyter notebook, performing actions in code cells and reporting results in Markdown cells.
1. Use the csv module to load and examine the dataset.
2. Find the quartiles for Week 1. You may wish to consult the Python Sorting HOW TO document for help manipulating the data.
3. In order to record attendance, we want to find the students who logged into the Zoom meeting but did not attend the entire lecture. 
In order to do this, we can look for outliers in the data.
Tukey’s fences are a simple method to define outliers in terms of the interquartile range. Use this method with k = 1.5 to find the 
outliers in the Week 1 attendance data.
4. Repeat experiments (2) and (3) for Weeks 2 and 3.
5. Consolidate your code from experiments (2) through (4) into a Python function named tardy(). You may wish to define other functions as well.
This function should list the name and attendance statistics for any student whose attendance in any week falls below the bottom fence for that
 week. Tardy students should be listed in the same order as they appear in the original .csv file.
