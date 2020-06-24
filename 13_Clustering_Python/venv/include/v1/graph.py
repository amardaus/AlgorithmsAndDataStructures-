class Graph:

    def __init__(self, n, labels):
        self.n = n
        self.edges = []
        self.labels = labels

    def addEdge(self, u, v, w):
        self.edges.append([u, v, w])

    # (uses path compression technique)
    def find(self, parent, i):
        if parent[i] == i:
            return i
        return self.find(parent, parent[i])

        # A function that does union of two sets of x and y

    # (uses union by rank)
    def union(self, parent, rank, x, y):
        xroot = self.find(parent, x)
        yroot = self.find(parent, y)

        # Attach smaller rank tree under root of  
        # high rank tree (Union by Rank) 
        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot

            # If ranks are same, then make one as root
        # and increment its rank by one 
        else:
            parent[yroot] = xroot
            rank[xroot] += 1

    def assign(self, parents, K):
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
        result = []  # This will store the resultant MST

        i = 0  # An index variable, used for sorted edges
        e = 0  # An index variable, used for result[]

        # Step 1:  Sort all the edges in non-decreasing
        # order of their
        # weight.  If we are not allowed to change the
        # given edges, we can create a copy of edges
        self.edges = sorted(self.edges, key=lambda item: item[2])

        parent = [];
        rank = []

        # Create n subsets with single elements 
        for node in range(self.n):
            parent.append(node)
            rank.append(0)

            # Number of edges to be taken is equal to n-1
        while e < self.n - K:

            # Step 2: Pick the smallest edge and increment  
            # the index for next iteration
            u, v, w = self.edges[i]
            i = i + 1
            x = self.find(parent, u)
            y = self.find(parent, v)

            # If including this edge does't cause cycle,  
            # include it in result and increment the index
            # of result for next edge
            if x != y:
                e = e + 1
                result.append([u, v, w])
                self.union(parent, rank, x, y)
                # Else discard the edge

        clusters = self.assign(parent,K)
        return clusters
