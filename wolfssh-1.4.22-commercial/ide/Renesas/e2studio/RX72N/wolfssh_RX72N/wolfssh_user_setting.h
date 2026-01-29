/* wolfssh_user_settings.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSH.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFSSH_USER_SETTING_H_
#define WOLFSSH_USER_SETTING_H_

#define WOLFSSL_WOLFSSH

#undef WOLFSSH_USER_IO
#define WOLFSSH_USER_IO

#undef NO_WOLFSSH_SERVER

#undef WOLFSSH_SFTP
#define WOLFSSH_SFTP

#undef WOLFSSH_NO_TIMESTAMP
#define WOLFSSH_NO_TIMESTAMP

#define WOLFSSH_FATFS
#define WOLFSSH_STOREHANDLE
#define PRINTF printf
#define DEFAULT_WINDOW_SZ 16384
#define WOLFSSH_NO_RSA
#define WOLFSSH_NO_HMAC_SHA2_512
/* enable for debugging */
/* #define DEBUG_WOLFSSH */
#endif /* WOLFSSH_USER_SETTING_H_ */
