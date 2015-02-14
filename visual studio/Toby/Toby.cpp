

#include "Windows.h"
#include "atlstr.h"
#include <iostream>

#define RELEASE 0

BOOL RegisterMyProgramForStartup(PCWSTR pszAppName, PCWSTR pathToExe, PCWSTR args)
{
	HKEY hKey = NULL;
	LONG lResult = 0;
	BOOL fSuccess = TRUE;
	DWORD dwSize;

	const size_t count = MAX_PATH * 2;
	wchar_t szValue[count] = {};


	wcscpy_s(szValue, count, L"\"");
	wcscat_s(szValue, count, pathToExe);
	wcscat_s(szValue, count, L"\" ");

	if (args != NULL)
	{
		// caller should make sure "args" is quoted if any single argument has a space
		// e.g. (L"-name \"Mark Voidale\"");
		wcscat_s(szValue, count, args);
	}

	lResult = RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL);

	fSuccess = (lResult == 0);

	if (fSuccess)
	{
		dwSize = (wcslen(szValue) + 1) * 2;
		lResult = RegSetValueExW(hKey, pszAppName, 0, REG_SZ, (BYTE*)szValue, dwSize);
		fSuccess = (lResult == 0);
	}

	if (hKey != NULL)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}

	return fSuccess;
}


void RegisterProgram(WCHAR* path)
{
//	wchar_t szPathToExe[MAX_PATH];

//	GetModuleFileNameW(NULL, szPathToExe, MAX_PATH);
	RegisterMyProgramForStartup(L"Toby", path, L"");
}

void copyApplicationToLocation(TCHAR* path){
	TCHAR buf[MAX_PATH];
	GetModuleFileName(0, buf, MAX_PATH);
	CopyFile(buf, path, TRUE);
}



#if RELEASE
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
#else
int main(){
#endif

	std::cout << "copying to  " << getenv("APPDATA") << " ..." <<std::flush;
	WCHAR* appdata = _wgetenv(L"APPDATA");
	TCHAR out[MAX_PATH];
	_stprintf(out, L"%s\\Toby.exe", appdata);
	copyApplicationToLocation(out);
	std::cout << "done" << std::endl;

	std::cout << "Registering program... " << std::flush;
	RegisterProgram(out);
	std::cout << "done" << std::endl;

	while (1){
		Sleep(50);
	}

	return 0;
}


