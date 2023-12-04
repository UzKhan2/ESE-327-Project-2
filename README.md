# Project Description

**Implement the Decision Tree Induction Algorithm on a group of datasets**

- The algorithm implements a tree system to store the frequent data sets in order
- Minimize run time
- Create a version of the code to run parallel on both the CPU and GPU

<br /> **Program inputs:**

- Data Values (DATA)
- Data Names

# Decision Tree Induction Algorithm

<br /> **Initialization**

- Begin with the entire dataset
- Select the best attribute to split the data based on certain criteria

<br /> **Splitting**

- Divide the dataset into subsets based on the values of the selected attribute
- Each subset represents a branch from the current node

<br /> **Recursive Process**

- For each subset, repeat the process (recursively)
- Choose the best attribute in the current subset and split it further
- Continue until a stopping criterion is met, such as a maximum depth or a minimum number of samples in a leaf node

<br /> **Stopping Criteria**

- Decide when to stop the tree from growing further
- Common stopping criteria include reaching a certain depth, having a minimum number of samples in a leaf, or reaching a purity threshold

<br /> **Leaf Node Creation**

- Once a stopping criterion is met, create a leaf node for the subset
- Assign the most frequent class label (for classification) or the mean value (for regression) of the target variable in the subset to the leaf node

<br /> **Attribute Selection Criteria:**

- The algorithm uses a measure to evaluate the importance of different attributes for splitting. Common criteria include Gini impurity, information gain, or mean squared error, depending on whether it's a classification or regression problem

- Gini Impurity: Measures the frequency at which a randomly chosen element would be incorrectly labeled

- Information Gain: Measures the reduction in entropy (uncertainty) after a dataset is split

- Mean Squared Error (MSE): Measures the average squared difference between the actual and predicted values for regression problems

<br /> **Pruning**

- To avoid overfitting, pruning may be applied. Pruning involves removing parts of the tree that do not provide significant predictive power
- This can be done by merging or removing nodes based on their impurity or error rate

<br /> **Prediction**

- To predict for a new instance, traverse the tree from the root to a leaf, following the decision rules at each node
