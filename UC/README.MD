# Redistricting Program

This program is made to redistrict a state

## Setup

Download a shapefile (from the [US Census](https://www.census.gov/geo/maps-data/data/tiger-data.html)) of the state you wanna redistrict and change the file/folder names in /readBlocks.py

## Usage

In redistrict.cpp, change

```cpp
string stateName = "ohio";
string date = "2-19";
string trial = "1";
string folderName = "DATA/"+stateName+date+"_"+trial;
```
Accordingly
