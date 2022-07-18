#include <iostream>
#include <Windows.h>
#include <string.h>
#include <fstream>

int main() {
    unsigned int sector = 0;
    HANDLE drive = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    SetFilePointer(drive, sector*512, 0, FILE_BEGIN);

    DWORD dwRead;
    char buff[512];
    ReadFile(drive, *&buff, 512, &dwRead, 0);

    if(dwRead != 512) {
        std::cout << "ERROR \n";
        std::cout << "dumping to file mbr-save.out may be not correct!\n";
        std::cout << "make sure you are running as administrator to access \\\\.\\PhysicalDrive0\n";
        system("pause");
        return 0;
    }


    std::fstream mbr;
    mbr = std::fstream("mbr-save.bin", std::ios::out | std::ios::binary);

    mbr.write(buff, 512);
    mbr.close();

    CloseHandle(drive);

    std::cout << "success! mbr saved as 'mbr-save.bin' ";
    
    return 0;
}