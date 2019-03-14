class lloydBalanced{
public:
	lloydBalanced(vector<PopPoint> allPts){
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
		double oldPopBal = 0;
		for(int i = 0; i<100; i++){
			changeCent();
			assignNearest();
			double newDisp = calcDisp();
			double newPopBal = calcPopBalance();
			cout<<oldDisp<<endl;
			cout<<oldPopBal<<endl;
			if(i > 1){
				if((oldDisp)<=newDisp){
					break;
				}
			}
			//cout<<newDisp<<endl;
			ofs<<setprecision(16)<<i<<","<<newDisp<<endl;
			oldDisp = newDisp;
			oldPopBal = newPopBal;
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
		int totalPopOState = 0;
		double avgPopOState;
		for(vector<PopPoint>& i : pointGroups){
			totalPopOState+=popOfGroup(i);
		}
		avgPopOState = (double)totalPopOState/(double)numDists;
		int medPopOState = 99999999;
		for(vector<PopPoint>& i: pointGroups){
			if(abs(popOfGroup(i)-avgPopOState) < medPopOState){
				medPopOState = popOfGroup(i);
			}
		}
		for(vector<PopPoint>& i : pointGroups){
			double multiplier = 0;
			if(popOfGroup(i) > medPopOState){
				multiplier = 1.0;
			}
			else{
				multiplier = 1.0;//0.25;
			}
			double newLat = 0;
			double newLon = 0;

			int distPop = 0;
			for(PopPoint& j : i){
				distPop+=j.pop;
			}
			for(PopPoint& j : i){
				newLat+=(multiplier*(j.lat*(double)j.pop)/(double)distPop);
				newLon+=(multiplier*(j.lon*(double)j.pop)/(double)distPop);
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

	void balancePopsMove(int largestInd, int smolInd){
		PopPoint oldBig = centers[largestInd];
		PopPoint oldSmall = centers[smolInd];
		int oldBigPop = popOfGroup(pointGroups[largestInd]);
		int oldSmallPop = popOfGroup(pointGroups[smolInd]);

		bool worked = false;
		int iterer = 0;
		double mag = 0.0001;
		while(!worked && iterer<360){
			centers[largestInd] = oldBig;
			centers[smolInd] = oldSmall;
			double randAng = (double)iterer;
			centers[largestInd].lon+=(sin(randAng*M_PI/180)*mag);
			centers[largestInd].lat+=(cos(randAng*M_PI/180)*mag);
			assignNearest();
			// finish refining this bitch
			if(false){
				worked = true;
				cout<<"holy fuck"<<endl;
				break;
			}
			else{
				centers[largestInd] = oldBig;
				centers[smolInd] = oldSmall;
			}
			iterer+=8;
		}
		/*iterer = 0;
		while(!worked && iterer<45){
			centers[largestInd] = oldBig;
			centers[smolInd] = oldSmall;
			srand(time(NULL)+iterer);
			double randAng = rand()%360;
			centers[smolInd].lon+=(sin(randAng*M_PI/180)*mag);
			centers[smolInd].lat+=(cos(randAng*M_PI/180)*mag);
			assignNearest();
			if(popOfGroup(pointGroups[largestInd])<oldBigPop && popOfGroup(pointGroups[smolInd])>oldSmallPop){
				worked = true;
				cout<<"holy fuck"<<endl;
			}
			iterer++;
		}*/
	}

	void balanceTwo(int largestInd, int smolInd){

		double smolDist = 1;
		int closeInd;
		vector<double> bannedSlopes = {};
		for(int numTimes = 0; numTimes<30; numTimes++){
			double finalSlope;
			for(int i = 0; i<pointGroups[largestInd].size(); i++){
				if(distSquared(pointGroups[largestInd][i], centers[smolInd])<smolDist){
					PopPoint big = pointGroups[largestInd][i];
					PopPoint small = centers[smolInd];
					double slope = (small.lon-big.lon)/(small.lat-big.lat);
					finalSlope = slope;
					bool works = true;
					for(double& j : bannedSlopes){
						if(abs(j-slope) < 1){
							works = false;
							break;
						}
					}
					if(works){
						closeInd = i;
						smolDist = distSquared(pointGroups[largestInd][i], centers[smolInd]);
						finalSlope = slope;
					}
				}
			}
			bannedSlopes.push_back(finalSlope);
			pointGroups[smolInd].push_back(pointGroups[largestInd][closeInd]);
			pointGroups[largestInd].erase(pointGroups[largestInd].begin()+closeInd);
		}
	}

	void balancePops(){
		/*for(int i = 0; i<numDists; i++){
			double otherDist = 1000;
			int otherInd = 0;
			for(int j = 0; j<numDists; j++){
				if(distSquared(centers[i],centers[j])<otherDist && i!=j){
					otherDist = distSquared(centers[i],centers[j]);
					otherInd = j;
				}
			}
			if(largerGroup(pointGroups[i],pointGroups[otherInd])){
				balancePopsMove(i,otherInd);
			}
			else{
				balancePopsMove(otherInd,i);
			}
		}*/
		int largestPop = 0;
		int bigDistInd;
		for(int i = 0; i<numDists; i++){
			if(popOfGroup(pointGroups[i]) > largestPop){
				largestPop = popOfGroup(pointGroups[i]);
				bigDistInd = i;
			}
		}
		int smallestPop = largestPop;
		int smallDistInd;
		for(int i = 0; i<numDists; i++){
			if(popOfGroup(pointGroups[i]) < smallestPop){
				smallestPop = popOfGroup(pointGroups[i]);
				smallDistInd = i;
			}
		}
		balancePopsMove(bigDistInd,smallDistInd);
	}
};