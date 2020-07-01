#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <vector>
#include "doSomePic.h"
using namespace std;


//check GLFW window is created or not
int checkGLFWwindow(GLFWwindow* window) {
	if (window == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
}

// glad: load all OpenGL function pointers
int checkGLADload() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

//find neighbours of a PixelNode
void FindNeighbor(PixelNode* p, int width, int height, vector<vector<PixelNode*>*>& picPixels) {
	if (p->selfPosition->x == 0) {
		p->pn[0] = nullptr;
		p->pn[3] = nullptr;
		p->pn[5] = nullptr;
		if (p->selfPosition->y == 0) {
			p->pn[1] = nullptr;
			p->pn[2] = nullptr;
			p->pn[4] = (*picPixels[p->selfPosition->x + 1])[p->selfPosition->y + 0];
			p->pn[6] = (*picPixels[p->selfPosition->x + 0])[p->selfPosition->y + 1];
			p->pn[7] = (*picPixels[p->selfPosition->x + 1])[p->selfPosition->y + 1];
			p->neighbour = 3;
		}
		else if (p->selfPosition->y == height-1) {
			p->pn[1] = (*picPixels[p->selfPosition->x + 0])[p->selfPosition->y - 1];
			p->pn[2] = (*picPixels[p->selfPosition->x + 1])[p->selfPosition->y - 1];
			p->pn[4] = (*picPixels[p->selfPosition->x + 1])[p->selfPosition->y + 0];
			p->pn[6] = nullptr;
			p->pn[7] = nullptr;
			p->neighbour = 3;
		}
		else {
			p->pn[1] = (*picPixels[p->selfPosition->x + 0])[p->selfPosition->y - 1];
			p->pn[2] = (*picPixels[p->selfPosition->x + 1])[p->selfPosition->y - 1];
			p->pn[4] = (*picPixels[p->selfPosition->x + 1])[p->selfPosition->y + 0];
			p->pn[6] = (*picPixels[p->selfPosition->x + 0])[p->selfPosition->y + 1];
			p->pn[7] = (*picPixels[p->selfPosition->x + 1])[p->selfPosition->y + 1];
			p->neighbour = 5;
		}
	}
	else if (p->selfPosition->x == width-1) {
		p->pn[2] = nullptr;
		p->pn[4] = nullptr;
		p->pn[7] = nullptr;
		if (p->selfPosition->y == 0) {
			p->pn[0] = nullptr;
			p->pn[1] = nullptr;
			p->pn[3] = (*picPixels[p->selfPosition->x - 1])[p->selfPosition->y];
			p->pn[5] = (*picPixels[p->selfPosition->x - 1])[p->selfPosition->y + 1];
			p->pn[6] = (*picPixels[p->selfPosition->x])[p->selfPosition->y + 1];
			p->neighbour = 3;
		}
		else if (p->selfPosition->y == height-1) {
			p->pn[0] = (*picPixels[p->selfPosition->x - 1])[p->selfPosition->y - 1];
			p->pn[1] = (*picPixels[p->selfPosition->x])[p->selfPosition->y - 1];
			p->pn[3] = (*picPixels[p->selfPosition->x - 1])[p->selfPosition->y];
			p->pn[5] = nullptr;
			p->pn[6] = nullptr;
			p->neighbour = 3;
		}
		else {
			p->pn[0] = (*picPixels[p->selfPosition->x - 1])[p->selfPosition->y - 1];
			p->pn[1] = (*picPixels[p->selfPosition->x])[p->selfPosition->y - 1];
			p->pn[3] = (*picPixels[p->selfPosition->x - 1])[p->selfPosition->y];
			p->pn[5] = (*picPixels[p->selfPosition->x - 1])[p->selfPosition->y + 1];
			p->pn[6] = (*picPixels[p->selfPosition->x])[p->selfPosition->y + 1];
			p->neighbour = 5;
		}
	}
	else {
		if (p->selfPosition->y == 0) {
			p->pn[0] = nullptr;
			p->pn[1] = nullptr;
			p->pn[2] = nullptr;
			p->pn[3] = (*picPixels[p->selfPosition->x - 1])[p->selfPosition->y];
			p->pn[4] = (*picPixels[p->selfPosition->x + 1])[p->selfPosition->y];
			p->pn[5] = (*picPixels[p->selfPosition->x - 1])[p->selfPosition->y + 1];
			p->pn[6] = (*picPixels[p->selfPosition->x])[p->selfPosition->y + 1];
			p->pn[7] = (*picPixels[p->selfPosition->x + 1])[p->selfPosition->y + 1];
			p->neighbour = 5;
		}
		else if (p->selfPosition->y == height-1) {
			p->pn[0] = (*picPixels[p->selfPosition->x - 1])[p->selfPosition->y - 1];
			p->pn[1] = (*picPixels[p->selfPosition->x])[p->selfPosition->y - 1];
			p->pn[2] = (*picPixels[p->selfPosition->x + 1])[p->selfPosition->y - 1];
			p->pn[3] = (*picPixels[p->selfPosition->x - 1])[p->selfPosition->y];
			p->pn[4] = (*picPixels[p->selfPosition->x + 1])[p->selfPosition->y];
			p->pn[5] = nullptr;
			p->pn[6] = nullptr;
			p->pn[7] = nullptr;
			p->neighbour = 5;
		}
		else {
			p->pn[0] = (*picPixels[p->selfPosition->x - 1])[p->selfPosition->y - 1];
			p->pn[1] = (*picPixels[p->selfPosition->x])[p->selfPosition->y - 1];
			p->pn[2] = (*picPixels[p->selfPosition->x + 1])[p->selfPosition->y - 1];
			p->pn[3] = (*picPixels[p->selfPosition->x - 1])[p->selfPosition->y];
			p->pn[4] = (*picPixels[p->selfPosition->x + 1])[p->selfPosition->y];
			p->pn[5] = (*picPixels[p->selfPosition->x - 1])[p->selfPosition->y + 1];
			p->pn[6] = (*picPixels[p->selfPosition->x])[p->selfPosition->y + 1];
			p->pn[7] = (*picPixels[p->selfPosition->x + 1])[p->selfPosition->y + 1];
			p->neighbour = 8;
		}
	}
	p->ifFound = true;
}

//find all PixelNodes' neighbour
void FindAllNeighbor(int width, int height, vector<vector<PixelNode*>*>& picPixels) {
	cout << "finding neighbours ... ..." << endl;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if ((*picPixels[i])[j]->ifFound == false) {
				FindNeighbor((*picPixels[i])[j], width, height, picPixels);
			}
		}
	}
	cout << "DONE !" << endl;
}

void savePicPix(int width, int height, vector<vector<PixelNode*>*>& picPixels) {
	cout << "Reading Picture ... ..." << endl;
	vector< unsigned char > color(1 * 1 * 3);
	for (int i = 0; i < width; i++) {
		vector<PixelNode*>* tempV=new vector<PixelNode*>();
		for (int j = 0; j < height; j++) {
			glReadPixels(i, height - j, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &color[0]);
			PixelNode* tempPN= new PixelNode(i,j);
			tempPN->selfColour->r  = color[0];
			tempPN->selfColour->g = color[1];
			tempPN->selfColour->b = color[2];			
			(*tempV).push_back(tempPN);
		}
		picPixels.push_back(tempV);
	}
	color.clear();
	cout << "DONE !" << endl;
}

//judge two pixels' color similar or not
bool isSamePixel(PixelNode* A, PixelNode* B, int sameRange) {
	if (A != NULL && B != NULL) {
		if ((-sameRange <= A->selfColour->r - B->selfColour->r) && (A->selfColour->r - B->selfColour->r <= sameRange) &&
			(-sameRange <= A->selfColour->g - B->selfColour->g) && (A->selfColour->g - B->selfColour->g <= sameRange) &&
			(-sameRange <= A->selfColour->b - B->selfColour->b) && (A->selfColour->b - B->selfColour->b <= sameRange)){
			return 1;
		}
		else {
			return 0;
		}
	}
}

//show all data if need
void showMousePn(int xpos, int ypos, vector<vector<PixelNode*>*>& picPixels) {
	cout << "mouse POS: " << "(" << xpos << "," << ypos << ")" << endl;
	cout << "color: " << "R:(" << (*picPixels[xpos])[ypos]->selfColour->r << ") G:(" << (*picPixels[xpos])[ypos]->selfColour->g << ") B:(" << (*picPixels[xpos])[ypos]->selfColour->b << ")" << endl;
	//show around pixels[8]
	/*for (int i = 0; i < 8; i++) {
		if ((*picPixels[xpos])[ypos]->pn[i] != NULL) {
			cout << "pn[" << i << "]:(" << (*picPixels[xpos])[ypos]->pn[i]->selfPosition->x << "," << (*picPixels[xpos])[ypos]->pn[i]->selfPosition->y << ")" << endl;
		}
		else {
			cout << "pn[" << i << "]:NULL" << endl;
		}
	}*/
		//cout << "neighbour Pixels:"<< (*picPixels[xpos])[ypos]->neighbour <<endl;
	//cout << "similar neighbour :" << (*picPixels[xpos])[ypos]->similarNeighbour << endl;
	//cout << "similar?:" << (*picPixels[xpos])[ypos]->isSimilar << endl;
	//cout << "isEdge?:" << (*picPixels[xpos])[ypos]->isEdge << endl;
	//cout << "whichEdge?:" << (*picPixels[xpos])[ypos]->edge << endl;
	//cout << "color to show:" <<"R:"<< (*picPixels[xpos])[ypos]->showColour->r << "G:" << (*picPixels[xpos])[ypos]->showColour->g << "B:" << (*picPixels[xpos])[ypos]->showColour->b << endl;
	//cout << endl;
}

//find similarPixels and edgePixels 
void similarSituation(int xpos, int ypos, int sameRange, vector<vector<PixelNode*>*>& picPixels, vector<PixelNode*>& edgePixels, vector<PixelNode*>& similarPixels) {
	cout<<"analyzing Pixels... ..."<<endl;
	for (int i = 0; i < picPixels.size(); i++) {
		for (int j = 0; j < (*picPixels[i]).size(); j++) {
			//judge all pixels if similar to mousePos pixel
			if (isSamePixel((*picPixels[xpos])[ypos], (*picPixels[i])[j], sameRange)) {
				(*picPixels[i])[j]->isSimilar = true;
				//store the similarPixels
				similarPixels.push_back((*picPixels[i])[j]);
				int similarNei = 0;
				for (int k = 0; k < 8; k++) {
					if ((*picPixels[i])[j]->pn[k] != NULL) {
						if (isSamePixel((*picPixels[xpos])[ypos], (*picPixels[i])[j]->pn[k], sameRange)) {
							similarNei += 1;
						}
					}
				}
				//judge all pixels if meet the requirements of Edge
				(*picPixels[i])[j]->similarNeighbour = similarNei;
				if (((*picPixels[i])[j]->neighbour  <  8 && (*picPixels[i])[j]->similarNeighbour <= (*picPixels[i])[j]->neighbour)||
					 ((*picPixels[i])[j]->neighbour == 8 && (*picPixels[i])[j]->similarNeighbour < (*picPixels[i])[j]->neighbour)){
					(*picPixels[i])[j]->isEdge = true;
					//store the edgePixels
					edgePixels.push_back((*picPixels[i])[j]);
				}
			}
		}
	}
	cout << "DONE !!" << endl;
	cout << "similar Pixel Number:" << similarPixels.size() << endl;
	cout << "edge Pixel Number:" << edgePixels.size() << endl;
}

void NumSimi(vector<PixelNode*>& similarPixels) {
	cout << "Num similar pixels... ..." << endl;
	int similarNum = 0;
	for (int i = 0; i < similarPixels.size(); i++) {
		////cout<<"Now["<<i<<"] "<<"of"<<" ["<<similarPixels.size()<<"]"<<endl;
		//color similarPixels
		similarPixels[i]->showColour->r = 0;
		similarPixels[i]->showColour->g = 0;
		similarPixels[i]->showColour->b = 255;
		//collect pixelgrid[9] similarGroup Number
		int Similar[9] = { -1,-1,-1,-1, -1,-1, -1,-1, -1};
		for (int k = 0; k < 8; k++) {
			if (similarPixels[i]->pn[k] != NULL && similarPixels[i]->pn[k]->isSimilar == true) {
				Similar[k] = similarPixels[i]->pn[k]->similarGroup;
			}
		}
		Similar[8] = similarPixels[i]->similarGroup;
		int witchS = -2;
		int* first = &Similar[0];
		sortArray(first, 9);
		for (int q = 8; q > -1; q--) {
			if (Similar[q] != -1) {
				witchS = q;
			}
		}
		//cout<<"similarGroups here: "<<endl;
		//for (int r = 0; r < 8; r++) {
		//	cout << Similar[r] <<",";
		//}
		if (witchS == -2) {
			for (int k = 0; k < 8; k++) {
				if (similarPixels[i]->pn[k] != NULL && similarPixels[i]->pn[k]->isSimilar == true) {
					similarPixels[i]->pn[k]->similarGroup = similarNum;
				}
			}
			similarPixels[i]->similarGroup = similarNum;
			similarNum += 1;
		}
		else if (witchS == 8) {
			for (int k = 0; k < 8; k++) {
				if (similarPixels[i]->pn[k] != NULL && similarPixels[i]->pn[k]->isSimilar == true) {
					similarPixels[i]->pn[k]->similarGroup = Similar[witchS];
				}
			}
			similarPixels[i]->similarGroup = Similar[witchS];
		}
		else if(0<=witchS&&witchS<8){
			for (int k = 0; k < 8; k++) {
				if (similarPixels[i]->pn[k] != NULL && similarPixels[i]->pn[k]->isSimilar == true) {
					similarPixels[i]->pn[k]->similarGroup = Similar[witchS];
				}
			}
			similarPixels[i]->similarGroup = Similar[witchS];
			for (int w = witchS + 1; w < 9; w++) {
				for (int q = 0; q < similarPixels.size(); q++) {
					if (similarPixels[q]->similarGroup == Similar[w]) {
						similarPixels[q]->similarGroup = Similar[witchS];
					}
				}
			}
		}
		else {
			cout << "something bad..." << endl;
		}
	}
	cout << "Num similar pixels DONE !!" << endl;
	cout<<"Initial similarGroups Num: "<<similarNum<<endl;
}

void reNumSimi(vector<PixelNode*>& similarPixels, vector<vector<PixelNode*>*>& similarGroups) {
	cout << "Renum similar pixels... ..." << endl;
	//collect similar Number
	vector<int>Similar;
	for (int i = 0; i < similarPixels.size(); i++) {
		if (Similar.size() == 0) {
			Similar.push_back(similarPixels[i]->similarGroup);
		}
		else {
			bool same = false;
			for (int j = 0; j < Similar.size(); j++) {
				if (similarPixels[i]->similarGroup == Similar[j]) {
					same = true;
				}
			}
			if (same == false) {
				Similar.push_back(similarPixels[i]->similarGroup);
			}
		}
	}
	//Sort similar numbers into serial Numbers
	for (int i = 0; i < similarPixels.size(); i++) {
		for (int j = 0; j < Similar.size(); j++) {
			if (similarPixels[i]->similarGroup == Similar[j]) {
				similarPixels[i]->similarGroup = j;
			}
		}
	}
	//also update the number vecter
	for (int i = 0; i < Similar.size(); i++) {
		Similar[i] = i;
	}
	//put similarGroups in vectors
	for (int i = 0; i < Similar.size(); i++) {
		vector<PixelNode*>* tempGroup = new vector<PixelNode*>;
		for (int j = 0; j < similarPixels.size(); j++) {
			if (similarPixels[j]->similarGroup == Similar[i]) {
				(*tempGroup).push_back(similarPixels[j]);
			}
		}
		cout<<"similarGroup["<<i<<"].size: "<<(*tempGroup).size();
		if ((*tempGroup).size() == 1) {
			cout << "singleSimi(" << (*tempGroup)[0]->selfPosition->x << "," << (*tempGroup)[0]->selfPosition->y << ")";
		}
		cout << endl;
		similarGroups.push_back(tempGroup);
	}
	cout << "Renum similar pixels DONE !!" << endl;
	cout << "Renumed similarGroup num:" << Similar.size() << endl;
	//for (int i = 0; i < edgeGroups.size(); i++) {
	//	cout << "EdgeGroup["<< i <<"]num:" << (*edgeGroups[i]).size() << endl;
	//}
}

void NumEdge(vector<PixelNode*>& edgePixels) {
	cout << "Num Edges... ..." << endl;
	int edgeNum = 0;
	for (int i = 0; i < edgePixels.size(); i++) {
		//color edgePixels
		edgePixels[i]->showColour->r = 255;
		edgePixels[i]->showColour->g = 0;
		edgePixels[i]->showColour->b = 0;
		int Edge[9] = {-1,-1,-1,-1, -1,-1, -1,-1,-1};
		for (int k = 0; k < 8; k++) {
			if (edgePixels[i]->pn[k] != NULL && edgePixels[i]->pn[k]->isEdge == true) {
				Edge[k] = edgePixels[i]->pn[k]->edge;
			}
		}
		Edge[8] = edgePixels[i]->edge;
		int witchG = -2;
		int* first = &Edge[0];
		sortArray(first, 8);
		for (int q = 8; q > -1; q--) {
			if (Edge[q] != -1) {
				witchG = q;
			}
		}
		//cout<<"edges here: "<<endl;
		//for (int r = 0; r < 8; r++) {
		//	cout << Edge[r] <<",";
		//}
		if (witchG == -2) {
			for (int k = 0; k < 8; k++) {
				if (edgePixels[i]->pn[k] != NULL && edgePixels[i]->pn[k]->isEdge == true) {
					edgePixels[i]->pn[k]->edge = edgeNum;
				}
			}
			edgePixels[i]->edge = edgeNum;
			edgeNum += 1;
		}
		else if (witchG == 8) {
			for (int k = 0; k < 8; k++) {
				if (edgePixels[i]->pn[k] != NULL && edgePixels[i]->pn[k]->isEdge == true) {
					edgePixels[i]->pn[k]->edge = Edge[witchG];
				}
			}
			edgePixels[i]->edge = Edge[witchG];
		}
		else if(0< witchG && witchG < 8){
			for (int k = 0; k < 8; k++) {
				if (edgePixels[i]->pn[k] != NULL && edgePixels[i]->pn[k]->isEdge == true) {
					edgePixels[i]->pn[k]->edge = Edge[witchG];
				}
			}
			edgePixels[i]->edge = Edge[witchG];
			for (int w = witchG+1; w < 8; w++) {
				for (int q = 0; q < edgePixels.size(); q++) {
					if (edgePixels[q]->edge == Edge[w]) {
						edgePixels[q]->edge = Edge[witchG];
					}
				}
			}
		}
		else {
			cout<<"something bad..."<<endl;
		}
	}
	cout << "Num Edges DONE !!" << endl;
	cout << "initial edgeGroups Num: " << edgeNum << endl;
}

void reNumEdge(vector<PixelNode*>& edgePixels, vector<vector<PixelNode*>*>& edgeGroups)   {
	cout << "ReNum Edges... ..." << endl;
	//collect edges Number
	vector<int>Edges;
	for (int i = 0; i < edgePixels.size(); i++) {
		if (Edges.size() == 0) {
			Edges.push_back(edgePixels[i]->edge);
		}
		else {
			bool same = false;
			for (int j = 0; j < Edges.size(); j++) {
				if (edgePixels[i]->edge == Edges[j]) {
					same = true;
				}
			}
			if (same == false) {
				Edges.push_back(edgePixels[i]->edge);
			}
		}
	}
	//Sort edge numbers into serial Numbers
	for (int i = 0; i < edgePixels.size(); i++) {
		for (int j = 0; j < Edges.size(); j++) {
			if (edgePixels[i]->edge == Edges[j]) {
				edgePixels[i]->edge = j;
			}
		}
	}	
	//also update number vector
	for (int i = 0; i < Edges.size(); i++) {
		Edges[i] = i;
	}
	//put edgeGroups in vectors
	for (int i = 0; i < Edges.size(); i++) {
		vector<PixelNode*>* tempGroup = new vector<PixelNode*>;
		for (int j = 0; j < edgePixels.size(); j++) {
			if (edgePixels[j]->edge == Edges[i]) {
				(*tempGroup).push_back(edgePixels[j]);
			}
		}
		edgeGroups.push_back(tempGroup);
		//cout << "edgeGroup[" << i << "].size: " << (*tempGroup).size();
		//if ((*tempGroup).size() == 1) {
		//	cout << "singleEdge("<<(*tempGroup)[0]->selfPosition->x<<","<<(*tempGroup)[0]->selfPosition->y << ")";
		//}
		//cout << endl;
	}
	cout << "Renum Edges DONE !!" << endl;
	cout << "ReNumed EdgeGroup num:" << Edges.size() << endl;
	//for (int i = 0; i < edgeGroups.size(); i++) {
	//	cout << "EdgeGroup["<< i <<"]num:" << (*edgeGroups[i]).size() << endl;
	//}
}

void goodEdge(vector<vector<PixelNode*>*>& edgeGroups, vector<vector<PixelNode*>*>& goodGroups, int Limit){
	int edgeNum=0;
	for (int i = 0; i < edgeGroups.size(); i++) {
		if ((*edgeGroups[i]).size() > Limit) {
			for (int j = 0; j < (*edgeGroups[i]).size(); j++) {
				(*edgeGroups[i])[j]->edge = edgeNum;
			}
			goodGroups.push_back(edgeGroups[i]);
			edgeNum += 1;
		} 
	}
	cout << "GoodGroup num:" << goodGroups.size() << endl;
	for (int i = 0; i < goodGroups.size(); i++) {
		cout << "GoodGroup[" << i << "]num:" << (*goodGroups[i]).size() << endl;
		cout << "GoodGroup[" << i << "]Edgenum:" << (*goodGroups[i])[0]->edge << endl;
		for (int j = 0; j < (*goodGroups[i]).size(); j++) {
			(*goodGroups[i])[j]->showColour->r = 0;
			(*goodGroups[i])[j]->showColour->g = 255;
			(*goodGroups[i])[j]->showColour->b = 0;
		}	
	}
}

void bestEdge(int xpos, int ypos, vector<vector<PixelNode*>*>& edgeGroups, vector<vector<PixelNode*>*>& picPixels) {
	vector<int> bestEdgeNum;
	vector<PixelNode*> xline, yline;
	for (int i = 0; i < picPixels.size(); i++) {
		if ((*picPixels[i])[ypos]->isEdge == true) {
			xline.push_back((*picPixels[i])[ypos]);
		}
	}
	for (int i = 0; i < (*picPixels[xpos]).size(); i++) {
		if ((*picPixels[xpos])[i]->isEdge == true) {
			yline.push_back((*picPixels[xpos])[i]);
		}
	}

	for (int i = 0; i < xline.size(); i++) {
		int temp = xline[i]->edge;
		for (int j = 0; j < yline.size(); j++) {
			if (yline[j]->edge == temp) {
				bestEdgeNum.push_back(temp);
			}
		}
	}

	vector<int> reallyBestEdgeNum;
	if (bestEdgeNum.size() > 0) {
		reallyBestEdgeNum.push_back(bestEdgeNum[0]);
		for (int i = 1; i < bestEdgeNum.size(); i++) {
			bool isExist = false;
			for (int j = 0; j < reallyBestEdgeNum.size(); j++) {
				if (bestEdgeNum[i] == bestEdgeNum[j]) {
					isExist = true;
				}
			}
			if (isExist == false) {
				reallyBestEdgeNum.push_back(bestEdgeNum[i]);
			}
		}
	}

	//cout << "xline: ";
	//for (int i = 0; i < xline.size(); i++) {
	//	cout<<xline[i]->edge<<":("<<xline[i]->selfPosition->x<<","<< xline[i]->selfPosition->y<<"), ";
	//}
	//cout << endl;
	//cout << "yline: ";
	//for (int i = 0; i < yline.size(); i++) {
	//	cout << yline[i]->edge << ":(" << yline[i]->selfPosition->x << "," << yline[i]->selfPosition->y << "), ";
	//}
	//cout<< endl;
	cout << "bestEdgeNum: ";
	for (int i = 0; i < reallyBestEdgeNum.size(); i++) {
		cout << reallyBestEdgeNum[i] << ",";
	}
	for (int i = 0; i < reallyBestEdgeNum.size(); i++) {
		for (int j = 0; j < (*edgeGroups[reallyBestEdgeNum[i]]).size(); j++) {
			(*edgeGroups[reallyBestEdgeNum[i]])[j]->ifGood = true;
			(*edgeGroups[reallyBestEdgeNum[i]])[j]->showColour->r = 0;
			(*edgeGroups[reallyBestEdgeNum[i]])[j]->showColour->g = 255;
			(*edgeGroups[reallyBestEdgeNum[i]])[j]->showColour->b = 0;
		}	
	}
	cout << endl;
}

void reSet(vector<vector<PixelNode*>*>& picPixels) {
	for (int i = 0; i < picPixels.size(); i++) {
		for (int j = 0; j < (*picPixels[i]).size(); j++) {
			(*picPixels[i])[j]->isSimilar = false;
			(*picPixels[i])[j]->similarGroup = -1;
			(*picPixels[i])[j]->similarNeighbour = 0;
			(*picPixels[i])[j]->isEdge = false;
			(*picPixels[i])[j]->edge = -1;
			(*picPixels[i])[j]->ifGood = false;

			(*picPixels[i])[j]->showColour->r = 0;
			(*picPixels[i])[j]->showColour->g = 0;
			(*picPixels[i])[j]->showColour->b = 0;			
		}
	}
}

//sort array from small to big
void sortArray(int* arr, const int length) {
	for (int i = 0; i < length; i++) {
		for (int j = i + 1; j < length; j++) {
			if (arr[i] > arr[j]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}