#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char * path_join(char *dest, const char *path1, const char *path2) {
    if (!dest) return NULL;

    if (path1 == NULL  && path2 == NULL) {
        strcpy(dest, "");
    } else if (path2 == NULL && strlen(path2) == 0) {
        strcpy(dest, path1);
    } else if (path1 == NULL && strlen(path1) == 0) {
        strcpy(dest, path2);
    } else {
        char sep = '/';
        int len1 = strlen(path1); //strlen(path1) - 1 + 1 (for null terminator)
        if (path1[len1 - 1] == sep && path2[0] == sep) { //if both have seperator...
            char temp[len1]; //temp array
            temp[len1 - 1] = '\0'; //make sure last element is null term.
            strncpy(temp, path1, len1 - 1); //copy everything but null term from first string to buffer.
            strncpy(dest, temp, len1 - 1); //copy everything but null term from buffer to dest
            strcpy((dest + len1) - 1 , path2); //copy contents of path2 to destination + offset of first string. -1 because we copied len1 - 1 characters, not the full length.

        } else if (path1[len1 - 1] == sep || (sep && path2[0] == sep)) { //if we have the separator in either but not both...
            strcpy(dest, path1);
            strcpy(dest + len1, path2);
        } else { //if neither has seperator...
            strcpy(dest, path1);
            strcpy(dest + len1, &sep);
            strcpy(dest + len1 + 1, path2);
        }
    }

    return dest;
}


