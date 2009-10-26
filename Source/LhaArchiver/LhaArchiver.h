/*
 *    Beezer
 *    Copyright (c) 2002 Ramshankar (aka Teknomancer)
 *    See "License.txt" for licensing info.
*/

#ifndef _LHA_ARCHIVER_H
#define _LHA_ARCHIVER_H

#include <stdio.h>

#include "Archiver.h"

#define BZR_ARK                            "lha"

class BMessenger;

class LhaArchiver : public Archiver
{
    public:
        LhaArchiver (const char *binPath);
        
        // Overridables
        void                BuildDefaultMenu ();
        
        // Abstract Implementations & overridables
        status_t            Open (entry_ref *ref, BMessage *fileList);
        status_t            ReadOpen (FILE *fp);

        status_t            ReadExtract (FILE *fp, BMessenger *progress, volatile bool *cancel);
        status_t            Extract (entry_ref *dir, BMessage *list, BMessenger *progress, volatile bool *cancel);
        
        status_t            Test (char *&outputStr, BMessenger *progress, volatile bool *cancel);
        status_t            ReadTest (FILE *fp, char *&outputStr, BMessenger *progress, volatile bool *cancel);
        
        status_t            ReadAdd (FILE *fp, BMessage *addedPaths, BMessenger *progress, volatile bool *cancel);
        status_t            Add (bool createMode, const char *relPath, BMessage *list, BMessage *addedPaths,
                                BMessenger *progress, volatile bool *cancel);
    
        status_t            Create (BPath *archivePath, const char *relPath, BMessage *fileList,
                                BMessage *addedPaths, BMessenger *progress, volatile bool *cancel);
    
        status_t            Delete (char *&outputStr, BMessage *list, BMessenger *progress, volatile bool *cancel);
        status_t            ReadDelete (FILE *fp, char *&outputStr,    BMessenger *progress, volatile bool *cancel);

        bool                SupportsFolderEntity () const;
        bool                CanPartiallyOpen () const;
        
    private:    
        // Private hooks
        int8                MonthStrToNum (const char *month) const;
        void                SetMimeType ();

        char                m_lhaPath[B_PATH_NAME_LENGTH];
};

#endif /* _LHA_ARCHIVER_H */
