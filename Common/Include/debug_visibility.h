#ifndef DEBUG_VISIBILITY_H
#define DEBUG_VISIBILITY_H

/*
 * NOICE_DEBUG_GLOBALS is enabled by the normal embedded debug build.  Removing
 * file-local linkage makes old GCC symbols visible to NoICE 9.8 watches.  The
 * release build leaves the macro undefined and preserves normal C static
 * linkage.  This changes symbol visibility only; it does not add runtime code.
 */
#if defined(NOICE_DEBUG_GLOBALS) && (NOICE_DEBUG_GLOBALS != 0)
#define FILE_LOCAL
#else
#define FILE_LOCAL static
#endif

#endif
