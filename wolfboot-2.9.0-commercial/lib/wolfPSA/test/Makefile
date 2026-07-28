WOLFPSA_PATH ?= ..
WOLFSSL_PATH ?= $(WOLFPSA_PATH)/../wolfssl
WOLFPSA_ABS := $(abspath $(WOLFPSA_PATH))
BUILD_DIR ?= build

WOLFSSL_CANDIDATE_DIRS := \
	$(WOLFSSL_PATH)/build \
	$(WOLFSSL_PATH)/src/.libs \
	$(WOLFSSL_PATH)

WOLFSSL_BUILD_DIR ?= $(firstword $(foreach dir,$(WOLFSSL_CANDIDATE_DIRS),\
	$(if $(wildcard $(dir)/libwolfssl.so $(dir)/libwolfssl.a),$(dir))))

CC ?= cc
NM ?= nm

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

CPPFLAGS += -DHAVE_CONFIG_H -DWOLFSSL_HAVE_PSA -DHAVE_PK_CALLBACKS
CPPFLAGS += -I$(WOLFSSL_PATH) -I$(WOLFSSL_PATH)/wolfssl
ifneq ($(WOLFSSL_BUILD_DIR),)
CPPFLAGS += -I$(WOLFSSL_BUILD_DIR)
endif
CPPFLAGS += -I$(WOLFPSA_PATH) -I$(WOLFPSA_PATH)/wolfpsa
CPPFLAGS += -I$(WOLFPSA_PATH)/src
CPPFLAGS += -I$(WOLFPSA_PATH)/test/psa_server

LDFLAGS += -L$(WOLFPSA_PATH)
ifneq ($(WOLFSSL_BUILD_DIR),)
LDFLAGS += -L$(WOLFSSL_BUILD_DIR)
endif
LDLIBS += -lwolfssl -lwolfpsa -lpthread -lm

RPATH_WOLFPSA = -Wl,-rpath,'$$ORIGIN/..'
RPATH_WOLFSSL =
ifneq ($(WOLFSSL_BUILD_DIR),)
RPATH_WOLFSSL = -Wl,-rpath,$(abspath $(WOLFSSL_BUILD_DIR))
endif

WOLFSSL_LOCAL_LIB := $(firstword \
	$(wildcard $(WOLFSSL_BUILD_DIR)/libwolfssl.so) \
	$(wildcard $(WOLFSSL_BUILD_DIR)/libwolfssl.a))
WOLFSSL_LOCAL_SYMBOLS := $(if $(WOLFSSL_LOCAL_LIB),$(shell \
	$(NM) -D $(WOLFSSL_LOCAL_LIB) 2>/dev/null || \
	$(NM) $(WOLFSSL_LOCAL_LIB) 2>/dev/null))
WOLFSSL_HAS_PSA_TLS := $(findstring wolfSSL_CTX_psa_enable,$(WOLFSSL_LOCAL_SYMBOLS))

BINARIES = psa_api_test psa_crypto_init_test psa_des3_stack_scrub_test psa_ecc_bit_inference_test psa_ecc_curve_id_test psa_random_size_test psa_rsa_pss_interop_test psa_mldsa_test psa_mlkem_test psa_xof_test psa_key_wrap_test psa_sign_context_test psa_lms_xmss_verify_test psa_ascon_xchacha_test psa_sp800_108_test psa_14_misc_test psa_tls_client wolfcrypt-psa-benchmark

# PSA 1.4 coverage tests: one self-contained binary per feature area, all
# built from psa_server/<name>.c with the default link recipe.
PSA_14_TESTS = psa_mldsa_test psa_mlkem_test psa_xof_test psa_key_wrap_test \
	psa_sign_context_test psa_lms_xmss_verify_test psa_ascon_xchacha_test \
	psa_sp800_108_test psa_14_misc_test

ifdef WOLFSSL_HAS_PSA_TLS
BINARIES += psa_tls_server
endif

PSA_API_TEST_OBJS = psa_server/psa_api_test.o
PSA_CRYPTO_INIT_TEST_OBJS = psa_server/psa_crypto_init_test.o
PSA_DES3_STACK_SCRUB_TEST_OBJS = psa_server/psa_des3_stack_scrub_test.o
PSA_ECC_BIT_INFERENCE_TEST_OBJS = psa_server/psa_ecc_bit_inference_test.o
PSA_ECC_CURVE_ID_TEST_OBJS = psa_server/psa_ecc_curve_id_test.o
PSA_RANDOM_SIZE_TEST_OBJS = psa_server/psa_random_size_test.o
PSA_ECC_CURVE_ID_TEST_DEPS = $(WOLFPSA_PATH)/$(BUILD_DIR)/obj/psa_asymmetric.o \
	$(WOLFPSA_PATH)/$(BUILD_DIR)/obj/psa_pq.o
PSA_RSA_PSS_TEST_OBJS = psa_server/psa_rsa_pss_interop_test.o

.PHONY: all clean rebuild-wolfssl-psa require-wolfssl-lib

all: info $(BINARIES)

info:
ifndef WOLFSSL_LOCAL_LIB
	@echo "Skipping psa_tls_server: no local wolfSSL library found under $(WOLFSSL_PATH) (checked: $(WOLFSSL_CANDIDATE_DIRS)). Build wolfSSL first, for example: make -C $(WOLFSSL_PATH)"
else ifndef WOLFSSL_HAS_PSA_TLS
	@echo "Skipping psa_tls_server: $(WOLFSSL_LOCAL_LIB) does not export wolfSSL PSA TLS callback symbols (for example wolfSSL_CTX_psa_enable). If you want to rebuild the sibling wolfSSL tree for wolfPSA, run: make rebuild-wolfssl-psa"
endif

psa_api_test: require-wolfssl-lib $(PSA_API_TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(PSA_API_TEST_OBJS) $(LDFLAGS) $(LDLIBS) $(RPATH_WOLFPSA) $(RPATH_WOLFSSL)

psa_crypto_init_test: require-wolfssl-lib $(PSA_CRYPTO_INIT_TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(PSA_CRYPTO_INIT_TEST_OBJS) $(WOLFPSA_PATH)/libwolfpsa.a $(LDFLAGS) -lwolfssl -lpthread -lm $(RPATH_WOLFSSL) -Wl,--wrap=wolfCrypt_Init

psa_des3_stack_scrub_test: require-wolfssl-lib $(PSA_DES3_STACK_SCRUB_TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(PSA_DES3_STACK_SCRUB_TEST_OBJS) $(LDFLAGS) $(LDLIBS) $(RPATH_WOLFPSA) $(RPATH_WOLFSSL)

psa_ecc_bit_inference_test: require-wolfssl-lib $(PSA_ECC_BIT_INFERENCE_TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(PSA_ECC_BIT_INFERENCE_TEST_OBJS) $(LDFLAGS) $(LDLIBS) $(RPATH_WOLFPSA) $(RPATH_WOLFSSL)

psa_ecc_curve_id_test: require-wolfssl-lib $(PSA_ECC_CURVE_ID_TEST_OBJS) $(PSA_ECC_CURVE_ID_TEST_DEPS)
	$(CC) $(CFLAGS) -o $@ $(PSA_ECC_CURVE_ID_TEST_OBJS) $(PSA_ECC_CURVE_ID_TEST_DEPS) $(LDFLAGS) $(LDLIBS) $(RPATH_WOLFPSA) $(RPATH_WOLFSSL)

psa_random_size_test: require-wolfssl-lib $(PSA_RANDOM_SIZE_TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(PSA_RANDOM_SIZE_TEST_OBJS) $(LDFLAGS) $(LDLIBS) $(RPATH_WOLFPSA) $(RPATH_WOLFSSL)

psa_rsa_pss_interop_test: require-wolfssl-lib $(PSA_RSA_PSS_TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(PSA_RSA_PSS_TEST_OBJS) $(LDFLAGS) $(LDLIBS) $(RPATH_WOLFPSA) $(RPATH_WOLFSSL)

$(PSA_14_TESTS): %: require-wolfssl-lib psa_server/%.o
	$(CC) $(CFLAGS) -o $@ psa_server/$@.o $(LDFLAGS) $(LDLIBS) $(RPATH_WOLFPSA) $(RPATH_WOLFSSL)

ifdef WOLFSSL_HAS_PSA_TLS
psa_tls_server: psa_server/psa_tls_server.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(RPATH_WOLFPSA) $(RPATH_WOLFSSL)
endif

psa_tls_client:
	make -C psa_server/tls_client
	cp psa_server/tls_client/psa_tls_client ./psa_tls_client

wolfcrypt-psa-benchmark:
	make -C wolfcrypt-benchmark
	cp wolfcrypt-benchmark/wolfcrypt-psa-benchmark ./wolfcrypt-psa-benchmark

require-wolfssl-lib:
ifndef WOLFSSL_LOCAL_LIB
	@echo "No local wolfSSL library found under $(WOLFSSL_PATH) (checked: $(WOLFSSL_CANDIDATE_DIRS)). Build wolfSSL first, for example: make rebuild-wolfssl-psa"
	@exit 1
endif

rebuild-wolfssl-psa: $(WOLFPSA_PATH)/libwolfpsa.so
	@test -d "$(WOLFSSL_PATH)" || { \
		echo "wolfSSL source tree not found at $(WOLFSSL_PATH)"; \
		exit 1; \
	}
	@test -x "$(WOLFSSL_PATH)/configure" || { \
		cd "$(WOLFSSL_PATH)" && ./autogen.sh; \
	}
	cd "$(WOLFSSL_PATH)" && ./configure \
		--enable-psa \
		--enable-pkcallbacks \
		--with-psa-include="$(WOLFPSA_ABS)/wolfpsa" \
		--with-psa-lib="$(WOLFPSA_ABS)" \
		--with-psa-lib-name=wolfpsa \
		CFLAGS="$(DEBUG_FLAGS) $(SANITIZE_FLAGS)" \
		CPPFLAGS="-DWOLFSSL_PSA_NO_RNG -DWOLFSSL_PSA_NO_HASH -DWOLFSSL_PSA_NO_AES" \
		LDFLAGS="$(SANITIZE_FLAGS) -Wl,-rpath,$(WOLFPSA_ABS) -Wl,-rpath-link,$(WOLFPSA_ABS)"
	$(MAKE) -C "$(WOLFSSL_PATH)" CFLAGS="$(DEBUG_FLAGS) $(SANITIZE_FLAGS)" LDFLAGS="$(SANITIZE_FLAGS) -Wl,-rpath,$(WOLFPSA_ABS) -Wl,-rpath-link,$(WOLFPSA_ABS)" src/libwolfssl.la

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	make -C psa_server/tls_client clean
	make -C wolfcrypt-benchmark clean
	rm -f psa_server/*.o
	rm -f $(BINARIES) *.o *.log
