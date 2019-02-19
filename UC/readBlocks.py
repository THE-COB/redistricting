import shapefile
from shapely.geometry import shape

#Rhode Island census block from census
blockShp = open("tabblock2010_44_pophu/tabblock2010_44_pophu.shp", "rb") 
blockDbf = open("tabblock2010_44_pophu/tabblock2010_44_pophu.dbf", "rb") 

blockSf = shapefile.Reader(shp=blockShp, dbf=blockDbf)
shapeRecsBlock = blockSf.iterShapeRecords()

f = open("rhodeIsland0.state", "w")
maryStr = ""
for i in shapeRecsBlock:
	pop = i.record[7]
	if(pop>=0):
		cent = shape(i.shape).centroid
		maryStr+=str(cent.y)+","+str(cent.x)+","+str(pop)+",\n"
f.write(maryStr)
f.close()
