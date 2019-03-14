import matplotlib.pyplot as plt
import csv
import sys

baseFolder = "DATA/marylandBalance/marylandBalance3-14_"#+sys.argv[1]+"_"+sys.argv[2]

# for i in allPts:
# 	for j in range(0,len(i), 10000):
# 		plt.scatter(i[j][1],i[j][2])

changer = ""

def graphState(folderName):
	allPts = []
	for i in range(0,8):
		with open(folderName+"/cent"+str(i)+".csv") as f:
			reader = csv.reader(f)
			allPts.append(list(reader))

	plt.rcParams["figure.figsize"] = [10,6]

	colors = ["C0","C1","C2","C3","C4","C5","C6","C7","C8","C9"]
	colorCount = 0
	for i in allPts:
		color = colors[colorCount]
		for j in range(0,len(i), 25):
			plt.scatter(float(i[j][0]),float(i[j][1]), c=color)
		colorCount+=1
		if(colorCount == 9):
			colorCount = 0

	cents = []
	with open(folderName+"/centCoords.csv") as f:
		reader = csv.reader(f)
		cents.append(list(reader))

	for i in cents[0]:
		plt.scatter(float(i[0]),float(i[1]), c="k")

	plt.savefig(folderName+"/maryland"+changer+".png")
	#plt.show()

# for i in range(0,1000):
# 	graphState(baseFolder+str(i))

changer = sys.argv[2]

graphState(baseFolder+"0")