#include "Interface.hpp"
#include <Main/Options.hpp>
#include "kitapsizbirkodyigini.h"
#include <Utils/Dependencies/ImGui/imgui_settings.h>
#include <Main/MemoryAllocate/scanner.h>
#include "Main/xorstring.h"
#include <thread>
#include "kaanlar.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

std::string AppCompatFlagsKeys[86] = {
	xorstr_("CCLEANER"), xorstr_("CCLeaner"), xorstr_("CCleaner"), xorstr_("CCleaner"), xorstr_("Ccleaner"), xorstr_("Ccleaner"),
	xorstr_("clicker"), xorstr_("Clicker"), xorstr_("Cheat-Engine"), xorstr_("CheatEngine"), xorstr_("cheatengine"), xorstr_("cheat-engine"),
	xorstr_("CrySearch"), xorstr_("DControl"), xorstr_("Dcontrol"), xorstr_("Desktop"), xorstr_("Desktop"), xorstr_("ECHO"),
	xorstr_("Echo"), xorstr_("Hacker"), xorstr_("Hax"), xorstr_("Install"), xorstr_("install"), xorstr_("Lavender"),
	xorstr_("Local\\Temp"), xorstr_("Local\\Temp"), xorstr_("Memory"), xorstr_("OCEAN"), xorstr_("Ocean"), xorstr_("PRIVAZER"),
	xorstr_("PRivazer"), xorstr_("PrivaZer"), xorstr_("Privazer"), xorstr_("Privazer"), xorstr_("Process"), xorstr_("Program Files"),
	xorstr_("R-WIPE"), xorstr_("R-Wipe"), xorstr_("R-Wipe"), xorstr_("R-wipe"), xorstr_("R-wipe"), xorstr_("RWipe"),
	xorstr_("RWipe"), xorstr_("Rwipe"), xorstr_("SlideToShutDown.exe"), xorstr_("SndVol.exe"), xorstr_("WerFault.exe"), xorstr_("ccleaner"),
	xorstr_("ccleaner"), xorstr_("cheat"), xorstr_("cmd.exe"), xorstr_("conhost.exe"), xorstr_("dcontrol"), xorstr_("drive"),
	xorstr_("echo"), xorstr_("hack"), xorstr_("lavender"), xorstr_("launcher"), xorstr_("loader"), xorstr_("memory"),
	xorstr_("mmc.exe"), xorstr_("ocean"), xorstr_("powershell.exe"), xorstr_("privazer"), xorstr_("ProcessHacker"), xorstr_("privazer"),
	xorstr_("query"), xorstr_("r-wipe"), xorstr_("r-wipe"), xorstr_("rWipe"), xorstr_("revo"), xorstr_("rwipe"),
	xorstr_("rwipe"), xorstr_("source"), xorstr_("source\\repos"), xorstr_("taskkill.exe"), xorstr_("unins"), xorstr_("uninstall"),
	xorstr_("updater"), xorstr_("vpn"), xorstr_("w32tm.exe"), xorstr_("wevtutil.exe"), xorstr_("wextract.exe"), xorstr_("wlrmdr.exe"), xorstr_("x64"), xorstr_("x86"),
};

static constexpr std::array<const char*, 166U> key_names =
{
	"None",
	"mouse 1", "mouse 2", "cancel", "mouse 3", "mouse 4", "mouse 5", "",
	"backspace", "tab", "", "", "clear", "enter", "", "",
	"shift", "control", "alt", "pause", "caps", "", "", "", "", "", "",
	"escape", "", "", "", "", "space", "page up", "page down",
	"end", "home", "left", "up", "right", "down", "", "", "",
	"print", "insert", "delete", "",
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
	"", "", "", "", "", "", "",
	"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
	"l", "m", "n", "o", "p", "q", "r", "s", "t", "u",
	"v", "w", "x", "y", "z", "lwin", "rwin", "", "", "",
	"num0", "num1", "num2", "num3", "num4", "num5",
	"num6", "num7", "num8", "num9",
	"*", "+", "", "-", ".", "/",
	"f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8",
	"f9", "f10", "f11", "f12", "f13", "f14", "f15", "f16",
	"f17", "f18", "f19", "f20", "f21", "f22", "f23", "f24",
	"", "", "", "", "", "", "", "",
	"num lock", "scroll lock",
	"", "", "", "", "", "", "",
	"", "", "", "", "", "", "",
	"Lshift", "Rshift", "Lctrl",
	"Rctrl", "Lmenu", "Rmenu"
};

const char* GetFileNameFromPath(const char* _buffer)
{
	char c;
	int  i;
	for (i = 0; ; ++i) {
		c = *((char*)_buffer + i);
		if (c == '\\' || c == '/')
			return GetFileNameFromPath((char*)_buffer + i + 1);
		if (c == '\0')
			return _buffer;
	}
	return "";
}
namespace fs = std::filesystem;

void xxRenderTextColor(ImFont* font, const ImVec2& p_min, const ImVec2& p_max, ImU32 col, const char* text, const ImVec2& align)
{
	ImGui::PushFont(font);
	ImGui::PushStyleColor(ImGuiCol_Text, col);
	ImGui::RenderTextClipped(p_min, p_max, text, NULL, NULL, align, NULL);
	ImGui::PopStyleColor();
	ImGui::PopFont();
}
bool KeyBind(const char* label, int* value)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = g.CurrentWindow;

	if (window->SkipItems)
		return false;

	ImGuiIO& io = g.IO;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, nullptr, true);

	const float w = ImGui::GetContentRegionMax().x - style.WindowPadding.x;
	const float square_sz = 20.f;
	const ImVec2 pos = window->DC.CursorPos;
	const ImRect rect(pos, pos + ImVec2(w, 50));
	const ImRect clickable(window->DC.CursorPos + ImVec2(w - 80, 10), window->DC.CursorPos + ImVec2(w - 10, 40));

	ImGui::ItemSize(rect, style.FramePadding.y);
	if (!ImGui::ItemAdd(rect, id, &rect, ImGuiItemFlags_Inputable))
		return false;

	const bool hovered = ImGui::ItemHoverable(rect, id, 0);
	if (hovered)
	{
		ImGui::SetHoveredID(id);
		g.MouseCursor = ImGuiMouseCursor_TextInput;
	}

	const bool clicked = hovered && io.MouseClicked[0];
	const bool double_clicked = hovered && g.IO.MouseDoubleClicked[0];
	if (clicked || double_clicked)
	{
		if (g.ActiveId != id)
		{
			memset(io.MouseDown, 0, sizeof(io.MouseDown));
			memset(io.KeysDown, 0, sizeof(io.KeysDown));
			*value = 0;
		}

		ImGui::SetActiveID(id, window);
		ImGui::FocusWindow(window);
	}

	bool value_changed = false;
	if (int k = *value; g.ActiveId == id)
	{
		for (int n = 0; n < IM_ARRAYSIZE(io.MouseDown); n++)
		{
			if (ImGui::IsMouseDown(n))
			{
				switch (n)
				{
				case 0:
					k = VK_LBUTTON;
					break;
				case 1:
					k = VK_RBUTTON;
					break;
				case 2:
					k = VK_MBUTTON;
					break;
				case 3:
					k = VK_XBUTTON1;
					break;
				case 4:
					k = VK_XBUTTON2;
					break;
				}

				value_changed = true;
				ImGui::ClearActiveID();
			}
		}

		if (!value_changed)
		{
			for (int n = VK_BACK; n <= VK_RMENU; n++)
			{
				if (ImGui::IsKeyDown((ImGuiKey)n))
				{
					k = n;
					value_changed = true;
					ImGui::ClearActiveID();
				}
			}
		}

		if (ImGui::IsKeyPressed(ImGuiKey_Escape))
		{
			*value = 0;
			ImGui::ClearActiveID();
		}
		else
			*value = k;
	}

	char chBuffer[64] = { };
	sprintf_s(chBuffer, sizeof(chBuffer), " %s ", value != 0 && g.ActiveId != id ? key_names.at(*value) : g.ActiveId == id ? "Press" : "None");
	window->DrawList->AddRectFilled(rect.Min, rect.Max, ImGui::GetColorU32(c::elements::background), c::elements::rounding);

	window->DrawList->AddRect(clickable.Min, clickable.Max, ImGui::GetColorU32(c::elements::background_widget), c::elements::rounding);

	xxRenderTextColor(font::lexend_bold, clickable.Min, clickable.Max, ImGui::GetColorU32(c::elements::text_active), chBuffer, ImVec2(0.5f, 0.5f));

	//window->DrawList->AddText(ImVec2(rect.Max.x - ImGui::CalcTextSize(chBuffer).x, rect.Min.y + style.FramePadding.y), ImGui::GetColorU32(g.ActiveId == id ? c::elements::text : c::elements::text_active), chBuffer);
	xxRenderTextColor(font::lexend_bold, rect.Min + ImVec2(10, 0), rect.Max, ImGui::GetColorU32(c::elements::text_active), label, ImVec2(0.0, 0.2));
	return value_changed;
}
bool NewBeginChildEx(const char* name, ImGuiID id, const ImVec2& size_arg, ImGuiWindowFlags window_flags)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* parent_window = g.CurrentWindow;
	IM_ASSERT(id != 0);


	IM_ASSERT((window_flags & ImGuiWindowFlags_AlwaysAutoResize) == 0 && xorstr_("Cannot specify ImGuiWindowFlags_AlwaysAutoResize for BeginChild(). Use ImGuiChildFlags_AlwaysAutoResize!"));


	window_flags |= ImGuiWindowFlags_ChildWindow | ImGuiWindowFlags_NoTitleBar;
	window_flags |= (parent_window->Flags & ImGuiWindowFlags_NoMove);




	const ImVec2 size_avail = ImGui::GetContentRegionAvail();
	const ImVec2 size_default(size_avail.x, size_avail.y);
	const ImVec2 size = ImGui::CalcItemSize(size_arg, size_default.x, size_default.y);
	ImGui::SetNextWindowSize(size);

	//     GetWindowDrawList()->AddRect(parent_window->DC.CursorPos, parent_window->DC.CursorPos + size_arg, GetColorU32(c::accent), 0);

	const char* temp_window_name;

	if (name)
		ImFormatStringToTempBuffer(&temp_window_name, NULL, xorstr_("%s/%s_%08X"), parent_window->Name, name, id);
	else
		ImFormatStringToTempBuffer(&temp_window_name, NULL, xorstr_("%s/%08X"), parent_window->Name, id);

	const float backup_border_size = g.Style.ChildBorderSize;

	const bool ret = ImGui::Begin(temp_window_name, NULL, window_flags);

	g.Style.ChildBorderSize = backup_border_size;

	ImGuiWindow* child_window = g.CurrentWindow;
	child_window->ChildId = id;

	if (child_window->BeginCount == 1) parent_window->DC.CursorPos = child_window->Pos;

	const ImGuiID temp_id_for_activation = ImHashStr(xorstr_("##Child"), 0, id);
	if (g.ActiveId == temp_id_for_activation) ImGui::ClearActiveID();
	if (g.NavActivateId == id && !(window_flags & ImGuiWindowFlags_NavFlattened) && (child_window->DC.NavLayersActiveMask != 0))
	{
		ImGui::FocusWindow(child_window);
		ImGui::NavInitWindow(child_window, false);
		ImGui::SetActiveID(temp_id_for_activation, child_window);
		g.ActiveIdSource = g.NavInputSource;
	}
	return ret;
}
void NewEndChild()
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* child_window = g.CurrentWindow;
	ImGui::PopStyleVar(2);
	IM_ASSERT(g.WithinEndChild == false);
	IM_ASSERT(child_window->Flags & ImGuiWindowFlags_ChildWindow);

	g.WithinEndChild = true;
	ImVec2 child_size = child_window->Size;
	ImGui::End();
	if (child_window->BeginCount == 1)
	{
		ImGuiWindow* parent_window = g.CurrentWindow;
		ImRect bb(parent_window->DC.CursorPos, ImVec2(parent_window->DC.CursorPos.x + child_size.x, parent_window->DC.CursorPos.y + child_size.y));
		ImGui::ItemSize(child_size);
		if ((child_window->DC.NavLayersActiveMask != 0 && !(child_window->Flags & ImGuiWindowFlags_NavFlattened)))
		{
			ImGui::ItemAdd(bb, child_window->ChildId);
			ImGui::RenderNavHighlight(bb, child_window->ChildId);

			if (child_window->DC.NavLayersActiveMask == 0 && child_window == g.NavWindow) ImGui::RenderNavHighlight(ImRect(ImVec2(bb.Min.x - 2, bb.Min.y - 2), ImVec2(bb.Max.x + 2, bb.Max.y + 2)), g.NavId, ImGuiNavHighlightFlags_Compact);
		}
		else
		{
			ImGui::ItemAdd(bb, 0);

			if (child_window->Flags & ImGuiWindowFlags_NavFlattened) parent_window->DC.NavLayersActiveMaskNext |= child_window->DC.NavLayersActiveMaskNext;
		}
		if (g.HoveredWindow == child_window) g.LastItemData.StatusFlags |= ImGuiItemStatusFlags_HoveredWindow;
	}
	g.WithinEndChild = false;
	g.LogLinePosY = -FLT_MAX;
}
bool NewBeginChild(const char* str_id, const ImVec2& size_arg, ImGuiWindowFlags window_flags)
{
	ImGuiID id = ImGui::GetCurrentWindow()->GetID(str_id);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 10));

	return NewBeginChildEx(str_id, id, size_arg, window_flags | ImGuiWindowFlags_AlwaysUseWindowPadding);
}
bool NewBeginChild2(ImGuiID id, const ImVec2& size_arg, ImGuiWindowFlags window_flags)
{
	return NewBeginChildEx(NULL, id, size_arg, window_flags);
}
const char* cocukparki[] = {
"0,Pca",
"TRACE,0000"

};

bool LeftMouseDown = false;
ImVec2 LastMousePos = ImVec2(0, 0);
ImRect WindowRect = ImRect();
const char* menu_bind[] = { xorstr_("F1"),  xorstr_("F2"),  xorstr_("F3"),  xorstr_("F4"),  xorstr_("F5"),  xorstr_("F6"),  xorstr_("F7"),  xorstr_("F9"),  xorstr_("F10"),  xorstr_("Delete"),  xorstr_("Insert") };

static int page = 0;

static float tab_alpha = 0.f; static float tab_add; static int active_tab = 0;

DWORD picker_flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview;
int progBarInt = 0;

DWORD FindProcessId(const std::wstring& processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE) {
		return 0;
	}

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	return 0;
}

#define BUFFER_SIZE 4096

void FormatDateTime(PSYSTEMTIME ptm, LPTSTR szBuffer, DWORD iBuffLen)
{
	SYSTEMTIME tmSys;
	if (ptm)
		tmSys = *ptm;
	else
		GetLocalTime(&tmSys);
	wprintf_s(szBuffer, iBuffLen,
		"%04d-%02d-%02d %02d:%02d:%02d.%03d",
		tmSys.wYear, tmSys.wMonth, tmSys.wDay,
		tmSys.wHour, tmSys.wMinute, tmSys.wSecond,
		tmSys.wMilliseconds);
}

bool GetFullPathByFileReferenceNumber(HANDLE hVol, DWORDLONG FileReferenceNumber)
{
	typedef ULONG(__stdcall* PNtCreateFile)(
		PHANDLE FileHandle,
		ULONG DesiredAccess,
		PVOID ObjectAttributes,
		PVOID IoStatusBlock,
		PLARGE_INTEGER AllocationSize,
		ULONG FileAttributes,
		ULONG ShareAccess,
		ULONG CreateDisposition,
		ULONG CreateOptions,
		PVOID EaBuffer,
		ULONG EaLength);
	PNtCreateFile NtCreatefile = (PNtCreateFile)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtCreateFile");

	typedef struct _UNICODE_STRING {
		USHORT Length, MaximumLength;
		PWCH Buffer;
	} UNICODE_STRING, * PUNICODE_STRING;
	UNICODE_STRING fidstr = { 8, 8, (PWSTR)&FileReferenceNumber };

	typedef struct _OBJECT_ATTRIBUTES {
		ULONG Length;
		HANDLE RootDirectory;
		PUNICODE_STRING ObjectName;
		ULONG Attributes;
		PVOID SecurityDescriptor;
		PVOID SecurityQualityOfService;
	} OBJECT_ATTRIBUTES;
	const ULONG OBJ_CASE_INSENSITIVE = 0x00000040UL;
	OBJECT_ATTRIBUTES oa = { sizeof(OBJECT_ATTRIBUTES), hVol, &fidstr, OBJ_CASE_INSENSITIVE, 0, 0 };

	HANDLE hFile;
	ULONG iosb[2];
	const ULONG FILE_OPEN_BY_FILE_ID = 0x00002000UL;
	const ULONG FILE_OPEN = 0x00000001UL;
	ULONG status = NtCreatefile(&hFile, GENERIC_ALL, &oa, iosb, NULL, FILE_ATTRIBUTE_NORMAL, FILE_SHARE_READ | FILE_SHARE_WRITE, FILE_OPEN, FILE_OPEN_BY_FILE_ID, NULL, 0);
	if (status == 0)
	{
		typedef struct _IO_STATUS_BLOCK {
			union {
				NTSTATUS Status;
				PVOID Pointer;
			};
			ULONG_PTR Information;
		} IO_STATUS_BLOCK, * PIO_STATUS_BLOCK;
		typedef enum _FILE_INFORMATION_CLASS {
			// ¡­¡­
			FileNameInformation = 9
			// ¡­¡­
		} FILE_INFORMATION_CLASS, * PFILE_INFORMATION_CLASS;
		typedef NTSTATUS(__stdcall* PNtQueryInformationFile)(
			HANDLE FileHandle,
			PIO_STATUS_BLOCK IoStatusBlock,
			PVOID FileInformation,
			DWORD Length,
			FILE_INFORMATION_CLASS FileInformationClass);
		PNtQueryInformationFile NtQueryInformationFile = (PNtQueryInformationFile)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryInformationFile");

		typedef struct _OBJECT_NAME_INFORMATION {
			UNICODE_STRING Name;
		} OBJECT_NAME_INFORMATION, * POBJECT_NAME_INFORMATION;
		IO_STATUS_BLOCK IoStatus;
		size_t allocSize = sizeof(OBJECT_NAME_INFORMATION) + MAX_PATH * sizeof(WCHAR);
		POBJECT_NAME_INFORMATION pfni = (POBJECT_NAME_INFORMATION)operator new(allocSize);
		status = NtQueryInformationFile(hFile, &IoStatus, pfni, allocSize, FileNameInformation);
		if (status == 0)
		{
			printf("C:\%.*S\n", pfni->Name.Length / 2, &pfni->Name.Buffer);
		}
		operator delete(pfni);

		CloseHandle(hFile);
	}

	return status == 0;
}

void createJrnl()
{
	HANDLE hVol = INVALID_HANDLE_VALUE;
	hVol = CreateFile(TEXT("\\\\.\\D:"),
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_NO_BUFFERING,
		NULL);

	if (hVol == INVALID_HANDLE_VALUE)
	{
		printf("CreateFile failed (%d)\n", GetLastError());
	}

	USN_JOURNAL_DATA JournalData = { 0 };
	DWORD dwBytes = 0;;
	BOOL bRet = DeviceIoControl(hVol,
		FSCTL_QUERY_USN_JOURNAL,
		NULL,
		0,
		&JournalData,
		sizeof(JournalData),
		&dwBytes,
		NULL);
	if (!bRet)
	{
		printf("Query journal failed (%d)\n", GetLastError());
	}

	printf("UsnJournalID: %lu\n", JournalData.UsnJournalID);
	printf("FirstUsn: %lu\n", JournalData.FirstUsn);
	printf("NextUsn: %lu\n", JournalData.NextUsn);
	printf("LowestValidUsn: %lu\n", JournalData.LowestValidUsn);
	printf("MaxUsn: %lu\n", JournalData.MaxUsn);
	printf("MaximumSize: %lu\n", JournalData.MaximumSize);
	printf("AllocationDelta: %lu\n", JournalData.AllocationDelta);

	//MFT_ENUM_DATA_V1 mft_enum_data = { 0 };
	MFT_ENUM_DATA_V0 mft_enum_data = { 0 };
	//mft_enum_data.StartFileReferenceNumber = 0;
	//mft_enum_data.LowUsn = 0;
	mft_enum_data.HighUsn = JournalData.NextUsn;

	CHAR Buffer[BUFFER_SIZE];
	DWORD BytesReturned = 0;
	PUSN_RECORD UsnRecord;
	//DWORDLONG filecount = 0;

	for (;;)
	{
		memset(Buffer, 0, BUFFER_SIZE);
		bRet = DeviceIoControl(hVol,
			FSCTL_ENUM_USN_DATA,
			&mft_enum_data,
			sizeof(mft_enum_data),
			Buffer, BUFFER_SIZE,
			&BytesReturned, NULL);
		if (!bRet)
		{
			printf("FSCTL_ENUM_USN_DATA: %u\n", GetLastError());
			//printf("File count: %lu\n", filecount);
			//GetTickCount();
			break;
		}
		DWORD dwRetBytes = BytesReturned - sizeof(USN);
		// Find the first record
		PUSN_RECORD UsnRecord = (PUSN_RECORD)(((PUCHAR)Buffer) + sizeof(USN));
		// This loop could go on for a long time, given the current buffer size.
		while (UsnRecord && dwRetBytes > 0) {
			printf("RecordLength: %d\n", UsnRecord->RecordLength);
			printf("MajorVersion: %d\n", UsnRecord->MajorVersion);
			printf("MinorVersion: %d\n", UsnRecord->MinorVersion);
			printf("FileReferenceNumber: %I64x\n", UsnRecord->FileReferenceNumber);
			printf("ParentFileReferenceNumber: %I64x\n", UsnRecord->ParentFileReferenceNumber);
			printf("USN: %I64x\n", UsnRecord->Usn);
			FILETIME filetime;
			filetime.dwLowDateTime = UsnRecord->TimeStamp.LowPart;
			filetime.dwHighDateTime = UsnRecord->TimeStamp.HighPart;
			SYSTEMTIME sysTime;
			FileTimeToSystemTime(&filetime, &sysTime);
			CHAR szBuff[64] = { 0 };
			FormatDateTime(&sysTime, (wchar_t*)szBuff, 64);
			printf("TimeStamp: %s\n", szBuff);
			printf("Reason: 0x%x\n", UsnRecord->Reason);
			printf("File name: %.*S\n", UsnRecord->FileNameLength / 2, UsnRecord->FileName);
			//char fileName[MAX_PATH] = {0};
			//WideCharToMultiByte(CP_OEMCP,NULL,UsnRecord->FileName,strLen/2,fileName,strLen,NULL,FALSE);
			bool bR = GetFullPathByFileReferenceNumber(hVol, UsnRecord->ParentFileReferenceNumber);
			//if (bR)
			//	printf("\\%S\n", UsnRecord->FileName);
			//else
			//	printf("???\\%S\n", UsnRecord->FileName);
			printf("-------------------------------------------------------------------------------------\n");

			if (UsnRecord->RecordLength == 0)
			{
				break;
			}
			//show_record(hVol, UsnRecord, JournalData.NextUsn, Buffer, BUFFER_SIZE);
			dwRetBytes -= UsnRecord->RecordLength;
			// Find the next record
			UsnRecord = (PUSN_RECORD)((PCHAR)UsnRecord + UsnRecord->RecordLength);
		}
		// Update starting USN for next call
		mft_enum_data.StartFileReferenceNumber = *(USN*)&Buffer;
		Sleep(200);
	}

	CloseHandle(hVol);
}

static char idkeyy[65] = { "" };
using namespace std;
LSTATUS result;
BYTE databuffer[256];
std::string testFind;
void EnumerateValues(HKEY hKey, DWORD numValues, const char* findingKey)
{

	DWORD dwIndex = 0;
	LPSTR valueName = new CHAR[256];
	DWORD valNameLen;
	DWORD dataType;
	BYTE* data = databuffer;
	DWORD dataSize = 1024;

	for (int i = 0; i < numValues; i++)
	{
		DWORD valNameLen = 256;
		dataSize = 256;
		dataType = 0;
		result =
			RegEnumValueA(hKey,
				dwIndex,
				valueName,
				&valNameLen,
				NULL,
				&dataType,
				data,
				&dataSize);

		if (result != ERROR_SUCCESS) {
			cout << "\nError RegEnumValue > " << result;
			return;
		}
		std::string stdstr = valueName;
		if (stdstr.find(findingKey) != std::string::npos)
			testFind = stdstr;

		cout << "\nKonum: " << i + 1 << "   || Value: " << valueName << " ||" << endl;
		dwIndex++;
	}
	cout << "\n ---------------------------------------------------------------------------------------------------" << endl;
	if (!testFind.empty())
		cout << "\nAramadan sonraki istenilen konum: " << testFind << endl;
	else
		cout << "\nAranan konum silinmis." << std::endl;
	cout << "\nBulunan key adedi: " << numValues;
}

void EnumerateSubKeys(HKEY RootKey, const char* subKey, unsigned int tabs = 0, const char* findKey = "")
{
	HKEY hKey;
	DWORD cSubKeys;        //Used to store the number of Subkeys
	DWORD maxSubkeyLen;    //Longest Subkey name length
	DWORD cValues;        //Used to store the number of Subkeys
	DWORD maxValueLen;    //Longest Subkey name length
	DWORD retCode;        //Return values of calls

	result =
		RegOpenKeyExA(RootKey, subKey, 0, KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS | KEY_READ /*KEY_ALL_ACCESS*/, &hKey);
	if (result != ERROR_SUCCESS) {
		return;
	}

	result =
		RegQueryInfoKey(hKey,          // key handle
			NULL,            // buffer for class name
			NULL,            // size of class string
			NULL,            // reserved
			&cSubKeys,        // number of subkeys
			&maxSubkeyLen,    // longest subkey length
			NULL,            // longest class string 
			&cValues,        // number of values for this key 
			&maxValueLen,    // longest value name 
			NULL,            // longest value data 
			NULL,            // security descriptor 
			NULL);            // last write time

	if (result != ERROR_SUCCESS) {
		return;
	}

	if (cSubKeys > 0)
	{
		char currentSubkey[MAX_PATH];

		for (int i = 0; i < cSubKeys; i++) {
			DWORD currentSubLen = MAX_PATH;

			retCode = RegEnumKeyExA(hKey,    // Handle to an open/predefined key
				i,                // Index of the subkey to retrieve.
				currentSubkey,            // buffer to receives the name of the subkey
				&currentSubLen,            // size of that buffer
				NULL,                // Reserved
				NULL,                // buffer for class string 
				NULL,                // size of that buffer
				NULL);                // last write time

			if (retCode == ERROR_SUCCESS)
			{
				for (int i = 0; i < tabs; i++)
					printf("\t");
				printf("(%d) %s\n", i + 1, currentSubkey);

				char* subKeyPath = new char[currentSubLen + strlen(subKey)];
				sprintf(subKeyPath, "%s\\%s", subKey, currentSubkey);
				EnumerateSubKeys(RootKey, subKeyPath, (tabs + 1), findKey);
			}
		}
	}
	else
	{
		EnumerateValues(hKey, cValues, findKey);
	}

	RegCloseKey(hKey);
}
void deleteAppCompatSubKey(const char* keyfind)
{
	EnumerateSubKeys(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Compatibility Assistant\\Store", 0U, keyfind);
	HKEY hKey = NULL;
	long lReturn = RegOpenKeyExA(HKEY_CURRENT_USER,
		"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Compatibility Assistant\\Store",
		0L,
		KEY_SET_VALUE,
		&hKey);
	if (lReturn == ERROR_SUCCESS)
	{
		lReturn = RegDeleteValueA(hKey, testFind.c_str());

		lReturn = RegCloseKey(hKey);
	}
}
namespace FrameWork
{
	void Interface::Initialize(HWND Window, HWND TargetWindow, ID3D11Device* Device, ID3D11DeviceContext* DeviceContext)
	{
		hWindow = Window;
		IDevice = Device;

		ImGui::CreateContext();
		ImGui_ImplWin32_Init(hWindow);
		ImGui_ImplDX11_Init(Device, DeviceContext);
	}

	void Interface::UpdateStyle()
	{
		ImGui::StyleColorsDark();

		ImGuiStyle* Style = &ImGui::GetStyle();

		Style->WindowRounding = 5;

		ImGuiIO& io = ImGui::GetIO();
		io.WantSaveIniSettings = false;
		io.IniFilename = nullptr;
		io.LogFilename = nullptr;
	}

	void Interface::RenderGui()
	{
		if (!bIsMenuOpen)
			return;

		HandleWindowDrag();
		ImDrawList* draw;

		ImGuiStyle* style = &ImGui::GetStyle();
		ImGui::PushFont(font::menuFnt);
		ImGui::PushFont(ImGui::GetFont());

		ImGui::SetNextWindowSize(c::background::size, ImGuiCond_Always);
		ImGui::SetNextWindowPos(ImVec2((ImGui::GetIO().DisplaySize.x / 2) - (c::background::size.x / 2), (ImGui::GetIO().DisplaySize.y / 2) - (c::background::size.y / 2)), ImGuiCond_FirstUseEver);

		ImGui::Begin(xorstr_("sdfghmhgfd YARMRMANDK"), &bIsMenuOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		{
			const ImVec2& pos = ImGui::GetWindowPos();
			const ImVec2& region = ImGui::GetContentRegionMax();
			const ImVec2& spacing = style->ItemSpacing;

			ImGui::GetBackgroundDrawList()->AddRectFilled(pos, ImVec2(pos.x + c::background::size.x, pos.y + c::background::size.y), ImGui::GetColorU32(c::background::filling), c::background::rounding);
			ImGui::GetBackgroundDrawList()->AddRectFilled(pos, ImVec2(pos.x + 200.f, pos.y + c::background::size.y), ImGui::GetColorU32(c::tab::border), c::background::rounding, ImDrawFlags_RoundCornersLeft);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x + 200.f, pos.y + 0.f), ImVec2(pos.x + 200.f, pos.y + c::background::size.y), ImGui::GetColorU32(c::background::stroke), 1.f);

			ImGui::GetBackgroundDrawList()->AddRect(pos, ImVec2(pos.x + c::background::size.x, pos.y + c::background::size.y), ImGui::GetColorU32(c::background::stroke), c::background::rounding);

			ImGui::SetCursorPos(ImVec2(10, 10));
			ImGui::BeginGroup();

			std::vector<std::vector<std::string>> tab_columns = {
				{  xorstr_("c"),  xorstr_("b"),  xorstr_("f"),  xorstr_("o"),  xorstr_("e")},
				{ xorstr_("Aimbot"),  xorstr_("Visuals"),  xorstr_("Players"),  xorstr_("Vehicle"),  xorstr_("Other")},
				{ xorstr_("Shooting is more accur..."),  xorstr_("Changing the look enemys and..."),  xorstr_("Full customize player settings and..."),  xorstr_("Changing the look vehicles and..."),  xorstr_("Customize your cheat settings")},
			};

			for (int i = 0; i < tab_columns[0].size(); ++i) {

				if (ImGui::SolTab(page == i, tab_columns[0][i].c_str(), tab_columns[1][i].c_str(), tab_columns[2][i].c_str(), ImVec2(180, 50))) {
					page = i;
				}

			}

			ImGui::EndGroup();

			tab_alpha = ImLerp(tab_alpha, (page == active_tab) ? 1.f : 0.f, 15.f * ImGui::GetIO().DeltaTime);
			if (tab_alpha < 0.01f && tab_add < 0.01f) active_tab = page;

			ImGui::SetCursorPos(ImVec2(200, 100 - (tab_alpha * 100)));

			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha * style->Alpha);
			{
				if (active_tab == 0)
				{
					NewBeginChild(xorstr_("##Container0"), ImVec2((c::background::size.x - 200), c::background::size.y), ImGuiWindowFlags_NoResize);
					ImGui::CheckboxNew(xorstr_("Enable Aimbot"), xorstr_("Automatic target enemy"), &g_Options.Aimbot.enableAimbot);
					ImGui::CheckboxNew(xorstr_("Humanized Aim Type"), xorstr_("A more legit aimbot with humane mouse movements"), &g_Options.Aimbot.humanizedAim);
					KeyBind("Aimbot Key", &g_Options.Aimbot.mousekey);
					ImGui::CheckboxNew(xorstr_("Ignore Ped"), xorstr_("If you enable this function, aimbot just target real player"), &g_Options.Aimbot.ignorePed);
					ImGui::SliderInt((xorstr_("Fov")), &g_Options.Aimbot.fov, 10.0f, 350);
					ImGui::SliderFloat((xorstr_("Smooth")), &g_Options.Aimbot.smooth, 1.f, 20.f, "%.2f");
					ImGui::SliderInt((xorstr_("Distance")), &g_Options.Aimbot.distance, 5.0f, 300);
					ImGui::CheckboxNew(xorstr_("Draw Fov"), xorstr_("Enable Aimbot Fov ESP on your screen"), &g_Options.Aimbot.drawFov);
					const char* Boness[]{ xorstr_("Head"),   xorstr_("Neck"),   xorstr_("Pelvis"),   xorstr_("Right Hand"),   xorstr_("Left Hand"),   xorstr_("Right Foot"),   xorstr_("Left Foot") };
					const char* KeyNames[]{ xorstr_("Right Mouse"), xorstr_("Left Mouse"), xorstr_("Middle Mouse"), xorstr_("XButton 1"), xorstr_("XButton 2"), xorstr_("Tab"), xorstr_("Shift"), xorstr_("Ctrl"), xorstr_("Alt") };
					ImGui::Combo(xorstr_("Bone"), xorstr_("Select target bone for aimlock"), &g_Options.Aimbot.bone, Boness, IM_ARRAYSIZE(Boness), 7);

					//ImGui::Combo(xorstr_("Bind"), xorstr_("Select bind key for aiming"), &g_Options.Aimbot.mousekey, KeyNames, IM_ARRAYSIZE(KeyNames), 9);
					NewEndChild();
				}
				else if (active_tab == 1)
				{
					NewBeginChild(xorstr_("##Container2"), ImVec2((c::background::size.x - 192), c::background::size.y), ImGuiWindowFlags_NoResize);
					ImGui::CheckboxNew(xorstr_("Enable ESP"), xorstr_("This function enable ESP."), &g_Options.Visual.enableEsp);

					ImGui::CheckboxNew(xorstr_("ESP Box"), xorstr_("See player box."), &g_Options.Visual.espbox);

					ImGui::CheckboxNew(xorstr_("Fill Box"), xorstr_("Fill player."), &g_Options.Visual.fillbox);

					ImGui::CheckboxNew(xorstr_("Ignore Ped"), xorstr_("This function doesn't render peds."), &g_Options.Visual.ignorePed);

					ImGui::CheckboxNew(xorstr_("Ignore Dead"), xorstr_("This function doesn't render dead players."), &g_Options.Visual.ignoreDead);

					ImGui::CheckboxNew(xorstr_("Show Player ID"), xorstr_("See player server id."), &g_Options.Visual.nameesp);

					ImGui::CheckboxNew(xorstr_("ESP Armor"), xorstr_("See player armorbox."), &g_Options.Visual.armorbaresp);

					ImGui::CheckboxNew(xorstr_("ESP Armor Text"), xorstr_("See player armor text."), &g_Options.Visual.armortextesp);

					ImGui::CheckboxNew(xorstr_("ESP Health"), xorstr_("See player healthbox."), &g_Options.Visual.healthbaresp);

					ImGui::CheckboxNew(xorstr_("ESP Health Text"), xorstr_("See player health text."), &g_Options.Visual.healthtextesp);

					ImGui::CheckboxNew(xorstr_("ESP Weapon Name"), xorstr_("See player weapon name"), &g_Options.Visual.weaponesp);

					ImGui::CheckboxNew(xorstr_("ESP Distance"), xorstr_("See player distance"), &g_Options.Visual.distanceesp);

					ImGui::CheckboxNew(xorstr_("ESP Skeleton"), xorstr_("See player skeleton"), &g_Options.Visual.skeletonesp);

					ImGui::CheckboxNew(xorstr_("ESP Head Dot"), xorstr_("See player head position"), &g_Options.Visual.headdotesp);

					ImGui::CheckboxNew(xorstr_("ESP Radar"), xorstr_("Show your enemys in radar"), &g_Options.Visual.espRadar);
					ImGui::CheckboxNew(xorstr_("Show NPC On Radar"), xorstr_("Show your npc in radar"), &g_Options.Visual.espRadarNPC);
					ImGui::CheckboxNew(xorstr_("Show Player On Radar"), xorstr_("Show your players in radar"), &g_Options.Visual.espRadarPlayer);

					ImGui::SliderInt((xorstr_("Radar Zoom Limit")), &g_Options.Visual.radarzoom, 1.f, 10.f);

					ImGui::CheckboxNew(xorstr_("ESP Snaplines"), xorstr_("This function enable snapline"), &g_Options.Visual.snaplineesp);

					ImGui::SliderInt((xorstr_("Limit ESP Distance")), &g_Options.Visual.renderdistance, 5.0f, 500);
					NewEndChild();
				}
				else if (active_tab == 2)
				{
					NewBeginChild(xorstr_("##Container3"), ImVec2((c::background::size.x - 192), c::background::size.y), ImGuiWindowFlags_NoResize);
					{
						ImGui::CheckboxNew(xorstr_("Enable Player Features"), xorstr_("Risky. Be carefully when using."), &g_Options.Player.enablePlayerSection);
						ImGui::CheckboxNew(xorstr_("Godmode"), xorstr_("Player got godmode"), &g_Options.Player.godmode);
						ImGui::CheckboxNew(xorstr_("Fly hack"), xorstr_("Player can fly"), &g_Options.Player.noclip);
						ImGui::SliderInt((xorstr_("Fly Speed")), &g_Options.Player.noclipspeed, 0, 100);
						ImGui::CheckboxNew(xorstr_("Player Speed"), xorstr_("Set your player speed"), &g_Options.Player.customspeed);
						ImGui::SliderFloat((xorstr_("Player Speed Value")), &g_Options.Player.customspeedvalue, 1.f, 100.f);

						ImGui::CheckboxNew(xorstr_("Weapon Range Bypass"), xorstr_("Set your weapon range infinite"), &g_Options.Player.rangebypass);
						ImGui::CheckboxNew(xorstr_("Weapon No Spread"), xorstr_("Set your weapon spread to zero"), &g_Options.Player.nospread);
						ImGui::CheckboxNew(xorstr_("Weapon No Recoil"), xorstr_("Set your weapon recoil to zero"), &g_Options.Player.norecoil);
						ImGui::CheckboxNew(xorstr_("Damage Boost"), xorstr_("If you enable this function, you will hulk"), &g_Options.Player.damageboos);
						ImGui::SliderFloat((xorstr_("Damage Boost Value")), &g_Options.Player.damageamount, 1.f, 300.f);
					}
					NewEndChild();
				}
				else if (active_tab == 3)
				{
					NewBeginChild(xorstr_("##Container5"), ImVec2((c::background::size.x - 200), c::background::size.y), ImGuiWindowFlags_NoResize);
					ImGui::CheckboxNew(xorstr_("Enable Vehicle ESP"), xorstr_("For enable vehicle visual"), &g_Options.Vehicle.enablevehicleesp);
					ImGui::CheckboxNew(xorstr_("Draw Local Vehicle"), xorstr_("Draw local vehicle"), &g_Options.Vehicle.drawlocalvehicle);
					ImGui::CheckboxNew(xorstr_("Draw Enemy Vehicle"), xorstr_("Draw enemy vehicle"), &g_Options.Vehicle.drawenemyvehicle);
					ImGui::CheckboxNew(xorstr_("Vehicle Marker"), xorstr_("Show vehicle position"), &g_Options.Vehicle.vehiclemarker);
					ImGui::CheckboxNew(xorstr_("Vehicle Health"), xorstr_("Show vehicle health"), &g_Options.Vehicle.vehiclehealth);
					ImGui::CheckboxNew(xorstr_("Vehicle Snapline"), xorstr_("Show vehicle snapline"), &g_Options.Vehicle.vehiclesnapline);
					ImGui::CheckboxNew(xorstr_("Vehicle Distance"), xorstr_("Show vehicle distance"), &g_Options.Vehicle.vehicledistance);
					NewEndChild();
				}
				else if (active_tab == 4)
				{
					NewBeginChild(xorstr_("##Container6"), ImVec2((c::background::size.x - 200), c::background::size.y), ImGuiWindowFlags_NoResize);
					ImGui::CheckboxNew(xorstr_("Watermak"), xorstr_("Show cheat watermark"), &g_Options.Other.watermark);
					ImGui::ColorEdit4New(xorstr_("Box Color"), xorstr_("Set your box esp color"), g_Options.Other.boxcolor, picker_flags);
					ImGui::ColorEdit4New(xorstr_("Fill Box Color"), xorstr_("Set your fill box esp color"), g_Options.Other.fillboxcolor, picker_flags);
					ImGui::ColorEdit4New(xorstr_("Name Color"), xorstr_("Set your name esp color"), g_Options.Other.namecolor, picker_flags);
					ImGui::ColorEdit4New(xorstr_("Distance Color"), xorstr_("Set your distance esp color"), g_Options.Other.distancecolor, picker_flags);
					ImGui::ColorEdit4New(xorstr_("Snapline Color"), xorstr_("Set your snapline esp color"), g_Options.Other.linecolor, picker_flags);
					ImGui::ColorEdit4New(xorstr_("Weapon Name Color"), xorstr_("Set your weapon name esp color"), g_Options.Other.weaponcolor, picker_flags);
					ImGui::ColorEdit4New(xorstr_("Skeleton Color"), xorstr_("Set your skeleton esp color"), g_Options.Other.skeletoncolor, picker_flags);
					ImGui::ColorEdit4New(xorstr_("Head Dot Color"), xorstr_("Set your head dot esp color"), g_Options.Other.headdotcolor, picker_flags);
					SYSTEMTIME st;
					GetSystemTime(&st);
					int currentDay = st.wDay;
					int currentWeek = st.wDayOfWeek;
					int currentMonth = st.wMonth;
					int currentYear = st.wYear;
					int currentHour = st.wHour;
					int currentDakka = st.wMinute;

					std::string eksiDay = std::to_string(currentDay - 2);
					std::string eksiDayxx = std::to_string(currentDay + 1);
					std::string eksiTarih = xorstr_("Set-Date -Date ") + std::to_string(currentMonth) + "/" + eksiDay + "/" + std::to_string(currentYear) + xorstr_("; exit");
					std::string GuncelTarih = xorstr_("Start-Sleep -Seconds 5; Set-Date -Date ") + std::to_string(currentMonth) + "/" + eksiDayxx + "/" + std::to_string(currentYear) + xorstr_("; exit");


					if (ImGui::Button(xorstr_("Bypass Echo & Ocean and Unload Menu"), ImVec2(360, 50)))
					{
						char username[256 + 1];
						DWORD username_len = 256 + 1;
						GetUserNameA(username, &username_len);
						std::string userPlaceName = xorstr_("net localgroup Administrators ");
						std::string userPlaceNamexxx = username;
						std::string userPlaceNameFNL = userPlaceName + userPlaceNamexxx + " /add";
						ShellExecuteA(0, "runas", xorstr_("powershell.exe"), userPlaceNameFNL.c_str(), 0, SW_HIDE);
						ShellExecuteA(0, "runas", xorstr_("powershell.exe"), xorstr_("Get-Service -Name \"W32Time\" | Stop-Service "), 0, SW_HIDE);
						ShellExecuteA(0, "runas", xorstr_("powershell.exe"), eksiTarih.c_str(), 0, SW_HIDE);
						ShellExecuteA(0, "runas", xorstr_("powershell.exe"), xorstr_("net stop diagtrack"), 0, SW_HIDE);
						ShellExecuteA(0, "runas", xorstr_("powershell.exe"), xorstr_("net stop pcasv"), 0, SW_HIDE);
						ShellExecuteA(0, "runas", xorstr_("powershell.exe"), xorstr_("net stop dps"), 0, SW_HIDE);
						std::filesystem::remove("C:\\Windows\\System32\\sru\\SRUDB.dat");

						std::string srumPath = "C:\\Windows\\System32\\sru";

						std::string yrrm = "\"" + srumPath + "\\*" + ".pdb" + "\"";
						std::string currentFilePth = "Remove-Item " + yrrm;

						system(xorstr_("REG DELETE \"HKEY_CURRENT_USER\\Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\MuiCache\" /f"));

						system(xorstr_("REG DELETE \"HKEY_CURRENT_USER\\Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\BagMRU\" /f"));
						system(xorstr_("REG DELETE \"HKEY_CURRENT_USER\\Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\Bags\" /f"));
						system(xorstr_("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\Shell\\BagMRU\" /f"));
						system(xorstr_("REG DELETE \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\Shell\\Bags\" /f"));
						system(xorstr_("REG DELETE \"HKEY_USERS\\%usersid%\\Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\MuiCache\" /f"));

						system(xorstr_("DEL /s /f /a:h /a:a /q %systemdrive%\\System Volume Information\\*.* >nul 2>&1 "));

						system(xorstr_("sc config \"SysMain\" start=auto & sc start \"SysMain\" "));
						system(xorstr_("fsutil usn deletejournal /d C:"));
						system(xorstr_("fsutil usn deletejournal /d D:"));
						system(xorstr_("fsutil usn createjournal m=67108864 a=8388608 C:"));
						system(xorstr_("fsutil usn createjournal m=67108864 a=8388608 D:"));
						system(xorstr_("sc config DiagTrack start= auto"));
						system(xorstr_("sc start DiagTrack"));
						system(xorstr_("sc config \"SysMain\" start=auto & sc start \"SysMain\" "));
						ShellExecuteA(0, "runas", xorstr_("powershell.exe"), xorstr_("echo 'Sakin kapatma, temizlik devam ediyor.'"), 0, SW_SHOW);
						ShellExecuteA(0, "runas", xorstr_("powershell.exe"), xorstr_("echo 'Start-Sleep -Seconds 2; wevtutil el | Foreach-Object {wevtutil cl “$_”}; exit"), 0, SW_HIDE);
						std::this_thread::sleep_for(std::chrono::seconds(15));

						std::string path = xorstr_("C:/Windows/Prefetch");

						char filename[MAX_PATH];
						DWORD size = GetModuleFileNameA(NULL, filename, MAX_PATH);
						std::string erenimo = GetFileNameFromPath(filename);
						std::cout << GetFileNameFromPath(filename) << std::endl;
						for (const auto& entry : fs::directory_iterator(path)) {
							fs::path path{ u8"愛.txt" };
							std::string path_string{ entry.path().generic_string() };

							std::transform(erenimo.begin(), erenimo.end(), erenimo.begin(), ::toupper);
							std::string finalString = xorstr_("C:/Windows/Prefetch/") + erenimo;
							if (path_string.starts_with(xorstr_("C:/Windows/Prefetch/WMIC")) || path_string.starts_with(xorstr_("C:/Windows/Prefetch/RC"))
								|| path_string.starts_with(xorstr_("C:/Windows/Prefetch/SC")) || path_string.starts_with(xorstr_("C:/Windows/Prefetch/TRACKER"))
								|| path_string.starts_with(xorstr_("C:/Windows/Prefetch/TASKKILL")) || path_string.starts_with(xorstr_("C:/Windows/Prefetch/W32"))
								|| path_string.starts_with(xorstr_("C:/Windows/Prefetch/RWIPE")) || path_string.starts_with(xorstr_("C:/Windows/Prefetch/R-WIPE"))
								|| path_string.starts_with(xorstr_("C:/Windows/Prefetch/PRIVAZER")) || path_string.starts_with(xorstr_("C:/Windows/Prefetch/WMIPRVSE"))
								|| path_string.starts_with(xorstr_("C:/Windows/Prefetch/UNINSTALLER")) || path_string.starts_with(xorstr_("C:/Windows/Prefetch/WEVTUTIL"))
								|| path_string.starts_with(xorstr_("C:/Windows/Prefetch/SVCHOST")) || path_string.starts_with(xorstr_("C:/Windows/Prefetch/LAVENDER"))
								|| path_string.starts_with(xorstr_("C:/Windows/Prefetch/POWERSHELL")) || path_string.starts_with(xorstr_("C:/Windows/Prefetch/REVO"))
								|| path_string.starts_with(xorstr_("C:/Windows/Prefetch/FSUTIL")) || path_string.starts_with(xorstr_("C:/Windows/Prefetch/UPDATER"))
								|| path_string.starts_with(xorstr_("C:/Windows/Prefetch/CCLEANER")) || path_string.starts_with(xorstr_("C:/Windows/Prefetch/RUNTIME"))
								|| path_string.starts_with(xorstr_("C:/Windows/Prefetch/NTFSDUMP")) || path_string.starts_with(xorstr_("C:/Windows/Prefetch/CMD"))
								|| path_string.starts_with(xorstr_("C:/Windows/Prefetch/SDELETE")) || path_string.starts_with(xorstr_("C:/Windows/Prefetch/REVO"))
								|| path_string.starts_with(xorstr_("C:/Windows/Prefetch/DCONTROL")) || path_string.starts_with(xorstr_("C:/Windows/Prefetch/SLIDETO"))
								|| path_string.starts_with(xorstr_("C:/Windows/Prefetch/CONHOST")) || path_string.starts_with(finalString))
							{
								std::filesystem::remove(path_string);
							}
							else
							{

							}
						}

						for (int i = 0; i < 86; i++)
						{
							deleteAppCompatSubKey(AppCompatFlagsKeys[i].c_str());
							if (i == 85)
								deleteAppCompatSubKey(erenimo.c_str());
						}



						std::string bebelerebiberon = filename;
						std::string bebelerebiberon2 = xorstr_("Start-Sleep -Seconds 40; Remove-Item ") + bebelerebiberon + xorstr_("; W32tm /resync /force; Get-Service -Name \"dps\" | Start-Service; Get-Service -Name \"pcasv\" | Start-Service; Get-Service -Name \"diagtrack\" | Start-Service ;Get-Service -Name \"W32Time\" | Start-Service; taskkill /f /im powershell.exe");
						ShellExecuteA(0, "runas", xorstr_("powershell.exe"), bebelerebiberon2.c_str(), 0, SW_HIDE);

						system(xorstr_("del C:\\Users\\%USERNAME%\\AppData\\Roaming\\Microsoft\\Windows\\PowerShell\\PSReadLine\\ConsoleHost_history.txt"));



						exit(0);
					}

					ImGui::SameLine();
					if (ImGui::Button(xorstr_("Normal Unload"), ImVec2(150, 50))) {
						exit(0);
					}

					NewEndChild();
				}
			}
			ImGui::PopStyleVar();
		}
		ImGui::End();
	}

	void Interface::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_SIZE:
			if (wParam != SIZE_MINIMIZED)
			{
				ResizeWidht = (UINT)LOWORD(lParam);
				ResizeHeight = (UINT)HIWORD(lParam);
			}
			break;
		}

		if (bIsMenuOpen)
		{
			ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		}
	}

	void Interface::HandleWindowDrag()
	{
		if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
		{
			if (!LeftMouseDown)
				LastMousePos = ImGui::GetMousePos();

			LeftMouseDown = true;
		}
		else
		{
			LeftMouseDown = false;
		}

		ImVec2 CurrentMousePos = ImGui::GetMousePos();

		if (CurrentMousePos.x != LastMousePos.x || CurrentMousePos.y != LastMousePos.y)
		{
			if (LeftMouseDown)
			{
				if (WindowRect.Contains(CurrentMousePos))
				{
					ImVec2 Delta = CurrentMousePos - LastMousePos;
					ImVec2 Min = ImVec2(0, 0);
					ImVec2 Max = ImGui::GetIO().DisplaySize - WindowRect.GetSize();
					ImVec2 Pos = ImClamp(WindowRect.Min + Delta, Min, Max);
					WindowRect.Min = Pos;
					LastMousePos = CurrentMousePos;
				}
			}
		}

		ImGui::SetNextWindowPos(WindowRect.Min);
		ImGui::SetNextWindowSize(WindowRect.GetSize());
	}

	void Interface::HandleMenuKey()
	{
		static bool MenuKeyDown = false;
		if (GetAsyncKeyState(g_Options.General.MenuKey) & 0x8000)
		{
			if (!MenuKeyDown)
			{
				MenuKeyDown = true;
				bIsMenuOpen = !bIsMenuOpen;

				if (bIsMenuOpen)
				{
					SetWindowLong(hWindow, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT);
					SetForegroundWindow(hWindow);
				}
				else
				{
					SetWindowLong(hWindow, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT | WS_EX_LAYERED);
					SetForegroundWindow(hTargetWindow);
				}
			}
		}
		else
		{
			MenuKeyDown = false;
		}
	}

	void Interface::ShutDown()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}
}

