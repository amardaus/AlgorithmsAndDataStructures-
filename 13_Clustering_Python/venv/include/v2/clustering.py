import csv
import math
from graph import Graph
from scipy.spatial import distance
from matplotlib import pyplot as plt
import numpy as np
from sklearn.metrics.cluster import homogeneity_score
from sklearn.metrics.cluster import completeness_score
from sklearn.metrics import v_measure_score

def euclideanDist(p1,p2,dim):
    dist = 0
    for d in range(0,dim):
        dist += (p1[d]-p2[d])**2
    return np.sqrt(dist)

def silhouette(K,clusters):
    if K == 1:
        return 1

    a = {}
    for cluster, e in clusters.items():
        C = len(e)
        for i in e:
            d = 0
            for j in e:
                if i != j:
                    d += distances[i][j]
            if C > 1:
                a[i] = d / (C - 1)
            else:
                a[i] = math.inf

    b = {}
    for cluster, e in clusters.items():
        for i in e:
            for other, oe in clusters.items():
                if other != cluster:
                    C = len(oe)
                    d = 0
                    for j in oe:
                        d += distances[i][j]
                    if i in b:
                        if b[i] > d / C:
                            b[i] = d / C
                    else:
                        b[i] = d / C
    s = {}
    for i in range(0,K):
        if a[i] < b[i]:
            s[i] = 1 - a[i] / b[i]
        elif a[i] > b[i]:
            s[i] = b[i] / a[i] - 1
        else:
            s[i] = 0

    sm = sum(s.values()) / len(s)
    return sm


points = []
f = open("../../data/data_3.csv", "r")
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

"""
maxScore = -1
K = 1
for k in range(2,6):
    clusters = g.KruskalMST(K)
    score = silhouette(K,clusters)
    if score > maxScore:
        maxScore = score
        K = k
print(K)
print(maxScore)
"""

K = 5
clusters = g.KruskalMST(K)
silhouette(K,clusters)

clabels = [None]*n
for index,items in clusters.items():
    for item in items:
        clabels[item] = index

colors = ["blue","red","cyan","yellow","green","magenta","orange","black"]
for cluster,cpoints in clusters.items():
    X = []
    Y = []
    for p in cpoints:
        X.append(points[p][0])
        Y.append(points[p][1])
    plt.scatter(X,Y,color=colors[cluster])
plt.show()

print("completeness: " + str(completeness_score(labels,clabels)))
print("homogeneity: " + str(homogeneity_score(labels,clabels)))
print("v_measure: " + str(v_measure_score(labels,clabels)))