
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <vector>

using namespace std;

LPCSTR kill_path = "C:\\OS\\Processes\\Killer\\killer\\Debug\\killer.exe";

void print_mask() {
  cout << "------------------------------------------------------------------------\n";
  PROCESSENTRY32 pe = {0};
  pe.dwSize = sizeof(PROCESSENTRY32);
  HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  Process32First(hSnap, &pe);
  do {
    wprintf(L"%s\t\t\t\t%d\t%d\n", pe.szExeFile, pe.th32ProcessID,
            pe.cntThreads);
  } while (Process32Next(hSnap, &pe));

  CloseHandle(hSnap);
  cout << "------------------------------------------------------------------------\n";
}

void action() {
  STARTUPINFOA sia = {0};
  PROCESS_INFORMATION pi = {0};

  string command, arg;
  cin >> command;
  if (command == "kill") {
    cin >> arg;
    string res = command + " " + arg;
    char* input = (char*)res.c_str();

    if (CreateProcessA(kill_path, input, NULL, NULL, FALSE, 0, NULL, NULL, &sia,
                       &pi)) {
      WaitForSingleObject(pi.hProcess, INFINITE);
    } else
      cout << "WARNING! (Creation failed)\n";

  } else if (command == "print")
    print_mask();
  else if (command == "exit")
    return;
  else
    cout << "WARNING! (Unknown command)\n";

  // SetEnvironmentVariable(L"PROC_TO_KILL", NULL);

  _putenv_s("PROC_TO_KILL", "0");

  action();
}

int main() { 
	SetEnvironmentVariable(L"PROC_TO_KILL", L"iexplore.exe Viber.exe ");
	print_mask();
	action(); 
	return 0;
}	