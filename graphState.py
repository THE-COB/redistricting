import matplotlib.pyplot as plt
import csv

allPts = []

for i in range(0,16):
	with open("DATA/ohio2-19_1/cent"+str(i)+".csv") as f:
		reader = csv.reader(f)
		allPts.append(list(reader))

# for i in allPts:
# 	for j in range(0,len(i), 10000):
# 		plt.scatter(i[j][1],i[j][2])

plt.rcParams["figure.figsize"] = [9.5,9.5]

colors = ["C0","C1","C2","C3","C4","C5","C6","C7","C8","C9"]
colorCount = 0
for i in allPts:
	color = colors[colorCount]
	for j in range(0,len(i), 50):
		plt.scatter(float(i[j][0]),float(i[j][1]), c=color)
	colorCount+=1
	if(colorCount == 9):
		colorCount = 0

plt.show()