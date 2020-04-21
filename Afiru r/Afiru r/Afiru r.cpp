#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include "shlobj.h"
#include <string>
#include <commdlg.h>
#include <stdlib.h>
#include <time.h>
#include <mciapi.h>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;
using std::wstring;

vector <string> title;
vector <int> noe;
vector <LPSTR> path;

int file_print (int z)
{
    fstream playlist_file;
    playlist_file.open("./playlist.txt", std::ios::out | std::ios::trunc);
    playlist_file << title[z];
    playlist_file.close();
    return (77);
}
string getFileName(const string& s) {

    char sep = '/';

#ifdef _WIN32
    sep = '\\';
#endif
    size_t i = s.rfind(sep, s.length());
    if (i != string::npos) {
        return(s.substr(i + 1, s.length() - i));
    }
    return("");
}

int main(int argc, char* argv[])
{
    int nof = 0;    
   /* struct song_randomizer {
        string title    ;
        int noe;
        LPSTR path;
    };*/

    waveOutSetVolume(NULL, 0xFFFF);
    
    OPENFILENAME ofn;
    ::memset(&ofn, 0, sizeof(ofn));
    char f1[MAX_PATH];
    f1[0] = 0;
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrTitle = (LPCSTR)"Select A WAV / MP3 Files to randomize (press cancel to end)";
    ofn.lpstrFilter = (LPCSTR)"Wav files\0*.wav\0";
    ofn.nFilterIndex = 2;
    ofn.lpstrFile = (LPSTR)f1;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST;
    ofn.nFileOffset = OFN_EXPLORER;
    //song_randomizer* song;
    //song = new song_randomizer[nof];
    
    while (::GetOpenFileName(&ofn) != FALSE)
    {
        title.push_back(getFileName(ofn.lpstrFile));
        noe.push_back(nof + 1);
        path.push_back(ofn.lpstrFile);
        nof++;
    }
    
    if (nof <= 0)
    {
        exit(80085);
    } 
    
    srand(time(NULL));
    int random = rand() % nof;

    cout << "now playing (random song from picked from user's choose):" << title[random];

    string str = title[random];
    LPSTR cc = const_cast<char*>(str.c_str());;

    file_print(random);
    sndPlaySound(cc, 0);

    return 88;
    //tablica wczytania plikow przechowuje nazwy i lokacje (char / struct) , budowana dynamicznie (na nowej tablicy)(pamietac o kasowaniu pamieci i dynamicznym tworzeniu), zapisz w pliku dana liste (wczytanie playlisty), ale random tez moze odczytac z listy
}