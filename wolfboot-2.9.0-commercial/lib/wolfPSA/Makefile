# Simple static build for wolfPSA

WOLFSSL_PATH ?= ../wolfssl
USER_SETTINGS_PATH ?= $(CURDIR)/wolfpsa
PSA_INCLUDE ?=

BUILD_DIR ?= build
OBJDIR := $(BUILD_DIR)/obj
OBJDIR_PIC := $(BUILD_DIR)/obj.pic
LIBNAME := libwolfpsa.a
SHLIBNAME := libwolfpsa.so
EXPORT_MAP := $(CURDIR)/wolfpsa.map

CC ?= cc
AR ?= ar
RANLIB ?= ranlib

SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRC))
OBJ_PIC := $(patsubst src/%.c,$(OBJDIR_PIC)/%.o,$(SRC))

WOLFCRYPT_SRC := \
	$(WOLFSSL_PATH)/wolfcrypt/src/aes.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/ascon.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/asn.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/chacha.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/chacha20_poly1305.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/cmac.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/coding.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/cpuid.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/curve25519.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/curve448.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/des3.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/dsa.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/ecc.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/ecc_fp.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/ed25519.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/ed448.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/error.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/fe_operations.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/ge_operations.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/fe_448.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/ge_448.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/hash.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/hmac.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/integer.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/kdf.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/logging.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/md5.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/memory.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/poly1305.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/pwdbased.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/random.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/ripemd.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/rsa.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/sha.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/sha256.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/sha3.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/sha512.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/signature.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/sp_c32.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/sp_c64.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/sp_int.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/sp_x86_64.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/tfm.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/wc_encrypt.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/wc_lms.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/wc_lms_impl.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/wc_mldsa.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/wc_mlkem.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/wc_mlkem_poly.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/wc_port.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/wc_xmss.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/wc_xmss_impl.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/wolfentropy.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/wolfmath.c

WOLFCRYPT_OBJ := $(patsubst $(WOLFSSL_PATH)/wolfcrypt/src/%.c,$(OBJDIR)/wolfcrypt_%.o,$(WOLFCRYPT_SRC))
WOLFCRYPT_OBJ_PIC := $(patsubst $(WOLFSSL_PATH)/wolfcrypt/src/%.c,$(OBJDIR_PIC)/wolfcrypt_%.o,$(WOLFCRYPT_SRC))

WOLFSSL_CPPFLAGS ?= -DWOLFSSL_USER_SETTINGS

CPPFLAGS += -I$(WOLFSSL_PATH) -I$(USER_SETTINGS_PATH) \
	-I$(CURDIR) -I$(CURDIR)/wolfpsa -I$(CURDIR)/src $(WOLFSSL_CPPFLAGS)
ifneq ($(strip $(PSA_INCLUDE)),)
CPPFLAGS += -I$(PSA_INCLUDE)
endif

CFLAGS ?= -O2
WARNFLAGS ?= -Wall -Wextra -Werror
CFLAGS += $(WARNFLAGS)
DEBUG_FLAGS :=
ifeq ($(DEBUG),1)
DEBUG_FLAGS = -ggdb
endif
SANITIZE_FLAGS :=
ifeq ($(ASAN),1)
SANITIZE_FLAGS = -fsanitize=address
endif
CFLAGS += $(DEBUG_FLAGS) $(SANITIZE_FLAGS)
LDFLAGS += $(SANITIZE_FLAGS)

.PHONY: all clean

all: $(LIBNAME) $(SHLIBNAME)

$(LIBNAME): $(OBJ) $(WOLFCRYPT_OBJ)
	$(AR) rcs $@ $^
	$(RANLIB) $@

$(SHLIBNAME): $(OBJ_PIC) $(WOLFCRYPT_OBJ_PIC) $(EXPORT_MAP)
	$(CC) -shared -Wl,--version-script,$(EXPORT_MAP) -Wl,-Bsymbolic-functions -o $@ $(filter-out $(EXPORT_MAP),$^) $(LDFLAGS)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJDIR)/wolfcrypt_%.o: $(WOLFSSL_PATH)/wolfcrypt/src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJDIR_PIC)/%.o: src/%.c
	@mkdir -p $(OBJDIR_PIC)
	$(CC) $(CPPFLAGS) $(CFLAGS) -fPIC -c $< -o $@

$(OBJDIR_PIC)/wolfcrypt_%.o: $(WOLFSSL_PATH)/wolfcrypt/src/%.c
	@mkdir -p $(OBJDIR_PIC)
	$(CC) $(CPPFLAGS) $(CFLAGS) -fPIC -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(LIBNAME) $(SHLIBNAME)
