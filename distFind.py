import requests
import sys
import json

apikey = "AIzaSyAPl9tDa5w613RtNTkIczC95HOAhnjoyjo"

def sendReq(org, dest):
	payload = {"units":"metric", "origins":org, "destinations":dest, "key":apikey}
	r = requests.get("https://maps.googleapis.com/maps/api/distancematrix/json", params=payload)
	res = json.loads(r.text)
	fullDist = res["rows"][0]["elements"][0]["distance"]["value"]
	f = open("allDists.dists", "a+")
	f.write(sys.argv[3]+","+sys.argv[4]+","+str(fullDist)+",\n")
	f.close()

	f2 = open("tempDist.dist", "w")
	f2.write(str(fullDist))
	f2.close()

sendReq(sys.argv[1], sys.argv[2])