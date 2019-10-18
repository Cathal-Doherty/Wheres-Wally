//Cathal Doherty DOH16605113 O.O.P Assignment 1 : CMP2090M (Where's Wally?). 100%

//To start this program, you need to include all the libraries and header files that are relevant to this .cpp file.
#include <iostream>
#include <fstream>
#include <string>
#include "ReadWrite.h" //this refers to the header file "ReadWrite.h"
#include <vector> //enables vector creation 
#include <cmath> //enables use of sum() function found below
#include <map> //This enables map creation

using namespace std;

//this is the class for the Ref_image (the smaller Wally image)
class Ref_image { 

public:
	//this is a 2-D array that will be filled with data from the Wally image
	double WallyArray[49][36];
	//this calls the constructor that will fill the array with data
	Ref_image(); 
	//these 2 lines hold the addresses of the .txt and .pgm files in the assessment folder for the wally images
	const char *Wally_Grey = "Wally_grey.txt";
	const char *Wally_GreyPGM = "Wally_grey.pgm"; 
	//this calls the class destructor
	~Ref_image();
};

//this is the class for the Large_image (the Large puzzle image)
class Large_image { 

public:
	//this is a 2-D array that will be filled with data from the Puzzle image.
	double PuzzleArray[768][1024]; 
	//this calls the constructor that will fill the array with data
	Large_image(); 

	//these 2 lines hold the addresses of the .txt and .pgm files in the assessment folder for the puzzle images
	const char *Cluttered_Scene = "Cluttered_scene.txt";
	const char *Cluttered_ScenePGM = "Cluttered_scene.pgm"; 
	//this calls the class destructor
	~Large_image(); 
};

//this is the class for the Base image
class Base_image :

	//these two lines mean that the data from the Ref_image and Large_iamge classes are inherited into the Base_image class
	public Ref_image,
	public Large_image{ 

public:
	//this calls the constructor which sets the size for the Height and Width of the NNS matrix.
	Base_image(); 
	//this holds the address of the new pgm, where wally will be outlined.
	const char *NEWMAP = "NEW_MAP.pgm"; 
	//these 4 integers hold the size of the smaller and larger matrices
	int rowsR = 49;
	int columnsR = 36;
	int rowsL = 768;
	int columnsL = 1024;
	//this calls the class destructor
	~Base_image(); 
};

//this is the Ref_image class constructor
Ref_image::Ref_image() { 
	cout << "Ref_image constructor called..." << endl;
	double* wallydata = read_text(Wally_Grey, 49, 36); 

	for (int i = 0; i < 49; i++) {
		//this loop is used to cycle through every line of the WallyArray and append data at the correct points
		for (int j = 0; j < 36; j++) {
			WallyArray[i][j] = *(wallydata + (i * 36) + j); 
		}
	}
}

Large_image::Large_image() { 
	cout << "Large_image constructor called..." << endl;

	//this pointer reads in the data of the Cluttered_scene.txt file so that it can be appended to the PuzzleArray
	double* puzzledata = read_text(Cluttered_Scene, 768, 1024); 

	//this loop is used to cycle through every line of the PuzzleArray and append data at the correct points
	for (int i = 0; i < 768; i++) {
		for (int j = 0; j < 1024; j++) {
			PuzzleArray[i][j] = *(puzzledata + (i * 1024) + j); 
		}
	}
}

//this is the Base_image class constructor
Base_image::Base_image() { 
	int WIDTH = rowsL - rowsR;
	int HEIGHT = columnsL - columnsR; 

}

//this is the Ref_image class destructor
Ref_image::~Ref_image() { 
	cout << "Ref_image Destructor Called" << endl;
}

//this is the Large_image class destructor
Large_image::~Large_image() { 
	cout << "Large_image Destructor Called" << endl;
}

//this is the Base_image class destructor
Base_image::~Base_image() { 
	cout << "Base_image Destructor Called" << endl; 
}

//this is the function which finds the difference of the sums of the greyscale values to help find wally in the PuzzleArray.
int CheckPow(int rows, int cols, vector<vector<double>> &matrix, double matrixR[][36]) 
{
	int sumofsquares = 0;
	for (int x = 0; x < rows; x++)
	{
		//this loop cycles through each value in the matrixR (WallyArray) so that it can be compared with whats currently in the 2-D vector
		for (int y = 0; y < cols; y++) 
		{
			if (matrixR[x][y] != 255)
			{
				//this line adds the Squared value of the difference between the greyscale value of the 2-D vector and the WallyArray, when the values arent 255 (white).
				sumofsquares += int(pow(matrix[x][y] - matrixR[x][y], 2)); 
			}
		}
	}

	//then the value is returned to the main function so it can serve as a key in the map
	return sumofsquares; 
}

int main()
{
	cout << "Where's Wally programmed begins..." << endl;

	//Large_image LRG;
	//Ref_image REF;
	//write_pgm(LRG->Cluttered_ScenePGM, read_text(LRG->Cluttered_Scene, 768, 1024), 768, 1024, 255); 
	//write_pgm(REF->Wally_GreyPGM, read_text(REF->Wally_Grey, 49, 36), 49, 36, 255);
	//these 4 lines of code are used to create the .pgm files for the "Wally_grey.txt" and "Cluttered_scene.txt" files but are not needed after those files are created once
	//(These lines of code are commented for possible future use.)

	//this line creates an instance of the Ref_image class
	Ref_image *Wally = new Ref_image;
	//this line creates an instance of the Large_image class
	Large_image *Puzzle = new Large_image; 
	//this line creates an instance of the Base_image class
	Base_image *Base = new Base_image; 
	//this line is used to create a map, holding a pair of integers with an integer key.
	map<int, pair<int, int>> WallyMap; 


	//NEXT NEIGHBOUR SEARCH
	int WIDTH = Base->rowsL - Base->rowsR;
	int HEIGHT = Base->columnsL - Base->columnsR; 

	for (int i = 0; i < WIDTH; i++)
	{
		//these loops cycle through every value in the set boundary of the PuzzleArray, row by row
		for (int j = 0; j < HEIGHT; j++) { 
			//here is created the 2-D vector that will be storing the values of the PuzzleArray in to comapare those values to the WallyArray
			vector<vector<double>> temp; 
			//this resizes the 2-D vector so that it the same size as the WallyArray, so that when this sample of data is compared, it is completely accurate
			temp.resize(Base->rowsR, vector<double>(Base->columnsR, 0));
			//A key for the map so that when the comparison is made, we know at which point wally will be
			int key = 0; 
			for (int x = 0; x < (Base->rowsR); x++) {
				//these loops cycle through each point of the 2-D vector
				for (int y = 0; y < (Base->columnsR); y++) 
				{
					//at each point in the vector, the corresponding point in the sample area of the PuzzleArray is appended, so that it can be used for comparison
					temp[x][y] = Puzzle->PuzzleArray[i + x][j + y]; 
				}
			}
			//this line calls the CheckPow function and returns an integer to the key which will tell us how close the sample was the WallyArray
			key = CheckPow(Base->rowsR, Base->columnsR, temp, Wally->WallyArray);

			//this line creates a pair of integers to hold the coordinates at the point where the last comparison began
			pair <int, int> pair(i, j);

			//these coordinates are then added to the map with their corresponding key
			WallyMap[key] = pair; 

		}
	}

	//the x-coordinate is the 1st value in the pair of values that are stored in conjunction with the smallest key
	int xcoord = get<0>(WallyMap.begin()->second); 

	//the y-coordinate is the 2nd value
	int ycoord = get<1>(WallyMap.begin()->second); 

	for (int counter = xcoord; counter < (xcoord + 49); counter++) 
	{
		//these loops cycle through the PuzzleArray starting at the point where Wally is.
		for (int counter1 = ycoord; counter1 < (ycoord + 36); counter1++) 
		{
			// these if statements are responsible for turning the greyscale value of the points along the border of where Wally is in the PuzzleArray to black
			if (counter == xcoord || counter == xcoord + 48) 
			{	
				Puzzle->PuzzleArray[counter][counter1] = 0;
			}
			if (counter1 == ycoord || counter1 == ycoord + 35)
			{
				Puzzle->PuzzleArray[counter][counter1] = 0;	
			
			}
		}
	}

	//this double pointer is created to hold all the information of the updated PuzzleArray, now with the border in it
	double* NewPuzzleData = new double[Base->rowsL * Base->columnsL]; 

	for (int r = 0; r < Base->rowsL; r++)
	{
		//these loops cycle through every value in the double pointer
		for (int c = 0; c < Base->columnsL; c++) { 
			NewPuzzleData[r*Base->columnsL + c] =  Puzzle->PuzzleArray[r][c]; //and add the values of the 2-D array in, line by line, so that I am left with a very large 1-D array
		}
	}

	//then I create a new pgm file using the 1-D array and writing it to the address stored in the Base_image class
	write_pgm(Base->NEWMAP, NewPuzzleData, 768, 1024, 255); 

	//I then call the Base destructors which in turn will call the Large_image and Ref_image destructors
	delete Base;

	cout << "Where's Wally programme ends..." << endl;
	system("Pause");
}