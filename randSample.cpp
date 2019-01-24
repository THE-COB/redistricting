#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <math.h>

#include "sampler.h"
using namespace std;
using std::string;

int main(){
	string fName = "rhodeIsland.state";
	ifstream stateFile(fName);
	vector<PopPoint> allPoints;

	string line;
	int ids = 0;
	if(stateFile.is_open()){
		while(getline(stateFile,line)){
			string tempNum = "";
			int parNum = 0;
			double nums[3];
			for(int i = 0; i<line.length(); i++){
				if(line[i] != ','){
					tempNum+=line[i];
				}
				else{
					nums[parNum] = stod(tempNum);
					parNum++;
					tempNum = "";
				}
			}
			PopPoint newPt;
			newPt.lon=nums[0];
			newPt.lat=nums[1];
			newPt.pop=nums[2];
			newPt.id = ids;
			ids++;
			allPoints.push_back(newPt);
		}
		stateFile.close();
	}

	vector<PopPoint> allPointsLatSort = allPoints;
	vector<PopPoint> allPointsLonSort = allPoints;
	sort(allPointsLatSort.begin(), allPointsLatSort.end(), moreLat);
	sort(allPointsLonSort.begin(), allPointsLonSort.end(), moreLon);

	PopPoint randCents[numDists];
	for(int i = 0; i<numDists; i++){
		srand(time(NULL)+i);
		int pointNum = rand()%allPoints.size();
		randCents[i] = allPoints[pointNum];
	}

	//PopPoint* oldCents = randCents;
	PopPoint oldCents[2];
	for(PopPoint& i : allPoints){
		if(i.id == 107) oldCents[0] = i;
		if(i.id == 178) oldCents[1] = i;
	}

	cout<<sumOdaSquares(allPoints, oldCents)<<endl;
	
	PopPoint* newCents = getNewCents(allPoints, oldCents);
	
	cout<<sumOdaSquares(allPoints, newCents)<<endl;
	return 0;
}