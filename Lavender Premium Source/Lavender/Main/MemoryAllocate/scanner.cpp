#include "scanner.h"

scanner::scanner(DWORD proccesid)
{
    GetSystemInfo(&si);
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, proccesid);
}

scanner::~scanner()
{
    CloseHandle(hProcess);
}

void scanner::scanstring(const std::string& stringtofind)
{
    while (currentmemorypage < si.lpMaximumApplicationAddress)
    {
        MEMORY_BASIC_INFORMATION info;
        if (VirtualQueryEx(hProcess, currentmemorypage, &info, sizeof(info)) == sizeof(info))
        {
            if (info.State == MEM_COMMIT && info.Protect == PAGE_READWRITE)
            {
                std::vector<char> buffer(info.RegionSize);
                SIZE_T bytesRead;
                if (ReadProcessMemory(hProcess, currentmemorypage, buffer.data(), info.RegionSize, &bytesRead))
                {
                    for (size_t begin = 0; begin <= bytesRead - stringtofind.size(); ++begin)
                    {
                        if (memcmp(buffer.data() + begin, stringtofind.c_str(), stringtofind.size()) == 0)
                        {
                            addres.push_back(reinterpret_cast<uintptr_t>(currentmemorypage) + begin);
                        }
                    }
                }
            }
            currentmemorypage = currentmemorypage + info.RegionSize;
        }
        else
        {
            break;
        }
    }
    currentmemorypage = 0;
}

std::string scanner::cleanstringstest(uintptr_t value)
{
    char buffer[256];
    ZwReadVirtualMemory(hProcess, (LPVOID)value, &buffer, sizeof(buffer) + 1, 0);
    return buffer;
}
void scanner::cleanstringseyvah(uintptr_t value)
{
    std::string replacestring = "";
    ZwWriteVirtualMemory(hProcess, (LPVOID)value, &replacestring.c_str()[0], replacestring.size() + 1, 0); // WRITE.
}

void scanner::cleanstrings()
{
    std::string replacestring = "";
    char buffer[7];
    for (auto& addresaddres : addres)
    {

        ZwReadVirtualMemory(hProcess, (LPVOID)addresaddres, &buffer, sizeof(buffer) + 1, 0);
        std::cout << std::hex << "addres found: " << " " << addresaddres << "\n";
        ZwWriteVirtualMemory(hProcess, (LPVOID)addresaddres, &replacestring.c_str()[0], replacestring.size() + 1, 0); // WRITE.
        ZwReadVirtualMemory(hProcess, (LPVOID)addresaddres, &buffer, sizeof(buffer) + 1, 0);
        std::cout << "memory addres string after writed to it: " << buffer << "\n";
    }
}

void scanner::debug(std::string printthatshit)
{
#ifdef debug
    std::cout << printthatshit << "\n";
#endif 
}

std::vector<uintptr_t> scanner::returnaddreses()
{
    return addres;
}