#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <TlHelp32.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>

using namespace std;

vector<const wchar_t*> envir_val;

void get_envir_val() {
  
  string input = string(getenv("PROC_TO_KILL"));
  while (!input.empty()) {
    auto end = find(input.begin(), input.end(), ' ');
    string tmp = input.substr(0, end - input.begin());
    if (end == input.end()) break;
    end++;
    input.erase(input.begin(), end);

    wstring wstr(tmp.begin(), tmp.end());
    const wchar_t* wchr = wstr.c_str();
    envir_val.push_back(wchr);
  }
}

void kill(char* arg) {
  PROCESSENTRY32 pe = {0};
  pe.dwSize = sizeof(PROCESSENTRY32);
  HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  Process32First(hSnap, &pe);

  vector<DWORD> proc_to_kill;
  string name(arg); 
  int id;
  istringstream(name) >> id;

  wstring wstr = wstring(name.begin(), name.end());
  const wchar_t* wchr = wstr.c_str();

  get_envir_val();  

  if (id == 0) {
    do {
        if (!wcscmp(pe.szExeFile, wchr)) 
          proc_to_kill.push_back(pe.th32ProcessID);
    
      for (int i = 0; i < envir_val.size(); i++) 
          if (!wcscmp(pe.szExeFile, envir_val[i])) 
             proc_to_kill.push_back(pe.th32ProcessID);
       
    } while (Process32Next(hSnap, &pe));
  } else {
    do {
      if (pe.th32ProcessID == id) 
          proc_to_kill.push_back(pe.th32ProcessID);

      for (int i = 0; i < envir_val.size(); i++)
        if (!wcscmp(pe.szExeFile, envir_val[i])) 
            proc_to_kill.push_back(pe.th32ProcessID);
    } while (Process32Next(hSnap, &pe));
  }

  CloseHandle(hSnap);

  if (proc_to_kill.empty()) cout << "WARNING! (couldn't find such process)\n";

  for (DWORD & p : proc_to_kill) {
    HANDLE process = {0};
    process = OpenProcess(PROCESS_ALL_ACCESS, TRUE, p);
    if (process)
      TerminateProcess(process, 0);
    else
      cout << "WARNING! (couldn't terminate process)\n";
  }

  envir_val.clear();
}

int main(int argc, char* argv[]) {
  if (argc == 2) 
     kill(argv[1]);
  else
    cout << "WARNING! (must enter 2 args)\n";

  return 0;
}