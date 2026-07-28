WOLFSSL_PATH ?= ../../../../wolfssl

CC ?= cc
CFLAGS ?= -O2
WARNFLAGS ?= -Wall -Wextra
CFLAGS += $(WARNFLAGS)

CPPFLAGS += -DWOLFSSL_USER_SETTINGS
CPPFLAGS += -I. -I$(WOLFSSL_PATH) -I$(WOLFSSL_PATH)/wolfssl
CPPFLAGS += -DWOLFSSL_ECC_CLIENT_CERT

WOLFCRYPT_SRC_ALL := $(wildcard $(WOLFSSL_PATH)/wolfcrypt/src/*.c)
WOLFCRYPT_SRC := $(filter-out \
	$(WOLFSSL_PATH)/wolfcrypt/src/evp.c \
	$(WOLFSSL_PATH)/wolfcrypt/src/misc.c \
,$(WOLFCRYPT_SRC_ALL))

WOLFSSL_SRC_ALL := $(wildcard $(WOLFSSL_PATH)/src/*.c)
WOLFSSL_SRC := $(filter-out \
	$(WOLFSSL_PATH)/src/tls13.c \
	$(WOLFSSL_PATH)/src/dtls13.c \
	$(WOLFSSL_PATH)/src/quic.c \
	$(WOLFSSL_PATH)/src/bio.c \
	$(WOLFSSL_PATH)/src/conf.c \
	$(WOLFSSL_PATH)/src/pk.c \
	$(WOLFSSL_PATH)/src/ssl_asn1.c \
	$(WOLFSSL_PATH)/src/ssl_bn.c \
	$(WOLFSSL_PATH)/src/ssl_certman.c \
	$(WOLFSSL_PATH)/src/ssl_crypto.c \
	$(WOLFSSL_PATH)/src/ssl_load.c \
	$(WOLFSSL_PATH)/src/ssl_misc.c \
	$(WOLFSSL_PATH)/src/ssl_p7p12.c \
	$(WOLFSSL_PATH)/src/ssl_sess.c \
	$(WOLFSSL_PATH)/src/ssl_sk.c \
	$(WOLFSSL_PATH)/src/x509.c \
	$(WOLFSSL_PATH)/src/x509_str.c \
,$(WOLFSSL_SRC_ALL))
CLIENT_SRC := $(WOLFSSL_PATH)/examples/client/client.c

OBJDIR := build/obj
OBJS := $(patsubst $(WOLFSSL_PATH)/wolfcrypt/src/%.c,$(OBJDIR)/wolfcrypt_%.o,$(WOLFCRYPT_SRC)) \
	$(patsubst $(WOLFSSL_PATH)/src/%.c,$(OBJDIR)/wolfssl_%.o,$(WOLFSSL_SRC)) \
	$(OBJDIR)/client.o

TARGET := psa_tls_client

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm -lpthread

$(OBJDIR)/wolfcrypt_%.o: $(WOLFSSL_PATH)/wolfcrypt/src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJDIR)/wolfssl_%.o: $(WOLFSSL_PATH)/src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJDIR)/client.o: $(CLIENT_SRC)
	@mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)
