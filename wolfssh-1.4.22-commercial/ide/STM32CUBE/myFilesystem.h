/* myFilesystem.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSH.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */


#ifndef MY_FILESYSTEM_H
#define MY_FILESYSTEM_H

#ifdef WOLFSSH_USER_FILESYSTEM

    #define WFILE int

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

static inline int WFOPEN(FILE **f, const char *n, const char *m){
    (void) n; (void) m; (void)f;
    return NULL;
}

static inline int WFCLOSE(FILE *f) {
    (void) f;
    return 0;
}

static inline size_t WFREAD(void *b, size_t s, size_t n, FILE *f) {
    (void) b; (void) s; (void) n; (void) f;
    return 0;
}

static inline size_t WFWRITE(const void *b, size_t s, size_t n, FILE *f) {
    (void) b; (void) s; (void) n; (void) f;
    return 0;
}

static inline int WFSEEK(FILE *f, long int p, int m) {
    (void) f; (void) p; (void) m;
    return 0;
}

static inline long int WFTELL(FILE *f) {
    (void) f;
    return 0;
}
static inline void WREWIND(FILE *f) {
    (void) f;
}

static inline int WOPEN (const char* n, int f, int m) {
    (void) f; (void) n; (void) m;
    return 0;
}

static inline int WCLOSE(int f) {
    (void) f;
    return 0;
}

static inline size_t WPREAD(int f, void* b, size_t c,  off_t *o) {
    (void) f; (void) b; (void) c; (void)o;
    return 0;
}

static inline size_t WPWRITE(int f, void* b, size_t c,  off_t *o) {
    (void) f; (void) b; (void) c; (void)o;
    return 0;
}

static inline char *WGETCWD(void *fs, char *f, size_t l){
    (void) fs; (void) f; (void) l;
    return 0;
}

static inline int WRMDIR(void *fs, const char *p){
     (void) p;
    return 0;
}

static inline int WMKDIR(void *fs, const char *p, mode_t m) {
    (void) p; (void) m;
    return 0;
}

static inline int WREMOVE(void *fs, const char *p){
    (void) fs; (void) p;
    return 0;
} 

static inline int WRENAME(void *fs, const char *p, const char *np){
    (void) fs; (void) p; (void)np;
    return 0;
}

static inline int WSTAT(const char *p, stat_t *b) {
    (void) p; (void)b;
    return 0;
}

static inline int WLSTAT(const char *p, stat_t *b) {
    (void) p; (void)b;
    return 0;
}

static inline int WCHMOD(void *fs, const char *p, mode_t m) {
    (void) fs; (void) p; (void)m;
    return 0;
}

static inline int SFTP_GetAttributes(void* fs, const char* fileName,
        void* atr, byte link, void* heap) {
    (void)fs; (void)fileName; (void)atr; (void)link; (void)heap;
    return 0;

}

static inline int SFTP_GetAttributes_Handle(void* ssh, byte* handle, int handleSz,
        char* name, void* atr) {
            (void)ssh; (void)handle; (void)handleSz; (void)name;

        return 0;
}

#endif /*  WOLFSSH_USER_FILESYSTEM */

#endif
