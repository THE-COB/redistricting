#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <math.h>

using namespace std;
using std::string;

string stateName = "ohio";
string date = "2-19";
string trial = "1";
string folderName = "DATA/"+stateName+date+"_"+trial;

#include "PopPoint.h"
#include "lloyd.h"

int main(){
	string fName = "statefiles/"+stateName+".state";
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

/*	vector<PopPoint> allPointsLatSort = allPoints;
	vector<PopPoint> allPointsLonSort = allPoints;
	sort(allPointsLatSort.begin(), allPointsLatSort.end(), moreLat);
	sort(allPointsLonSort.begin(), allPointsLonSort.end(), moreLon);*/

	lloyd newLloyd(allPoints);
	newLloyd.runAlgo();
/*
//	PopPoint* oldCents = randCents;
	PopPoint testCase[numDists] = {allPoints[178], allPoints[107]};
	PopPoint* oldCents = testCase;

	PopPoint* newCentsPt;
	vector<PopPoint> allPtsUsed = allPoints;
	int oldDisp = -1; 
	int newDisp = -1;
	bool amIDone = false;
	int numTries = 0;
	vector<vector<PopPoint>> posCents(6);
	while(!amIDone){
		oldDisp = sumOdaSquares(allPoints, oldCents);
		newCentsPt = getNewCents(allPtsUsed, oldCents);
		PopPoint newCents[numDists];
		for(int i = 0; i<numDists; i++){
			newCents[i] = *(newCentsPt+i);
		}
		newDisp = sumOdaSquares(allPoints, newCents);
		if(newDisp<oldDisp && numTries<=6){
			vector<PopPoint> centGroup(newCents, newCents+(sizeof(newCents)/sizeof(newCents[0])));
			posCents[numTries] = centGroup;
			vector<PopPoint> newPtsUsed;
			for(PopPoint& i : allPtsUsed){
				bool isInGroup = false;
				for(PopPoint& j : centGroup){
					if(j == i){
						isInGroup = true;
					}
				}
				if(!isInGroup){
					newPtsUsed.push_back(i);
				}
			}
			allPtsUsed = newPtsUsed;
			numTries++;
		}
		else if(numTries>6){
			bool anyBois = false;
			for(vector<PopPoint>& i : posCents){
				if(!(i[0] == PopPoint()) && !(i[1] == PopPoint())){
					anyBois = true;
					break;
				}
			}
			if(!anyBois){
				amIDone = true;
				break;
			}
			else{
				numTries = 0;
	//			PopPoint base();
				PopPoint potPopCent[numDists];
				copy(posCents[0].begin(),posCents[0].end(), potPopCent);
				PopPoint trueCent[numDists] = potPopCent;
				int leastDist = sumOdaSquares(allPoints, trueCent);
				for(int i = 0; i<posCents.size(); i++){
					copy(posCents[i].begin(), posCents[i].end(), potPopCent);
					if(sumOdaSquares(allPoints,potPopCent) < sumOdaSquares(allPoints,trueCent)){
						leastDist = sumOdaSquares(allPoints,potPopCent);
						copy(potPopCent, potPopCent+numDists, trueCent);
					}
				}
				ofstream steps("rhodeIslandSteps.state", ofstream::out);
				for(PopPoint& i : trueCent){
					steps<<i.lon<<','<<i.lat<<','<<i.pop<<','<<endl;
					cout<<i.lon<<','<<i.lat<<','<<i.pop<<','<<endl;
				}
				steps<<endl;
				cout<<endl;
				steps.close();
			}
		}

	}*/

	return 0;
}