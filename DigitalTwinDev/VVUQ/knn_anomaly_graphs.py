import pandas as pd
import numpy as np
import seaborn as sns
import math
# %matplotlib widget
# %matplotlib inline
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score
from sklearn.metrics import mean_squared_error
from sklearn.datasets import load_digits
from sklearn.datasets import load_wine
from sklearn.cluster import KMeans
from sklearn import preprocessing
from datetime import datetime
from datetime import timedelta
import statistics as s
import scipy as stats
import statsmodels.api as sm
from sklearn.preprocessing import RobustScaler
from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import LeaveOneOut
from sklearn.model_selection import cross_val_score
from sklearn.metrics import classification_report
from reportlab.pdfgen import canvas
from reportlab.lib.pagesizes import letter
from sklearn.metrics import precision_score
from sklearn.metrics import recall_score
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
import torchvision
import torchvision.transforms as transforms
from torchvision import datasets, transforms
from sklearn.neural_network import MLPClassifier
from sklearn.neural_network import MLPRegressor
# import tensorflow as tf
# from tensorflow.keras.models import Sequential
# from tensorflow.keras.layers import Dense
# from tensorflow.keras.datasets import mnist
import yfinance as yf
from datetime import date
import matplotlib.dates as mdates
from sklearn.decomposition import PCA
from mlxtend.plotting import plot_decision_regions
from sklearn.neighbors import LocalOutlierFactor
import schedule
import time

import os
# print(os.getcwd())

script_dir = os.path.dirname(os.path.abspath(__file__))
csv_file_path1 = os.path.join(script_dir, "data_good_1.csv")
csv_file_path2 = os.path.join(script_dir, "data_good_2.csv")
csv_file_path3 = os.path.join(script_dir, "data_good_3.csv")
csv_file_path4 = os.path.join(script_dir, "data_good_4.csv")

csv_file_path5 = os.path.join(script_dir, "bad_data.csv")


data_good_1_orig = pd.read_csv(csv_file_path1)
data_good_2_orig = pd.read_csv(csv_file_path2)
data_good_3_orig = pd.read_csv(csv_file_path3)
data_good_4_orig = pd.read_csv(csv_file_path4)

bad_data_1_orig = pd.read_csv(csv_file_path5)

# C:\Users\jas45\dt_project\digital_twins
# data_good_1_orig = pd.read_csv("data_good_1.csv", delimiter=',')
# data_good_2_orig = pd.read_csv("data_good_2.csv", delimiter=',')
# data_good_3_orig = pd.read_csv("data_good_3.csv", delimiter=',')
# data_good_4_orig = pd.read_csv("data_good_4.csv", delimiter=',')


copy1 = data_good_1_orig.copy()
copy2 = data_good_2_orig.copy()
copy3 = data_good_3_orig.copy()
copy4 = data_good_4_orig.copy()
# copy4 = copy4 * 1.5
copy5 = bad_data_1_orig.copy()

data_combined = pd.concat([copy1['x'], copy2['x'], copy3['x'], copy4['x'], copy5['x']], axis=1)

# data_combined = np.concatenate([copy1['x'], copy2['x'], copy3['x'], copy4['x'], copy5['x']], axis=0) 
data_combinedy = np.concatenate([copy1['y'], copy2['y'], copy3['y'], copy4['y'], copy5['y']], axis=0)
data_combined = pd.DataFrame(data_combined)
data_combinedy = pd.DataFrame(data_combinedy)

data_combinedxy = np.concatenate([data_combined, data_combinedy], axis=1)
data_combinedxy = pd.DataFrame(data_combinedxy)
data_combinedxy.columns = ['x', 'y']

data_xy_copy = data_combined.copy() #data_combinedxy.copy()
shuffled_df = data_combinedxy.copy()

# data_xy_copy = data_xy_copy.drop(columns=['anomaly'])

p_data_df = data_xy_copy
xy_groups = 500
xy_splits = {}

for i in range(0, xy_groups, 1):
    p_data_split = p_data_df[(len(p_data_df)//xy_groups)*(i):(len(p_data_df)//xy_groups)*(i+1)] # splits shuffled data into groups
    xy_splits[f'split_{i}'] = pd.DataFrame(p_data_split)


pocket_split_std_features = {}
pocket_split_mean_features = {}

for i in range(0, xy_groups, 1):
    p_data_std_features = pd.DataFrame(xy_splits[f'split_{i}']).std()
    pocket_split_std_features[f'split_{i}'] = p_data_std_features

for i in range(0, xy_groups, 1):
    p_data_mean_features = pd.DataFrame(xy_splits[f'split_{i}']).mean()
    pocket_split_mean_features[f'split_{i}'] = p_data_mean_features



i = 0

split_features = {}

# for i in range(0, 500, 1):
data_features = pd.DataFrame(xy_splits[f'split_{i}']) #.mean()
split_features[f'split_{i}'] = data_features

# split_features = data_features

# data_features_df = pd.DataFrame.from_dict(split_features, orient='index')
df = split_features[f'split_{0}']

fig, ax = plt.subplots()
scatter1 = ax.scatter([], [], label='Normal Points', s=0.7) # Initialize an empty scatter plot
scatter2 = ax.scatter([], [], label='Detected Anomalies', s=0.7)
ax.legend()
for i in range(1, 10, 1):

    df = pd.DataFrame(np.concatenate([xy_splits[f'split_{i - 1}'], xy_splits[f'split_{i}']], axis=0))

    clf = LocalOutlierFactor(n_neighbors=15, contamination='auto')
    y_pred = clf.fit_predict(df)

    df['anomaly'] = y_pred

    normal_points = df[df['anomaly'] == 1]

    anomalies = df[df['anomaly'] == -1]

    scatter1 = ax.scatter(normal_points[0], normal_points[1], color='b', label='Normal Points', s=0.7)
    scatter2 = ax.scatter(anomalies[0], anomalies[1], color='r', label='Detected Anomalies', s=0.7)
    

    ax.set_title(f"batch: {i}        anomalies: {(df['anomaly'] == -1).sum()}")
    print()
    plt.pause(1)

# Try to archive the good data so the knn model does not have to run every time. Maybe save the average 
# location or standard deviation of the locations to test the new data against