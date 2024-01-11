#if 0

#include <Windows.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("USAGE: %s <filename>\n", argv[0]);
        return 1;
    }

    HANDLE hFile = CreateFileA(
        argv[1],
        GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        switch (GetLastError())
        {
        case ERROR_FILE_EXISTS:
            printf("ERROR: File %s exists\n", argv[1]);
            break;
        default:
            printf("ERROR: could not create file (%lu)", GetLastError());
            break;
        }

        return 1;
    }

    printf("INFO: %s File is created successfully.\n", argv[1]);

    // writing to file
    char* strbuff = "Hello World!";
    DWORD bytesWritten, bytesToWrite = strlen(strbuff);

    BOOL bWrite = WriteFile(hFile, strbuff, bytesToWrite, &bytesWritten, NULL);

    if (bWrite) {
        printf("INFO: Buffer written to %s\n", argv[1]);
    }
    else if (bytesToWrite != bytesWritten) {
        fprintf(stderr, "ERROR: Bytes written != bytes to write.\nSuccessfully wrote %d bytes to %s\n", bytesWritten, argv[1]);
        return 1;
    }
    else {
        switch (GetLastError()) {
        default:
            fprintf(stderr, "ERROR: could not write to file (%lu)\n", GetLastError());
            CloseHandle(hFile);
            return 1;
        }
    }
    CloseHandle(hFile);

    // read from file
    hFile = CreateFileA(
        argv[1],
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    DWORD nToRead = 15;
    char chBuff[16];
    DWORD nRead;

    BOOL bRead = ReadFile(hFile, &chBuff, nToRead, &nRead, NULL);
    chBuff[15] = '\0';

    if (bRead) {
        printf("DATA: %s\n", chBuff);
    }
    else if (nToRead != nRead) {
        fprintf(stderr, "Number of bytes to read != number of bytes read\n");
    }
    else {
        switch (GetLastError()) {
        case ERROR_NOACCESS:
            fprintf(stderr, "ERROR: No access to read file '%s'\n", argv[1]);
            break;
        default:
            fprintf(stderr, "ERROR: could not read file '%s' (%lu)", argv[1], GetLastError());
        }
        CloseHandle(hFile);
        return 1;
    }

    CloseHandle(hFile);

    system("PAUSE");
    return 0;
}
#endif