class Graph:

    def __init__(self, n, labels):
        self.n = n
        self.edges = []
        self.labels = labels

    def addEdge(self, u, v, w):
        self.edges.append([u, v, w])

    def find(self, parent, i):
        if parent[i] == i:
            return i
        return self.find(parent, parent[i])

    def union(self, parent, rank, x, y):
        xroot = self.find(parent, x)
        yroot = self.find(parent, y)

        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot

        else:
            parent[yroot] = xroot
            rank[xroot] += 1

    def assign(self, parents):
        roots = {}
        maxlabel = max(self.labels)

        labelcount = 0
        for i in range(0,self.n):
            if parents[i] == i:
                if labelcount <= maxlabel:
                    roots[i] = self.labels[i]
                else:
                    roots[i] = labelcount
                labelcount += 1

        clusters = {}
        for root,label in roots.items():
            clusters[label] = []

        for v in range(0,self.n):
            clusters[roots[self.find(parents, v)]].append(v)

        return clusters

    def KruskalMST(self, K):
        result = []
        i = 0
        e = 0
        self.edges = sorted(self.edges, key=lambda item: item[2])

        parent = []
        rank = []
        for node in range(self.n):
            parent.append(node)
            rank.append(0)

        while e < self.n - K:
            u, v, w = self.edges[i]
            i = i + 1
            x = self.find(parent, u)
            y = self.find(parent, v)

            if x != y:
                e = e + 1
                result.append([u, v, w])
                self.union(parent, rank, x, y)

        clusters = self.assign(parent)
        return clusters