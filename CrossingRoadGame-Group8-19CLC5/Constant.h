#ifndef _CONSTANT_
#define _CONSTANT_

#pragma comment(lib, "winmm.lib")
#pragma disable(warning:4996)

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
#define	minDifficulty 0
#define maxDifficulty 10
#define distanceObject 10
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
#define gameOverX 30
#define gameOverY 8	   
#define saveX 95
#define saveY 11
#define loadX 50
#define loadY 14
#define settingX 50
#define settingY 8

#define delayTimes 100

#define minCol 2
#define maxCol 82

#define scoreBoardPath "data\\scoreBoard"	 
#define saveFolder "data\\"

#define baseScore 10
#define baseNRow 1
#define deltaScore 3
#define deltaNRow 2

#define constantNull 0
#define constantBat 1
#define constantDuck 2
#define constantTruck 3
#define constantBicycle 4

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