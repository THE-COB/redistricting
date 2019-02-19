# Redistricting Program

This program is made to redistrict a state

## Setup

Download a shapefile (from the [US Census](https://www.census.gov/geo/maps-data/data/tiger-data.html)) of the state you wanna redistrict and change the file/folder names in /readBlocks.py

Once changed, run
```bash
python3 readBlocks.py
```

## Usage

In redistrict.cpp, change

```cpp
string stateName = "ohio";
string date = "2-19";
string trial = "1";
string folderName = "DATA/"+stateName+date+"_"+trial;
```
accordingly

Then, simply
```bash
make
./redistrict
```
To plot the points and actually visualize the redistricted state, go into graphState.py, and change
```python
with open("DATA/ohio2-19_1/cent"+str(i)+".csv") as f:
```
accordingly

Once changed, run
```bash
python3 graphState.py
```

Both the image and the dispersion files will be in /DATA/\[your folder name\]/
