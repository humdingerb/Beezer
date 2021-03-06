/*
 * Copyright (c) 2009, Ramshankar (aka Teknomancer)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * -> Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * -> Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * -> Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <Bitmap.h>
#include <Resources.h>
#include <Application.h>
#include <Roster.h>
#include <Directory.h>
#include <FindDirectory.h>
#include <Path.h>
#include <String.h>
#include <Locker.h>
#include <Debug.h>
#include <Autolock.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "AppUtils.h"

// Global object declares
BLocker _apputils_locker("_app_utils_lock", true);



BString StringFromBytes(int64 v)
{
    // Hacked from BeShare with minor changes -- many thanks to Jeremy Freisner,
    // Don't bother about holding calculated constants for 1024*1024.. etc. as it will be optimized
    // by the compiler
    BString str;
    if (v > -1)
    {
        char buf[50];
        if (v > (1024LL * 1024LL * 1024LL * 1024LL))
            sprintf(buf, "%.2f TiB", ((double)v) / (1024LL * 1024LL * 1024LL * 1024LL));
        else if (v > (1024LL * 1024LL * 1024LL))
            sprintf(buf, "%.2f GiB", ((double)v) / (1024LL * 1024LL * 1024LL));
        else if (v > (1024LL * 1024LL))
            sprintf(buf, "%.2f MiB", ((double)v) / (1024LL * 1024LL));
        else if (v > (1024LL))
            sprintf(buf, "%.2f KiB", ((double)v) / 1024LL);
        else
            sprintf(buf, "%Li bytes", v);

        str = buf;
    }
    else
        str = "-";

    return str;
}



int32 LastOccurrence(const char* str, char whatChar)
{
    // Move "str" to the last occurrence of "whatChar" also count and return number of occurrences
    int32 count = 0L;
    while (*str)
    {
        if (*str == whatChar)
            count++;

        str++;
    }

    return count;
}



int32 CountCharsInFront(char* str, char whatChar)
{
    // Simply count "whatChar"s in the beginning of "str" without modifying "str" pointer
    int32 count = 0;
    while (str[count] == ' ')
        count++;

    return count;
}



bool StrEndsWith(char* str, char* end)
{
    // Check if the given "str" ends with "end"
    *str += strlen(str) - strlen(end) - 2;
    if (strcmp(str, end) == 0)
        return true;
    else
        return false;
}



const char* FinalPathComponent(const char* path)
{
    // Return the final path component be it a file or folder
    // Archivers like zip etc will use this function to spit out either the final dir name
    // or the final file name - LeafFromPath will return ONLY final filename from a path
    // and will return "" if the path is a folder, whereas this function will return
    // the final folder name even if the path is a folder and NOT ""
    // We do NOT change LeafFromPath() as Archiver.cpp uses LeafFromPath in its critical
    // FillLists() function
    // Only problem is this function will return directory names with a trailing slash
    // We don't want to waste time by removing the trailing slash, if it was a leading
    // slash we can simply increment the pointer, but removing a trailing slash involves
    // making copy of the path that is being returned, then manipulating it, we avoid that
    // for sake of speed.
    int32 len = strlen(path);

    if (path[len - 1] == '/') len--;

    while (len > 0)
        if (path[--len] == '/')
            break;

    const char* leafStr = path;
    leafStr += len > 0 ? ++len : len;

    return leafStr;
}



const char* LeafFromPath(const char* path)
{
    // Return the filename (pointer to where filename starts rather) from a full path string
    int32 len = strlen(path);

    while (len > 0)
        if (path[--len] == '/')
            break;

    const char* leafStr = path;
    leafStr += len > 0 ? ++len : len;        // Workaround for no slashes ie root directory

    return leafStr;
}



char* ParentPath(const char* pathStr, bool truncateSlash)
{
    // Returns the parent path given a path,
    // e.g: "be/book" is passed, "be" will be returned
    //      if, "dir" is passed then "" will be returned and NOT NULL!
    int32 parentLen = strlen(pathStr) - strlen(FinalPathComponent(pathStr));
    char* parent = NULL;
    if (parentLen > 0)
    {
        parent = (char*)malloc(parentLen + 1);
        if (pathStr[parentLen - 1] == '/' && truncateSlash == true)
            parentLen--;
        strncpy(parent, pathStr, parentLen);
    }
    else
        parent = (char*)malloc(1);

    parent[parentLen] = 0;
    return parent;
}



char* Extension(const char* fileName, int extLen)
{
    // Return the extension in lowercase, without '.' in front -- freeing left to the caller
    int32 len = strlen(fileName);
    int32 lenCopy = len;
    char* m = new char[extLen + 1];
    bool dotEncountered = false;
    while (len >= lenCopy - extLen - 1)
        if (fileName[--len] == '.')
        {
            dotEncountered = true;
            break;
        }

    if (len >= 0 && dotEncountered == true)
        len++;
    else
        return NULL;

    int32 i = 0L;
    for (; i < extLen; i++, len++)
        m[i] = tolower(fileName[len]);

    m[i] = 0;

    return m;
}



BString SupressWildcards(const char* str)
{
    BString s = str;
    s.ReplaceAll("[", "\\[");
    s.ReplaceAll("*", "\\*");
    return s;
}



BString SupressWildcardSet(const char* str)
{
    BString s = str;
    s.ReplaceAll("[", "\\[");
    return s;
}


