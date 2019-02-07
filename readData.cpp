#include <iostream>
#include <fstream>
#include <vector>
#include "sampler.h"

using namespace std;

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

	PopPoint cent0;		//Should be 25
	PopPoint cent1;		//Should be 175
	for(PopPoint& i : allPoints){
		if(i.id == 108){
			cent0 = i;
		}
		if(i.id == 21){
			cent1 = i;
		}
	}
	vector<PopPoint> group0;
	vector<PopPoint> group1;
	int maybe = 0;
	for(PopPoint& i : allPoints){
		if(getDist(i, cent0) == getDist(i, cent1)){
			if(maybe = 0){
				group0.push_back(i);
				maybe = 1;
			}
			else{
				group1.push_back(i);
				maybe = 0;
			}
		}
		else if(getDist(i, cent0) < getDist(i, cent1)){
			group0.push_back(i);
		}
		else{
			group1.push_back(i);
		}
	}

	ofstream g0("group0.csv");
	g0<<"Latitude,Longitude"<<endl;
	g0<<cent0.lat<<','<<cent0.lon<<endl;
	for(PopPoint& i : group0){
		g0<<i.lat<<','<<i.lon<<endl;
	}
	g0.close();

	ofstream g1("group1.csv");
	g1<<"Latitude,Longitude"<<endl;
	g1<<cent1.lat<<','<<cent1.lon<<endl;
	for(PopPoint& i : group1){
		g1<<i.lat<<','<<i.lon<<endl;
	}
	g1.close();
	
}