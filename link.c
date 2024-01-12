#if 0
#include <stdio.h>
#include <Windows.h>

int main(int argc, char** argv)
{
    if (argc < 3) {
        fprintf(stderr, "USAGE: %s <existing file> <new file>\n", argv[0]);
        return 1;
    }

    // flag for creating symlink of a file
    DWORD flags = 0x0;

    if (GetFileAttributesA(argv[1]) == FILE_ATTRIBUTE_DIRECTORY) {
        flags = SYMBOLIC_LINK_FLAG_DIRECTORY;
    }

    if (!CreateSymbolicLinkA(argv[2], argv[1], flags)) {
        if (GetLastError() == 1314) {
            fprintf(stderr, "ERROR: Try again with administrator account\n");
            return 1;
        }
        fprintf(stderr, "ERROR: could not create symlink (%lu)\n", GetLastError());
        return 1;
    }

    printf("INFO: symlink created\n");

    printf("INFO: hard link created successfully.\n");

    system("PAUSE");
    return 0;
}

#endif