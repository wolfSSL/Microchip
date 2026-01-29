/* dummy_filesystem.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSH.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */


#ifndef DUMMY_FILESYSTEM_H
#define DUMMY_FILESYSTEM_H

#ifdef WOLFSSH_USER_FILESYSTEM

    typedef unsigned int off_t;
    typedef int mode_t; 
    #define WFILE int
    typedef int FILE;

    #define WSEEK_END           SEEK_END
    #define WBADFILE            NULL
    #define WS_DELIM            '/'
enum {
    WOLFSSH_O_RDWR, WOLFSSH_O_RDONLY, WOLFSSH_O_WRONLY, 
    WOLFSSH_O_APPEND, WOLFSSH_O_CREAT, WOLFSSH_O_TRUNC, WOLFSSH_O_EXCL
} ;

#define  WSTAT_T  stat_t
typedef  struct { int i; } stat_t;

#define WFD int
enum { O_RDWR, O_RDONLY, O_WRONLY, O_APPEND, O_CREAT, O_TRUNC, O_EXCL } ;

static int WFOPEN(FILE **f, const char *n, const char *m){
    (void) n; (void) m; (void)f;
    return NULL;
}

static int WFCLOSE(FILE *f) {
    (void) f;
    return 0;
}

static size_t WFREAD(void *b, size_t s, size_t n, FILE *f) {
    (void) b; (void) s; (void) n; (void) f;
    return 0;
}

static size_t WFWRITE(const void *b, size_t s, size_t n, FILE *f) {
    (void) b; (void) s; (void) n; (void) f;
    return 0;
}

static int WFSEEK(FILE *f, long int p, int m) {
    (void) f; (void) p; (void) m;
    return 0;
}

static long int WFTELL(FILE *f) {
    (void) f;
    return 0;
}
static void WREWIND(FILE *f) {
    (void) f;
}

static int WOPEN (const char* n, int f, int m) {
    (void) f; (void) n; (void) m;
    return 0;
}

static int WCLOSE(int f) {
    (void) f;
    return 0;
}

static size_t WPREAD(int f, void* b, size_t c,  off_t *o) {
    (void) f; (void) b; (void) c; (void)o;
    return 0;
}

static size_t WPWRITE(int f, void* b, size_t c,  off_t *o) {
    (void) f; (void) b; (void) c; (void)o;
    return 0;
}

static char *WGETCWD(void *fs, char *f, size_t l){
    (void) fs; (void) f; (void) l;
    return 0;
}

static int WRMDIR(void *fs, const char *p){
     (void) p;
    return 0;
}

static int WMKDIR(void *fs, const char *p, mode_t m) {
    (void) p; (void) m;
    return 0;
}

static int WREMOVE(void *fs, const char *p){
    (void) fs; (void) p;
    return 0;
} 

static int WRENAME(void *fs, const char *p, const char *np){
    (void) fs; (void) p; (void)np;
    return 0;
}

static int WSTAT(const char *p, stat_t *b) {
    (void) p; (void)b;
    return 0;
}

static int WLSTAT(const char *p, stat_t *b) {
    (void) p; (void)b;
    return 0;
}

static int WCHMOD(void *fs, const char *p, mode_t m) {
    (void) fs; (void) p; (void)m;
    return 0;
}

static int SFTP_GetAttributes(void* fs, const char* fileName,
        void* atr, byte link, void* heap) {
    (void)fs; (void)fileName; (void)atr; (void)link; (void)heap;
    return 0;

}

static int SFTP_GetAttributes_Handle(void* ssh, byte* handle, int handleSz,
        char* name, void* atr) {
            (void)ssh; (void)handle; (void)handleSz; (void)name;

        return 0;
}

#endif /*  WOLFSSH_USER_FILESYSTEM */

#endif
