#include <iostream>
#include <Windows.h>

using namespace std;

// Memory

DWORD_PTR Ammunition = 0x0323CF0;

// Declared Variables

int value;
int ReceiveValue;

int main(int argc, char *argv[]) {
	HWND Window = FindWindowA(NULL, "AssaultCube");
	if (!Window) {
		cout << "Window not found!" << endl;
		system("pause");
		exit(-1);
	}

	DWORD Process;

	cout << "Enter the amount of ammo: ";
	cin >> value;

	GetWindowThreadProcessId(Window, &Process);

	HANDLE Handler = OpenProcess(PROCESS_ALL_ACCESS, false, Process);

	if (!Handler) {
		cout << "Process not found!" << endl;
		system("pause");
		exit(-1);
	}

	while (true) {
		// 0x52 = Key R
		if (GetAsyncKeyState(0x52)) {
			WriteProcessMemory(Handler, (LPVOID)Ammunition, &value, 4, 0);
		}
		ReadProcessMemory(Handler, (LPVOID)Ammunition, &ReceiveValue, sizeof(int), 0);
		cout << "Ammo quantity: " << ReceiveValue;
		system("cls");
	}
	
	return 0;
}