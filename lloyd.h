class lloyd{
public:
	lloyd(vector<PopPoint> allPts){
		allPoints = allPts;
		randSet();
	}

	void printPoint(PopPoint a){
		cout<<a.lat<<" "<<a.lon<<" "<<a.pop<<" "<<a.id<<" "<<endl;
	}

	void runAlgo(){	
		assignNearest();
		cout<<calcDisp()<<endl;

		int ogTime = time(NULL);
		
		string dispFile = folderName+"/dispersion.csv";
		ofstream ofs(dispFile.c_str());
		ofs<<"Iteration,Dispersion"<<endl;
		double oldDisp = 0;
		for(int i = 0; i<100; i++){
			changeCent();
			assignNearest();
			double newDisp = calcDisp();
			if(i != 0){
				if(oldDisp<=newDisp){
					break;
				}
			}
			cout<<newDisp<<endl;
			ofs<<setprecision(16)<<i<<","<<newDisp<<endl;
			oldDisp = newDisp;
		}
		cout<<time(NULL)-ogTime<<endl;
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
		cout<<endl;
		for(vector<PopPoint>& i : pointGroups){
			int tempPop = 0;
			for(PopPoint& j : i){
				tempPop+=j.pop;
			}
			cout<<tempPop<<endl;
		}
	}

private:
	vector<PopPoint> allPoints;
	//16 Districts in ohio
	int numDists = 16;
	PopPoint centers[16];
	
	vector<PopPoint> pointGroups[16];

	void randSet(){
		for(int i = 0; i<numDists; i++){
			srand(time(NULL)+i);
			int pointNum = rand()%allPoints.size();
			centers[i] = allPoints[pointNum];
		}
	}

	void assignNearest(){
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
	}

	void changeCent(){
		int count = 0;
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

};