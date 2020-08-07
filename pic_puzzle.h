#ifndef _PIC_PUZZLE_H                                                                                                                                                    
#define _PIC_PUZZLE_H


#define EXTERNC extern "C"




#define EXTERNFCT EXTERNC __declspec(dllexport)



#include<iostream>
#include<vector>
#include <bits/stdc++.h>
#include<math.h>
#include<cstdio> 
#include<string>
#include<set>
#include<algorithm>
#include<memory.h>

using namespace std;

#define MAX_WIDTH 100
#define MAX_HEIGHT 100
#define MIN_WIDTH 1
#define MIN_HEIGHT 1

#define BIG_NUM 127


struct Vertex
{
  int * stat; //store the order
  int * stat2; // store the order to compute index
  int s_n; // pos of space
  int s_n_w; // pos w
  int s_n_h; //pos h
  int * adj; //store up/down/left/right stat index
  int father;
  int f;
  int h;
  int g;
  int i; // index
};

typedef vector<Vertex> VertexVec;

typedef struct{
	VertexVec vexs; //vertex vector
  int start;
	int goal; //vertex number of the Graph
  int w;
  int h;
  int num;
  int target;
  int source;
} MGraph;

typedef struct 
{
  int * data;
  int num;
} compute_result;

MGraph mg;


EXTERNFCT void release_c_result(compute_result c);

EXTERNFCT compute_result compute_steps(int w, int h, int * input);

#endif