
#include<stdio.h>
#include<iostream>
#include<string>
#include <windows.h>

using namespace std;

typedef unsigned char* (*FUNC1)(const char* koe, int iSpeed, int* pSize);
typedef void(*FUNC2)(unsigned char* wav);

int main(int argc, char* argv[])
{
	//cout << argv[1] << argv[2] << argv[3] << argv[4];
	if (!argv[1] || !argv[2] || !argv[3] || !argv[4]) {
		cout << -11;
		return -11;
	}
	HMODULE f1 = LoadLibrary(L"f1/AquesTalk.dll");
	FUNC1 AquesTalk_SyntheF1 = (FUNC1)GetProcAddress(f1, "AquesTalk_Synthe");
	FUNC2 AquesTalk_FreeWave = (FUNC2)GetProcAddress(f1, "AquesTalk_FreeWave");

	string text;
	//fstream inText;
	try {

		FILE* inText;
		char str[256];

		fopen_s(&inText, argv[3], "r");
		while (fgets(str, 256, inText) != NULL)
		{
			text = text + str;
		}
		fclose(inText);

	}
	catch (char* err) {
		cout << -1;
		return -1;
	}

	int size;
	unsigned char* wav;

	if ((string)argv[1] == (string)"f1") {
		wav = AquesTalk_SyntheF1(text.c_str(), atoi(argv[2]), &size);
	}
	else if ((string)argv[1] == (string)"f2") {
		HMODULE f2 = LoadLibrary(L"f2/AquesTalk.dll");
		FUNC1 AquesTalk_SyntheF2 = (FUNC1)GetProcAddress(f2, "AquesTalk_Synthe");
		wav = AquesTalk_SyntheF2(text.c_str(), (int)argv[2], &size);
	}
	else if ((string)argv[1] == (string)"imd1") {
		HMODULE imd1 = LoadLibrary(L"imd1/AquesTalk.dll");
		FUNC1 AquesTalk_SyntheImd1 = (FUNC1)GetProcAddress(imd1, "AquesTalk_Synthe");
		wav = AquesTalk_SyntheImd1(text.c_str(), (int)argv[2], &size);
	}
	else if ((string)argv[1] == (string)"jgr") {
		HMODULE jgr = LoadLibrary(L"jgr/AquesTalk.dll");
		FUNC1 AquesTalk_SyntheJgr = (FUNC1)GetProcAddress(jgr, "AquesTalk_Synthe");
		wav = AquesTalk_SyntheJgr(text.c_str(), (int)argv[2], &size);
	}
	else if ((string)argv[1] == (string)"dvd") {
		HMODULE dvd = LoadLibrary(L"dvd/AquesTalk.dll");
		FUNC1 AquesTalk_SyntheDvd = (FUNC1)GetProcAddress(dvd, "AquesTalk_Synthe");
		wav = AquesTalk_SyntheDvd(text.c_str(), (int)argv[2], &size);
	}
	else if ((string)argv[1] == (string)"m1") {
		HMODULE m1 = LoadLibrary(L"m1/AquesTalk.dll");
		FUNC1 AquesTalk_SyntheM1 = (FUNC1)GetProcAddress(m1, "AquesTalk_Synthe");
		wav = AquesTalk_SyntheM1(text.c_str(), (int)argv[2], &size);
	}
	else if ((string)argv[1] == (string)"m2") {
		HMODULE m2 = LoadLibrary(L"m2/AquesTalk.dll");
		FUNC1 AquesTalk_SyntheM2 = (FUNC1)GetProcAddress(m2, "AquesTalk_Synthe");
		wav = AquesTalk_SyntheM2(text.c_str(), (int)argv[2], &size);
	}
	else if ((string)argv[1] == (string)"phont") {
		HMODULE phont = LoadLibrary(L"phont/AquesTalk.dll");
		FUNC1 AquesTalk_SynthePhont = (FUNC1)GetProcAddress(phont, "AquesTalk_Synthe");
		wav = AquesTalk_SynthePhont(text.c_str(), (int)argv[2], &size);
	}
	else if ((string)argv[1] == (string)"r1") {
		HMODULE r1 = LoadLibrary(L"r1/AquesTalk.dll");
		FUNC1 AquesTalk_SyntheR1 = (FUNC1)GetProcAddress(r1, "AquesTalk_Synthe");
		wav = AquesTalk_SyntheR1(text.c_str(), (int)argv[2], &size);
	}
	else {
		cout << -2;
		return -2;
	}

	if (wav == 0) {
		fprintf(stderr, "ERR:%d", size);
		cout << -3;
		return -3;
	}

	FILE* fp;
	try {
		fopen_s(&fp, argv[4], "wb");
		if (fp == 0) {
			fprintf(stderr, "ERR:%d", size);
			cout << -4;
			return -4;
		}
		fwrite(wav, 1, size, fp);
		fclose(fp);
	}
	catch (char* err) {
		cout << err;
		return -5;
	}
	AquesTalk_FreeWave(wav);
	cout << 0;
	return 0;
}