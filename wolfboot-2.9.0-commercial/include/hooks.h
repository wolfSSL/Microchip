/* hooks.h
 *
 * wolfBoot hooks API definitions.
 *
 * Hooks allow users to inject custom logic at well-defined points in the
 * wolfBoot boot process. Each hook is independently enabled via its own
 * build macro.
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFBOOT_HOOKS_H
#define WOLFBOOT_HOOKS_H

#ifdef __cplusplus
extern "C" {
#endif

struct wolfBoot_image;

#ifdef WOLFBOOT_HOOK_LOADER_PREINIT
void wolfBoot_hook_preinit(void);
#endif

#ifdef WOLFBOOT_HOOK_LOADER_POSTINIT
void wolfBoot_hook_postinit(void);
#endif

#ifdef WOLFBOOT_HOOK_BOOT
void wolfBoot_hook_boot(struct wolfBoot_image *boot_img);
#endif

#ifdef WOLFBOOT_HOOK_PANIC
void wolfBoot_hook_panic(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* WOLFBOOT_HOOKS_H */
