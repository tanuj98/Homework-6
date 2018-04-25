/*
 * Usage of CDK Matrix
 *
 * F
 * Tanuj Tiwari
 * Email: tanuj.tiwari@utdallas.edu
 */

#include <iostream>
#include "cdk.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <string.h>

const int maxRecordStringLength = 25;
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;
// Class for BinaryFileHeader
class BinaryFileHeader
{
public:


  uint32_t magicNumber; /* Should be 0xFEEDFACE */
  uint32_t versionNumber;
  uint64_t numRecords;
};

// Class for BinaryFileRecord
class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"C0", "a", "b", "c"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */

  //
  // This is where code is modified
  //Initialize objects
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  BinaryFileRecord *myRecord = new BinaryFileRecord();
  // Initialize if stream reader
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);
  // Read the file
  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
  // Get the magic number
  uint32_t magic = myHeader ->magicNumber;
  uint32_t  num_record = myHeader ->numRecords;
  // Initialize stream objects
  stringstream stream;
  stream << hex << magic;
  // Store it in sresult
  string result( stream.str() );
  // Transform to upper case
  transform(result.begin(), result.end(), result.begin(),:: toupper);
  // C;ear the string stream
  stream.str("");
  stream.clear();
  stream << myHeader ->versionNumber;
  string versions(stream.str());
  versions = "Version Number : " + versions;
  // Another string stream object
  stringstream s3;
  s3 << myHeader ->numRecords;
  string rec(s3.str());
  rec = "NumRecords : " + rec;
  result = "Magic : 0x" + result;
  // Set the matrix 
  setCDKMatrixCell(myMatrix, 1, 1, result.c_str());
  setCDKMatrixCell(myMatrix, 1 , 2,versions.c_str());
  setCDKMatrixCell(myMatrix, 1 , 3,rec.c_str());
  // Set versions and everything inside matrix and the records
  for(uint32_t i=2; i <= num_record+1 ; i ++)
    {
      binInfile.read((char *) myRecord ,sizeof(BinaryFileRecord));
      int st_len = strlen((char *) myRecord ->stringBuffer);
      s3.str("");
      s3.clear();
      s3 << st_len;
      string num_rec(s3.str());
      num_rec = "strlen: " + num_rec;
      setCDKMatrixCell(myMatrix, i, 1, num_rec.c_str());
      setCDKMatrixCell(myMatrix, i, 2, myRecord -> stringBuffer);
      //cout <<endl<<st_len;
      //cout <<myRecord ->stringBuffer;
    }
   binInfile.close();
   drawCDKMatrix(myMatrix, true);
   unsigned char x;
   cin >> x;





  //


  // Cleanup screen
    endCDK();
}
