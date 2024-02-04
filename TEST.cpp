#include <Windows.h>
#include <stdio.h>
#include <RestartManager.h>
#pragma comment(lib,"Rstrtmgr.lib")

int wmain(int argc, WCHAR** argv)
{
	DWORD dwSessionHandle = 0xFFFFFFFF;
	WCHAR szSessionKey[CCH_RM_SESSION_KEY + 1] = { 0 };

	DWORD dwError = RmStartSession(&dwSessionHandle, 0, szSessionKey);

	wprintf(L"RmStartSession 返回值：%d\n", dwError);

	if (dwError == ERROR_SUCCESS) {
		
		PCWSTR pszFile = L"C:\\Program Files (x86)\\360\\360Safe\\safemon\\360tray.exe";
		dwError = RmRegisterResources(dwSessionHandle, 1, &pszFile, 0, NULL, 0, NULL);

		if (dwError == ERROR_SUCCESS) {
			DWORD dwReason;
			UINT i;
			UINT nProcInfoNeeded;
			UINT nProcInfo = 100;
			RM_PROCESS_INFO rgpi[100];

			dwError = RmGetList(dwSessionHandle, &nProcInfoNeeded, &nProcInfo, rgpi, &dwReason);

			if (dwError == ERROR_SUCCESS) {
				
				RmShutdown(dwSessionHandle, 0, NULL);
			}
		}
		RmEndSession(dwSessionHandle);
	}

	return 0;
}