import csv
import math
from graph import Graph
from scipy.spatial import distance
from matplotlib import pyplot as plt
import numpy as np

def euclideanDist(p1,p2,dim):
    dist = 0
    for d in range(0,dim):
        dist += (p1[d]-p2[d])**2
    return dist

points = []
f = open("../../data/sample_data.csv", "r")
reader = csv.reader(f)
labels = []

for row in reader:
    points.append(row[0:len(row)-1])
    labels.append(row[len(row)-1])

points.remove(points[0])
labels.remove(labels[0])

dim = len(points[0])
n = len(points)

for i in range(0, n):
    for j in range(0, dim):
            points[i][j] = float(points[i][j])
    labels[i] = int(labels[i])

distances = [[0]*n for i in range(n)]
for i in range(0,n):
    for j in range(0,n):
        if i == j:
            distances[i][j] = 0
        else:
            distances[i][j] = euclideanDist(points[i],points[j],dim)

g = Graph(n,labels)

for i in range(0,n):
    for j in range(0,n):
        g.addEdge(i,j,distances[i][j])

K = 3
clusters = g.KruskalMST(K)

colors = ["blue","red","orange","yellow","green"]
for cluster,cpoints in clusters.items():
    X = []
    Y = []
    for p in cpoints:
        X.append(points[p][0])
        Y.append(points[p][1])
    plt.scatter(X,Y,color=colors[cluster])

plt.show()