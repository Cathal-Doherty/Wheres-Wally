// Reads .txt file representing an image of R rows and C Columns stored in filename and converts it to a 1D array of doubles of size R*C
// Memory allocation is performed inside readTXT
// Read .txt file with image of size (R (rows) x C (columns) ), and convert to an array of doubles

#include <iostream>
#include <fstream>
#include "ReadWrite.h"

using namespace std;

double* read_text(const char *fileName, int sizeR, int sizeC)
{
  double* data = new double[sizeR*sizeC];
  int i=0;
  ifstream myfile (fileName);
  if (myfile.is_open())
  {
	 
	while ( myfile.good())
    {
       if (i>sizeR*sizeC-1) break;
		 myfile >> *(data+i);
        // cout << *(data+i) << ' '; // This line display the converted data on the screen, you may comment it out. 
	     i++;                                                             
	}
    myfile.close();
  }

  else cout << "Unable to open file"; 
  //cout << i;

  return data;
}



// Converts a 1D array of doubles of size R*C to .pgm image of R rows and C Columns 
// and stores .pgm in filename
// Use Q = 255 for greyscale images and 1 for binary images.
void write_pgm(const char *filename, double *data, int sizeR, int sizeC, int Q)
{

 int i;
 unsigned char *image;
 ofstream myfile;

 image = (unsigned char *) new unsigned char [sizeR*sizeC];

 // convert the integer values to unsigned char
 
 for(i=0; i<sizeR*sizeC; i++)
	 image[i]=(unsigned char)data[i];

 myfile.open(filename, ios::out|ios::binary|ios::trunc);

 if (!myfile) {
   cout << "Can't open file: " << filename << endl;
   exit(1);
 }

 myfile << "P5" << endl;
 myfile << sizeC << " " << sizeR << endl;
 myfile << Q << endl;

 myfile.write( reinterpret_cast<char *>(image), (sizeR*sizeC)*sizeof(unsigned char));

 if (myfile.fail()) {
   cout << "Can't write image " << filename << endl;
   exit(0);
 }

 myfile.close();

 delete [] image;

}