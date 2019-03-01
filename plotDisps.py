import matplotlib.pyplot as plt
import csv

baseFolder = "DATA/maryland/"#+sys.argv[1]+"_"+sys.argv[2]

disps = [["Iteration","DispInit","DispFinal"]]

def plotDisp(folder, trialNum):
	reader = csv.reader(open(folder+"/dispersion.csv"))
	trialDisps = list(reader)
	disps.append([str(trialNum),str(trialDisps[1][1]),str(trialDisps[-1][1])])

for i in range(0,1000):
	plotDisp(baseFolder+"maryland2-20_"+str(i),i)

with open(baseFolder+"allDisps.csv", "w", newline="") as csvfile:
	writer = csv.writer(csvfile, delimiter=",")
	for i in disps:
		writer.writerow(i)