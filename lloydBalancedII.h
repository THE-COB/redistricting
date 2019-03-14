class lloydBalancedII{
public:
	lloydBalancedII(vector<PopPoint> allPts){
		allPoints = allPts;
		randSet();
	}

	void printPoint(PopPoint a){
		cout<<a.lat<<" "<<a.lon<<" "<<a.pop<<" "<<a.id<<" "<<endl;
	}

	void runAlgo(){	
		assignNearest();
		//cout<<calcDisp()<<endl;

		int ogTime = time(NULL);
		
		string dispFile = folderName+"/dispersion.csv";
		ofstream ofs(dispFile.c_str());
		ofs<<"Iteration,Dispersion"<<endl;
		double oldDisp = 0;
		for(int i = 0; i<100; i++){
			changeCent();
			assignNearest();
			cout<<oldDisp<<endl;
			cout<<calcPopBalance()<<endl;
			double newDisp = calcDisp();
			if(i != 0){
				if(oldDisp<=newDisp){
					break;
				}
			}
			//cout<<newDisp<<endl;
			ofs<<setprecision(16)<<i<<","<<newDisp<<endl;
			oldDisp = newDisp;
		}
		//cout<<time(NULL)-ogTime<<endl;
		ofs.close();
		ofstream cents[numDists];
		int count = 0;
		ofstream mCent;
		for(vector<PopPoint>& i : pointGroups){
			string fname = folderName+"/cent"+to_string(count)+".csv";
			mCent.open(fname.c_str());
			for(PopPoint& j : i){
				mCent<<setprecision(12)<<j.lat<<","<<setprecision(12)<<j.lon<<endl;
			}
			count++;
			mCent.close();
		}
		//cout<<endl;

		string popFname = folderName+"/pops.dat";
		ofstream popFile(popFname.c_str());
		for(vector<PopPoint>& i : pointGroups){
			int tempPop = 0;
			for(PopPoint& j : i){
				tempPop+=j.pop;
			}
		//	cout<<tempPop<<endl;
			popFile<<tempPop<<endl;
		}
		popFile.close();

		//cout<<endl;
		string centsFname = folderName+"/centCoords.csv";
		ofstream centsFile(centsFname.c_str());
		for(PopPoint& i : centers){
			centsFile<<setprecision(12)<<i.lat<<","<<setprecision(12)<<i.lon<<endl;
		//	cout<<setprecision(12)<<i.lat<<","<<setprecision(12)<<i.lon<<endl;
		}
		centsFile.close();
	}

	void realCents(){
		string fname = "statefiles/"+stateName+".centers";
		ifstream centFile(fname);
		vector<PopPoint> realCenteroos;
		string line;
		if(centFile.is_open()){
			while(getline(centFile, line)){
				string xVal = "";
				string yVal = "";
				int i = 0;
				for(i = 0; i<line.length(); i++){
					if(line[i] != ','){
						yVal+=line[i];
					}
					else{
						break;
					}
				}
				for(int j = i+1; j<line.length(); j++){
					if(line[j] != ','){
						xVal+=line[j];
					}
				}
				PopPoint newCent;
				newCent.lon = stod(yVal);
				newCent.lat = stod(xVal);
				printPoint(newCent);
				realCenteroos.push_back(newCent);
			}
		}
		for(int i = 0; i<numDists; i++){
			centers[i] = realCenteroos[i];
		}
		assignNearest();
		cout<<calcDisp()<<endl;
	}

private:
	vector<PopPoint> allPoints;
	//16 Districts in ohio
	//int numDists = 16;
	PopPoint centers[numDists];
	
	vector<PopPoint> pointGroups[numDists];

	void randSet(){
		for(int i = 0; i<numDists; i++){
			srand(time(NULL)+i);
			int pointNum = rand()%allPoints.size();
			centers[i] = allPoints[pointNum];
		}
	}

	/*void assignNearest(){
		for(int i = 0; i<numDists; i++){
			pointGroups[i].erase(pointGroups[i].begin(), pointGroups[i].end());
		}
		for(PopPoint& i : allPoints){
			double tempDist = distSquared(i,centers[0]);
			int tempPoint = 0;
			for(int j = 0; j<numDists; j++){
				if(distSquared(i,centers[j]) < tempDist){
					tempDist = distSquared(i,centers[j]);
					tempPoint = j;
				}
			}
			pointGroups[tempPoint].push_back(i);
		}
	}*/

	void assignNearest(){
		int count = 0;
		int totalPopOState = 0;
		double avgPopOState;
		for(vector<PopPoint>& i : pointGroups){
			totalPopOState+=popOfGroup(i);
		}
		avgPopOState = (double)totalPopOState/(double)numDists;

		for(int i = 0; i<numDists; i++){
			pointGroups[i].erase(pointGroups[i].begin(), pointGroups[i].end());
		}
		for(PopPoint& i : allPoints){
			double tempDist = distSquared(i,centers[0]);
			int tempPoint = 0;
			
		}
	}

	void changeCent(){
		int count = 0;
		int totalPopOState = 0;
		double avgPopOState;
		for(vector<PopPoint>& i : pointGroups){
			totalPopOState+=popOfGroup(i);
		}
		avgPopOState = (double)totalPopOState/(double)numDists;
		
		for(vector<PopPoint>& i : pointGroups){
			double newLat = 0;
			double newLon = 0;

			int distPop = 0;
			for(PopPoint& j : i){
				distPop+=j.pop;
			}
			for(PopPoint& j : i){
				newLat+=((j.lat*(double)j.pop)/(double)distPop);
				newLon+=((j.lon*(double)j.pop)/(double)distPop);
			}

			centers[count] = PopPoint();
			centers[count].lat = newLat;
			centers[count].lon = newLon;
			count++;
		}
	}

	double calcDisp(){
		double disp = 0;
		int count = 0;
		for(vector<PopPoint>& i : pointGroups){
			for(PopPoint& j : i){
				disp+=distSquared(j,centers[count])*j.pop;
			}
			count++;
		}
		return disp;
	}

	int calcPopBalance(){
		int largestPop = 0;
		int smallestPop = 99999999;
		for(vector<PopPoint>& i : pointGroups){
			if(popOfGroup(i) > largestPop){
				largestPop = popOfGroup(i);
			}
			if(popOfGroup(i) < smallestPop){
				smallestPop = popOfGroup(i);
			}
		}
		return largestPop-smallestPop;
	}
};