// Compare files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;

int comparefiles(string file1, string file2)
{
  int i;

  unsigned char buf1[102400], buf2[102400];

  ifstream f1(file1, ios::in | ios::binary);
  if(!f1) {/*  ww  w  .    d  em  o  2   s .  c  o  m  */
    //cout << "Cannot open first file.\n";
    return 1;
  }
  ifstream f2(file2, ios::in | ios::binary);
  if(!f2) {
    //cout << "Cannot open second file.\n";
    return 1;
   }

  //cout << "Comparing files...\n";

  do {
    f1.read((char *) buf1, sizeof buf1);
    f2.read((char *) buf2, sizeof buf2);
  if(f1.gcount() != f2.gcount()) {
    //cout << "Files are of differing sizes.\n";
    f1.close();
    f2.close();
    return 0;
  }

  // compare contents of buffers
  for(i=0; i<f1.gcount(); i++)
    if(buf1[i] != buf2[i]) {
       //cout << "Files differ.\n";
       f1.close();
       f2.close();
       return 0;
    }


  } while(!f1.eof() && !f2.eof());

  //cout << "Files are the same.\n";

  f1.close();
  f2.close();

  return 3;
}

std::vector<string> files(128000);

int listfiles() {
    string path = "./";
    int i = 0;

    for (const auto & file : std::filesystem::recursive_directory_iterator(path)) {
        //cout << file.path() << endl;
        files[i] = file.path().string();
        i++;
    }
    cout << "done" << endl;
    return EXIT_SUCCESS;
}

bool fileExists(const string fileName)
{
  std::ifstream test(fileName);
  return (test) ? true : false;
}

int main() {
    listfiles();

    for(int i = 0; i < 128000; i++){
        if (fileExists(files[i]) /* && files[i].find("jpg") != std::string::npos */ ){ //commented code can be used to compare only some files
            //cout << "this is a file" << endl;
            for(int j = 0; j < 128000; j++){
                if (i != j && fileExists(files[j]) /* && files[i].find("jpg") != std::string::npos */ ){ //commented code can be used to compare only some files
                    if(comparefiles(files[i], files[j]) == 3){
                        cout << files[i] + " is the same as " + files[j] << endl;
                    }
                }
            }
        }
        else{
            //cout << "directory found" << endl;
        }
    }

    return 0;
}
