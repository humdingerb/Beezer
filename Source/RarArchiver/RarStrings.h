/*
 * Copyright (c) 2011, Ramshankar (aka Teknomancer)
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

#ifndef _RAR_STRINGS_H
#define _RAR_STRINGS_H

const char
*const kCompressionLevel =        "Compression level",
*const kLevel0 =                  "0 (none)",
*const kLevel1 =                  "1 (fastest)",
*const kLevel2 =                  "2",
*const kLevel3 =                  "3 (default)",
*const kLevel4 =                  "4",
*const kLevel5 =                  "5 (best)",

*const kAdding =                  "While adding",
*const kDisableSolidArk =         "Disable solid archive",
*const kMultimediaCompress =      "Multimedia compression",
*const kRecoveryRecord =          "Add recovery record",
*const kRecurse =                 "Recurse into folders",

*const kExtracting =              "While extracting",
*const kAlwaysOverwrite =         "Always overwrite (default)",
*const kNoOverwrite =             "Never overwrite existing files",
*const kUpdate =                  "Update files, create if needed",
*const kFreshen =                 "Freshen existing files, create none",

*const kOtherOptions =            "Other options",
*const kKeepBroken =              "Keep broken extracted files",
*const kProcessAttributes =       "Process attributes";

#endif /* _RAR_STRINGS_H */
