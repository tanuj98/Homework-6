#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <string.h>
using namespace std;
class BinaryFileHeader
{
public:


  uint32_t magicNumber; /* Should be 0xFEEDFACE */
  uint32_t versionNumber;
  uint64_t numRecords;
};


const int maxRecordStringLength = 25;
class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

int main()
{
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  BinaryFileRecord *myRecord = new BinaryFileRecord();

  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);

  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));

    //  cout << sizeof(BinaryFileRecord);

  //  cout << "Value was: " << setprecision(10) << myRecord->magicNumber << endl;
  int magic = myHeader ->magicNumber;
  uint32_t  num_record = myHeader ->numRecords;
  //  cout << magic;
  stringstream stream;
  stream << hex << magic;
  string result( stream.str() );
  //cout << result;
  transform(result.begin(), result.end(), result.begin(),:: toupper);
  stringstream s2;
  s2 << myHeader ->versionNumber;
  cout <<"Version number" << s2.str();
  cout << result;
  for(int i=2; i <= num_record+1 ; i ++)
    {
      binInfile.read((char *) myRecord ,sizeof(BinaryFileRecord));
      int st_len = strlen((char *) myRecord ->stringBuffer);
      cout <<endl<<st_len;
      cout <<myRecord ->stringBuffer;
    }
  binInfile.close();
  return 0;
}
