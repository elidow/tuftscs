'''
hw1.py
Author: Eli Dow

Tufts CS 135 Intro ML

'''

# imports
import numpy as np
import math

def split_into_train_and_test(x_all_LF, frac_test=0.5, random_state=None):
    ''' Divide provided array into train and test set along first dimension

    User can provide a random number generator object to ensure reproducibility.

    Args
    ----
    x_all_LF : 2D array, shape = (n_total_examples, n_features) (L, F)
        Each row is a feature vector
    frac_test : float, fraction between 0 and 1
        Indicates fraction of all L examples to allocate to the "test" set
    random_state : np.random.RandomState instance or integer or None
        If int, code will create RandomState instance with provided value as seed
        If None, defaults to the current numpy random number generator np.random

    Returns
    -------
    x_train_MF : 2D array, shape = (n_train_examples, n_features) (M, F)
        Each row is a feature vector
        Should be a separately allocated array, NOT a view of any input array

    x_test_NF : 2D array, shape = (n_test_examples, n_features) (N, F)
        Each row is a feature vector
        Should be a separately allocated array, NOT a view of any input array

    Post Condition
    --------------
    This function should be side-effect free. The provided input array x_all_LF
    should not change at all (not be shuffled, etc.)

    Examples
    --------
    >>> x_LF = np.eye(10)
    >>> xcopy_LF = x_LF.copy() # preserve what input was before the call
    >>> train_MF, test_NF = split_into_train_and_test(
    ...     x_LF, frac_test=0.3, random_state=np.random.RandomState(0))
    >>> train_MF.shape
    (7, 10)
    >>> test_NF.shape
    (3, 10)
    >>> print(train_MF)
    [[0. 0. 1. 0. 0. 0. 0. 0. 0. 0.]
     [0. 0. 0. 0. 0. 0. 0. 0. 1. 0.]
     [0. 0. 0. 0. 1. 0. 0. 0. 0. 0.]
     [0. 0. 0. 0. 0. 0. 0. 0. 0. 1.]
     [0. 1. 0. 0. 0. 0. 0. 0. 0. 0.]
     [0. 0. 0. 0. 0. 0. 1. 0. 0. 0.]
     [0. 0. 0. 0. 0. 0. 0. 1. 0. 0.]]
    >>> print(test_NF)
    [[0. 0. 0. 1. 0. 0. 0. 0. 0. 0.]
     [1. 0. 0. 0. 0. 0. 0. 0. 0. 0.]
     [0. 0. 0. 0. 0. 1. 0. 0. 0. 0.]]

    ## Verify that input array did not change due to function call
    >>> np.allclose(x_LF, xcopy_LF)
    True

    References
    ----------
    For more about RandomState, see:
    https://stackoverflow.com/questions/28064634/random-state-pseudo-random-numberin-scikit-learn
    '''

    if random_state is None:            # if None, random_state defaults to np.rando
        random_state = np.random
    else:                               # else, code will create RandomState instance with provided value as seed
        random_state = np.random.RandomState(seed = random_state)

    # retrieving size of input array and determining testing size
    input_size = len(x_all_LF)
    testing_size = int(math.ceil(frac_test * input_size))

    # get deep copy of input array and shuffle it with random_state
    x_all_LF_copy = x_all_LF.copy()
    shuffled = random_state.permutation(x_all_LF_copy)

    # divide x_all_LF into 2 mutually exclusive arrays: training and testing set
    x_train_MF = shuffled[testing_size:]
    x_test_NF = shuffled[0:testing_size]

    return np.array(x_train_MF), np.array(x_test_NF)


def calc_k_nearest_neighbors(data_NF, query_QF, K=1):
    ''' Compute and return k-nearest neighbors under Euclidean distance

    Any ties in distance may be broken arbitrarily.

    Args
    ----
    data_NF : 2D array, shape = (n_examples, n_features) aka (N, F)
        Each row is a feature vector for one example in dataset
    query_QF : 2D array, shape = (n_queries, n_features) aka (Q, F)
        Each row is a feature vector whose neighbors we want to find
    K : int, positive (must be >= 1)
        Number of neighbors to find per query vector

    Returns
    -------
    neighb_QKF : 3D array, (n_queries, n_neighbors, n_feats) (Q, K, F)
        Entry q,k is feature vector of the k-th neighbor of the q-th query
    '''

    # retrieving sizes of all arrays
    data_size = len(data_NF)
    query_size = len(query_QF)
    vector_size = len(data_NF[0])

    # initializing 3 dimensional array and dictionary for sorting
    neighb_QKF = []
    ED_for_queries = {}

    # looping through the query array
    for i in range(query_size):
        curr_query = query_QF[i]        # variable set to current query
        all_VD = []                     # list of all vectors and distances to query i

        # looping through data array
        for j in range(data_size):
            curr_vector = data_NF[j]      # variable set to current vector
            VD = []                       # array with vector and distance
            sum = 0                       # variables for euclidean distance
            euclidean_distance = 0

            # find euclidean distance of V1 and V2: ED = sqrt(sum[1 to vector_size]((V1 - V2)^2))
            for k in range(vector_size):
                sum += (curr_query[k] - curr_vector[k])**2
            euclidean_distance = math.sqrt(sum)

            # add tuple of vector and distance to all_VD
            VD.append(curr_vector)
            VD.append(euclidean_distance)
            all_VD.append(VD)

        # add to key-value pair to dictionary
        ED_for_queries[i] = all_VD

    # sort dictionary and add k-closest neighbors to neighb_QKF
    for i in range(len(ED_for_queries)):
        # sorting value of every dictionary by their euclidean distances
        # used lambda function (built in Math)
        ED_for_queries[i].sort(key = lambda item:item[1])

        k_closest = []    # initializing k-closest neighbors
        k_counter = 0     # keeping track of k

        # appending k_closest neighbors for every query to neighb_QFK
        for j in ED_for_queries[i]:
            if k_counter < K:
                k_closest.append(j[0])
                k_counter += 1
        neighb_QKF.append(k_closest)

    return np.array(neighb_QKF)


