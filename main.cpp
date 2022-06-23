// Compare files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <windows.h>

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

bool fileExists(string fileName) {//if can read file, then file exists
  ifstream test(fileName);
  return (test) ? true : false;
}

vector<string> shrinkVector(vector<string> vec) { //takes whole string vector and deletes empty elements
    while(vec.back().empty()){
        vec.pop_back();
    }

    return vec;
}

vector<string> listFiles(vector<string> files) { //finds all files and directories in program folder, then returns them in vector<string>
    string path = "./";
    int i = 0;

    cout << "Analyzing files..." << endl;

    for (const auto & file : std::filesystem::recursive_directory_iterator(path)) {
        //cout << file.path() << endl;
        files[i] = file.path().string();
        i++;
    }
    //cout << "done" << endl;
    files = shrinkVector(files);
//goal 76 files ||||
    for(unsigned int i = 0; i < files.size(); i++){
        if(!fileExists(files[i])){
            //cout << "deleting " + files[i] << endl;
            files[i].swap(files.back());
            files.pop_back();
        }
    }

    cout << "Number of files: " << files.size() << endl;

    return files;
}

int getWindowColumns(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    unsigned int columns;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    return columns;
}

int main(int argc, char *argv[]) {
    int maxarraysize = 128000;
    vector<string> files(maxarraysize);

    files = listFiles(files);
    vector<string> samefiles(1);
    int precentage = 0;

    for(unsigned int i = 0; i < files.size(); i++){
        if (fileExists(files[i]) /* && files[i].find("jpg") != std::string::npos */ ){ //commented code can be used to compare only some files
            //cout << "this is a file" << endl;
            for(unsigned int j = 0; j < files.size(); j++){
                if (i != j && fileExists(files[j]) /* && files[i].find("jpg") != std::string::npos */ ){ //commented code can be used to compare only some files

                    unsigned int columns = getWindowColumns();

                    cout << "\r";
                    string spaces = "";
                    for(unsigned int c = 0; c < columns; c++){
                       spaces += " ";
                    }
                    cout << spaces;

                    precentage = ((i * 1.0 + 1) / files.size())*100;
                    string text = to_string(precentage) + "% | Comparing " + files[i] + " to " + files[j];
                    text.resize(columns);
                    cout << "\r" + text;
                    if(comparefiles(files[i], files[j]) == 3){
                        //cout << files[i] + " is the same as " + files[j] << endl;
                        samefiles.push_back(files[i] + " is the same as " + files[j]);
                    }
                }
            }
        }
        else{
            //cout << "directory found" << endl;
        }
    }
    cout << endl;
    for(unsigned int i = 0; i < samefiles.size(); i++){
        cout << samefiles[i] << endl;
    }

    return 0;
}
