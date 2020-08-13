#ifndef _CONSTANT_
#define _CONSTANT_

#define APP_NAME L"CROSSING ROAD"	 

#define colorGreen 2
#define colorBlue 3
#define colorRed 4
#define colorPurple 5
#define colorOrange 6
#define colorWhite 7
#define colorMint 11

#define maxMenuChoice 5
#define maxNameLength 10
#define nLanes 4

#define logoX 5
#define logoY 1
#define menuX 50
#define menuY 8
#define newNameX 50
#define newNameY 8
#define gameWindowX	120
#define gameWindowY 25
#define playerNameX 95
#define playerNameY 3
#define levelX 95
#define levelY 5
#define scoreX 95
#define scoreY 7
#define nObjectX 95
#define nObjectY 9
#define infoX 1
#define infoY 10

#define delayTimes 200

#define minCol 2
#define maxCol 82

enum MOVE { UP, DOWN, LEFT, RIGHT };

#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <conio.h>
#include <stdio.h> 
#include <ctime>
#include <random>
#include <stdlib.h>
using namespace std;

#endif