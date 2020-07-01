#pragma once
#include <iostream>
using namespace std;


struct Position {
	int x;
	int y;
	Position(int _x, int _y) :x(_x), y(_y) {
	}
};

struct Color {
	int r;
	int g;
	int b;
	Color(int _r, int _g, int _b) :r(_r), g(_g), b(_b) {
	}
};

struct PixelNode {
public:
	Position*selfPosition;//this PixelNode's position : (x,y)
	Color* selfColour;//picture pixels' color
	Color* showColour;//edgepixels'color , samepixels' color  etc

	PixelNode* pn[8];

	bool isEdge;
	int edge;

	bool isSimilar;
	int similarGroup;

	int neighbour;
	int similarNeighbour;

	bool ifColored;
	bool ifFound;
	bool ifGood;


	PixelNode(int _x, int _y){

		selfPosition = new Position(_x,_y);
		selfColour = new Color(0,0,0);
		showColour = new Color(0, 0, 0);

		for (int i = 0; i < 8;i++) {
			pn[i] = nullptr;
		}

		isEdge =false;
		edge = -1;

		isSimilar = false;
		similarGroup = -1;

		neighbour = 0;
		similarNeighbour = 0;

		ifColored = false;
		ifFound = false;
		ifGood = false;
	}
	~PixelNode() {
		delete(selfPosition);
		delete(selfColour);
		delete(showColour);
	}
	//void SendInfo(Color* c) {
	//	this->selfColour = new Color(c->r, c->g, c->b);
	//	this->ifColored = true;
	//	for (int x = 0; x < 8; x++) {
	//		if (!pn[x]->ifColored) {
	//			SendInfo(c);
	//		}
	//	}
	//}
};


void FindNeighbor(PixelNode* p, int width, int height, vector<vector<PixelNode*>*>& picPixels);

void FindAllNeighbor(int width, int height, vector<vector<PixelNode*>*>& picPixels);

int checkGLFWwindow(GLFWwindow* window);

int checkGLADload();

void processInput(GLFWwindow* window);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void savePicPix(int width, int height, vector<vector<PixelNode*>*>& picPixels);

bool isSamePixel(PixelNode* A, PixelNode* B, int sameRange);

void showMousePn(int xpos, int ypos, vector<vector<PixelNode*>*>& picPixels);

void similarSituation(int xpos, int ypos, int sameRange, vector<vector<PixelNode*>*>& picPixels, vector<PixelNode*>& edgePixels, vector<PixelNode*>& similarPixels);

void NumSimi(vector<PixelNode*>& similarPixels);

void reNumSimi(vector<PixelNode*>& similarPixels, vector<vector<PixelNode*>*>& similarGroups);

void NumEdge(vector<PixelNode*>& edgePixels);

void reNumEdge(vector<PixelNode*>& edgePixels, vector<vector<PixelNode*>*>& edgeGroups);

void goodEdge(vector<vector<PixelNode*>*>& edgeGroups, vector<vector<PixelNode*>*>& goodGroups, int Limit);

void bestEdge(int xpos, int ypos, vector<vector<PixelNode*>*>& edgeGroups, vector<vector<PixelNode*>*>& picPixels);

void reSet(vector<vector<PixelNode*>*>& picPixels);

void sortArray(int* arr, const int length);