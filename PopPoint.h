using namespace std;
using std::string;

struct PopPoint{
	double lon,lat;
	int pop = 0;
	int id = -1;

	bool operator==(const PopPoint& b) const{
		if(b.lon==lon && b.lat==lat && b.pop==pop && b.id==id){
			return true;
		}
		else{
			return false;
		}
	}
};

bool moreLat(PopPoint a, PopPoint b){
	return a.lat>b.lat;
}
bool moreLon(PopPoint a, PopPoint b){
	return a.lon>b.lon;
}

int popOfGroup(vector<PopPoint> group){
	int totalPop = 0;
	for(PopPoint& i : group){
		totalPop+=i.pop;
	}
	return totalPop;
}

bool largerGroup(vector<PopPoint> groupA, vector<PopPoint> groupB){
	return popOfGroup(groupA) > popOfGroup(groupB);
}

double M_PI = 4*atan(1);
double deg2rad(double deg) {
	return (deg * M_PI / 180);
}

double rad2deg(double rad) {
	return (rad * 180 / M_PI);
}

//Returns distance in Kilometers
double distSquared(PopPoint a, PopPoint b) {
	double lon2d = pow(b.lon-a.lon,2.0);
	double lat2d = pow(b.lat-a.lat,2.0);
	return (lon2d+lat2d)/1000;

	//return pow(a.lat-b.lat,2) + (cos(a.lat*M_PI/180.0)*cos(b.lat*M_PI/180)*pow(a.lon-b.lon,2));

	/*double lat1d = a.lat;
	double lon1d = a.lon;
	double lat2d = b.lat;
	double lon2d = b.lon;
	double earthRadiusKm = 6371.0;
	double lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = deg2rad(lat1d);
	lon1r = deg2rad(lon1d);
	lat2r = deg2rad(lat2d);
	lon2r = deg2rad(lon2d);
	u = sin((lat2r - lat1r)/2);
	v = sin((lon2r - lon1r)/2);
	return asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));*/
}

/*vector<PopPoint> * */

/*string getCommand(PopPoint a, PopPoint b){
	string strA = to_string(a.lon)+','+to_string(a.lat);
	string strB = to_string(b.lon)+','+to_string(b.lat);
	return strA+' '+strB+' '+to_string(a.id)+' '+to_string(b.id);
}

int getDist(PopPoint a, PopPoint b){
	ifstream collDists("allDists.dists");
	int finalDist = -1;
	if(collDists.is_open()){
		string line;
		while(getline(collDists,line)){
			string tempNum = "";
			int filePieces[3];
			int numCommas = 0;
			for(int i = 0; i<line.length(); i++){
				if(line[i] != ','){
					tempNum+=line[i];
				}
				else{
					filePieces[numCommas] = stoi(tempNum);
					tempNum = "";
					numCommas++;
				}
			}
			//cout<<a.id<<' '<<b.id<<endl;
			if((filePieces[0] == a.id && filePieces[1] == b.id) || (filePieces[0] == b.id && filePieces[1] == a.id)){
				finalDist = filePieces[2];
				break;
			}
		}
	}
	if(finalDist == -1){
		string distLine;
		system(("python3 distFind.py "+getCommand(a,b)).c_str());
		ifstream tempDist("tempDist.dist");
		getline(tempDist,distLine);
		finalDist = stoi(distLine);
		tempDist.close();
	}
	return finalDist;
}*/


/*int sumOdaSquares(vector<PopPoint> allPoints, PopPoint cents[]){
	int dists[numDists];
	vector<PopPoint> groups[2];

	for(PopPoint& i : allPoints){
		int distA = getDist(i, cents[0]);
		int distB = getDist(i, cents[1]);
		if(distA < distB){
			groups[0].push_back(i);
		}
		else if(distA == distB){
			if(groups[0].size() < groups[1].size()){
				groups[0].push_back(i);
			}
			else{
				groups[1].push_back(i);
			}
		}
		else{
			groups[1].push_back(i);
		}
	}

	for(int i = 0; i<numDists; i++){
		int tempDist = 0;
		for(PopPoint& j : groups[i]){
			tempDist+=getDist(j,cents[i]);
		}
		dists[i] = tempDist*tempDist;
		tempDist = 0;
	}

	int totalDist = 0;
	for(int& i : dists){
		totalDist+=i;
	}
	return abs(totalDist);
}*/

/*PopPoint * getNewCents(vector<PopPoint> allPoints, PopPoint cents[]){
	vector<PopPoint> groups[2];

	for(PopPoint& i : allPoints){
		int distA = getDist(i, cents[0]);
		int distB = getDist(i, cents[1]);
		if(distA < distB){
			groups[0].push_back(i);
		}
		else if(distA == distB){
			if(groups[0].size() < groups[1].size()){
				groups[0].push_back(i);
			}
			else{
				groups[1].push_back(i);
			}
		}
		else{
			groups[1].push_back(i);
		}
	}

	PopPoint* testCents = new PopPoint[2];
	for(int i = 0; i<numDists; i++){
		PopPoint least = groups[i][0];
		for(PopPoint& j : groups[i]){
			if(getDist(j,cents[i]) < getDist(least,cents[i]) && j.id != cents[i].id){
				least = j;
			}
		}
		testCents[i] = least;
	}
	return testCents;
}*/