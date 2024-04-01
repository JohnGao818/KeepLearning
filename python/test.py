def bubble_sort(data):
    n=len(data)
    for i in range(0, n-1):
        for j in range(n-1, i, -1):
            if data[j-1][1]<data[j][1]:
                temp=data[j]
                data[j]=data[j-1]
                data[j-1]=temp
        if data[i][1]==0:
            break

def group(data, m):
    n=len(data)
    a=[]
    for i in range(n+1):
        a.append([])
    gnum=0
    for i in range(n):
        while data[i][1]>=m:
            gnum+=1
            k=data[i][0]
            a[k].append(gnum)
            data[i][1]-=m
    bubble_sort(data)
    b=[]
    for i in range(m):
        b.append([])
    i=0
    while i<n and data[i][1]!=0:
        j=data[i][1]
        while j<m and len(b[j])==0:
            j+=1
        if j<m:
            v=b[j].pop()
        else:
            gnum+=1
            v=gnum
        a[data[i][0]].append(v)
        b[j - data[i][1]].append(v)
        i+=1
    for i in range(1, n+1):
        print(i, a[i])

data=[[1, 23], [2, 17], [3, 54], [4, 20], [5, 38]]
m=20
group(data, m)
