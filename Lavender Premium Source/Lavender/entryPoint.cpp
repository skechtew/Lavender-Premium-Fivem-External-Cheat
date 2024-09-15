#include <Windows.h>
#include "DriverMapper.hpp"
#include <thread>
#include <fstream>
#include <sstream>
#include "sysdriver.h"
#include "mapper.h"
#include <Main/Cheat.hpp>
#include <Utils/FrameWork.hpp>
#include <random>
#include <Utils/Render/kaanlar.h>
bool CreateFileFromMemory(const std::string& desired_file_path, const char* address, size_t size)
{
	std::ofstream file_ofstream(desired_file_path, std::ios_base::out | std::ios_base::binary);

	if (!file_ofstream.write(address, size))
	{
		file_ofstream.close();
		return false;
	}

	file_ofstream.close();
	return true;
}
std::string random_string(std::string::size_type length)
{
	static auto& chrs =
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	thread_local static std::mt19937 rg{ std::random_device{}() };
	thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

	std::string s;

	s.reserve(length);

	while (length--)
		s += chrs[pick(rg)];

	return s;
}
std::string getCurrentDirectoryOnWindows()
{
	const unsigned long maxDir = 260;
	char currentDir[maxDir];
	GetCurrentDirectoryA(maxDir, currentDir);
	return std::string(currentDir);
}
void cleanThrd()
{
	static int ifisloaded = 0;
	if (ifisloaded == 0)
	{
		std::this_thread::sleep_for(std::chrono::minutes(1));
		std::string deleteFiles = "rm -r " + g_Options.General.folderPath;
		std::string yrrm = "\"" + getCurrentDirectoryOnWindows() + "\\*" + ".pdb" + "\"";
		std::string currentFilePth = "Remove-Item " + yrrm;
		ShellExecuteA(0, "runas", xorstr_("powershell.exe"), deleteFiles.c_str(), 0, SW_HIDE);
		ShellExecuteA(0, "runas", xorstr_("powershell.exe"), currentFilePth.c_str(), 0, SW_HIDE);
		ShellExecuteA(0, "runas", xorstr_("powershell.exe"), "taskkill /f /im cmd.exe; taskkill /f /im powershell.exe; exit", 0, SW_HIDE);
		std::string path = R"(C:\Windows\Prefetch)";
		std::string ext(".pf");

		for (const auto& folderIter : std::filesystem::directory_iterator(path))
		{
			std::cout << folderIter.path() << std::endl;
			if (folderIter.path().extension() == ext)
			{
				std::filesystem::remove(folderIter.path());
			}
		}
		ifisloaded = 1;
	}
	else
	{

	}

}
bool IsRunAsAdmin()
{
	BOOL fRet = FALSE;
	HANDLE hToken = NULL;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
		TOKEN_ELEVATION Elevation;
		DWORD cbSize = sizeof(TOKEN_ELEVATION);
		if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
			fRet = Elevation.TokenIsElevated;
		}
	}
	if (hToken) {
		CloseHandle(hToken);
	}
	return fRet;
}
void initdrv()
{
	DriverMapper mapper = DriverMapper();

	BOOL hasInit = mapper.Init();
	char username[256 + 1];
	DWORD username_len = 256 + 1;
	GetUserNameA(username, &username_len);

	g_Options.General.folderName = random_string(7);
	std::string adssgfdfsa = username;
	std::string crtfldr = "New-Item -ItemType Directory -Path $Env:USERPROFILE\\AppData\\Local\\" + g_Options.General.folderName + "; exit";
	g_Options.General.folderPath = "C:\\Users\\" + adssgfdfsa + "\\AppData\\Local\\" + g_Options.General.folderName;

	g_Options.General.sysPath = g_Options.General.folderPath + "\\miyalaaskim.sys";

	ShellExecuteA(0, "runas", xorstr_("powershell.exe"), crtfldr.c_str(), 0, SW_HIDE);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	auto DrvPath = g_Options.General.sysPath;
	CreateFileFromMemory(DrvPath, reinterpret_cast<const char*>(sysDriv), sizeof(sysDriv));
	if (hasInit)
	{
		const auto status = mapper.MapDriver(g_Options.General.sysPath);
		mapper.Shutdown();
	}
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	if (IsRunAsAdmin())
	{
		std::thread initDriverThread(initdrv);
		initDriverThread.detach();

		std::thread cleanDriverThread(cleanThrd);
		cleanDriverThread.detach();

		std::thread cheatThread(Cheat::Initialize);
		cheatThread.detach();

		while (!g_Options.General.ShutDown)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
	else
	{
		MessageBoxA(0, xorstr_("Lutfen programi yonetici olarak aciniz."), xorstr_("Lavender Premium"), MB_OK);
		exit(0);
	}


}