/* psa_asymmetric.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wolfssl/wolfcrypt/settings.h>

#if defined(WOLFSSL_PSA_ENGINE)

#include <psa/crypto.h>
#include <wolfpsa/psa_engine.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/wc_port.h>
#include <wolfssl/wolfcrypt/logging.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/mem_track.h>
#include <wolfssl/wolfcrypt/rsa.h>

psa_status_t psa_pq_check_key_type_supported(psa_key_type_t type);
psa_status_t psa_pq_check_key_size_valid(psa_key_type_t type, size_t bits);

#ifndef NO_RSA
#include <wolfssl/wolfcrypt/rsa.h>
#endif

#ifdef HAVE_ECC
#include <wolfssl/wolfcrypt/ecc.h>
#endif

#ifdef HAVE_ED25519
#include <wolfssl/wolfcrypt/ed25519.h>
#endif

#ifdef HAVE_ED448
#include <wolfssl/wolfcrypt/ed448.h>
#endif

#ifdef HAVE_CURVE25519
#include <wolfssl/wolfcrypt/curve25519.h>
#endif

#ifdef HAVE_CURVE448
#include <wolfssl/wolfcrypt/curve448.h>
#endif

/* Check if an asymmetric algorithm is supported */
psa_status_t psa_asymmetric_check_alg_supported(psa_algorithm_t alg)
{
    /* Check if the algorithm is a signature algorithm */
    if (PSA_ALG_IS_SIGN_HASH(alg) || PSA_ALG_IS_SIGN_MESSAGE(alg)) {
        /* Check RSA signature algorithms */
        if (PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg)) {
            #ifndef NO_RSA
                /* Check hash algorithm */
                psa_algorithm_t hash_alg = PSA_ALG_SIGN_GET_HASH(alg);
                switch (hash_alg) {
                    case PSA_ALG_SHA_1:
                    #ifndef NO_SHA
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case PSA_ALG_SHA_224:
                    #ifdef WOLFSSL_SHA224
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case PSA_ALG_SHA_256:
                    #ifndef NO_SHA256
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case PSA_ALG_SHA_384:
                    #ifdef WOLFSSL_SHA384
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case PSA_ALG_SHA_512:
                    #ifdef WOLFSSL_SHA512
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    default:
                        return PSA_ERROR_NOT_SUPPORTED;
                }
            #else
                return PSA_ERROR_NOT_SUPPORTED;
            #endif
        }
        else if (PSA_ALG_IS_RSA_PSS(alg)) {
            #if !defined(NO_RSA) && defined(WC_RSA_PSS)
                /* Check hash algorithm */
                psa_algorithm_t hash_alg = PSA_ALG_SIGN_GET_HASH(alg);
                switch (hash_alg) {
                    case PSA_ALG_SHA_1:
                    #ifndef NO_SHA
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case PSA_ALG_SHA_224:
                    #ifdef WOLFSSL_SHA224
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case PSA_ALG_SHA_256:
                    #ifndef NO_SHA256
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case PSA_ALG_SHA_384:
                    #ifdef WOLFSSL_SHA384
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case PSA_ALG_SHA_512:
                    #ifdef WOLFSSL_SHA512
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    default:
                        return PSA_ERROR_NOT_SUPPORTED;
                }
            #else
                return PSA_ERROR_NOT_SUPPORTED;
            #endif
        }
        else if (PSA_ALG_IS_ECDSA(alg)) {
            #ifdef HAVE_ECC
                /* Check hash algorithm */
                psa_algorithm_t hash_alg = PSA_ALG_SIGN_GET_HASH(alg);
                switch (hash_alg) {
                    case PSA_ALG_SHA_1:
                    #ifndef NO_SHA
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case PSA_ALG_SHA_224:
                    #ifdef WOLFSSL_SHA224
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case PSA_ALG_SHA_256:
                    #ifndef NO_SHA256
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case PSA_ALG_SHA_384:
                    #ifdef WOLFSSL_SHA384
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case PSA_ALG_SHA_512:
                    #ifdef WOLFSSL_SHA512
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    default:
                        return PSA_ERROR_NOT_SUPPORTED;
                }
            #else
                return PSA_ERROR_NOT_SUPPORTED;
            #endif
        }
        else if (alg == PSA_ALG_ED25519PH) {
            #ifdef HAVE_ED25519
                return PSA_SUCCESS;
            #else
                return PSA_ERROR_NOT_SUPPORTED;
            #endif
        }
        else if (alg == PSA_ALG_ED448PH) {
            #ifdef HAVE_ED448
                return PSA_SUCCESS;
            #else
                return PSA_ERROR_NOT_SUPPORTED;
            #endif
        }
    }
    /* Check if the algorithm is an asymmetric encryption algorithm */
    else if (PSA_ALG_IS_ASYMMETRIC_ENCRYPTION(alg)) {
        if (alg == PSA_ALG_RSA_PKCS1V15_CRYPT) {
            #ifndef NO_RSA
                return PSA_SUCCESS;
            #else
                return PSA_ERROR_NOT_SUPPORTED;
            #endif
        }
        else if (PSA_ALG_IS_RSA_OAEP(alg)) {
            #if !defined(NO_RSA) && defined(WOLFSSL_RSA_OAEP)
                /* Check hash algorithm */
                psa_algorithm_t hash_alg = PSA_ALG_RSA_OAEP_GET_HASH(alg);
                switch (hash_alg) {
                    case PSA_ALG_SHA_1:
                    #ifndef NO_SHA
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case PSA_ALG_SHA_224:
                    #ifdef WOLFSSL_SHA224
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case PSA_ALG_SHA_256:
                    #ifndef NO_SHA256
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case PSA_ALG_SHA_384:
                    #ifdef WOLFSSL_SHA384
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case PSA_ALG_SHA_512:
                    #ifdef WOLFSSL_SHA512
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    default:
                        return PSA_ERROR_NOT_SUPPORTED;
                }
            #else
                return PSA_ERROR_NOT_SUPPORTED;
            #endif
        }
    }
    
    return PSA_ERROR_NOT_SUPPORTED;
}

/* Check if an asymmetric key type is supported */
psa_status_t psa_asymmetric_check_key_type_supported(psa_key_type_t type)
{
    int is_pq = 0;

    if (type == PSA_KEY_TYPE_ML_KEM_KEY_PAIR ||
        type == PSA_KEY_TYPE_ML_KEM_PUBLIC_KEY ||
        type == PSA_KEY_TYPE_ML_DSA_KEY_PAIR ||
        type == PSA_KEY_TYPE_ML_DSA_PUBLIC_KEY) {
        is_pq = 1;
    }
#ifdef PSA_KEY_TYPE_LMS_KEY_PAIR
    if (type == PSA_KEY_TYPE_LMS_KEY_PAIR) {
        is_pq = 1;
    }
#endif
#ifdef PSA_KEY_TYPE_LMS_PUBLIC_KEY
    if (type == PSA_KEY_TYPE_LMS_PUBLIC_KEY) {
        is_pq = 1;
    }
#endif
#ifdef PSA_KEY_TYPE_XMSS_KEY_PAIR
    if (type == PSA_KEY_TYPE_XMSS_KEY_PAIR) {
        is_pq = 1;
    }
#endif
#ifdef PSA_KEY_TYPE_XMSS_PUBLIC_KEY
    if (type == PSA_KEY_TYPE_XMSS_PUBLIC_KEY) {
        is_pq = 1;
    }
#endif

    /* Check RSA key types */
    if (type == PSA_KEY_TYPE_RSA_KEY_PAIR || type == PSA_KEY_TYPE_RSA_PUBLIC_KEY) {
        #ifndef NO_RSA
            return PSA_SUCCESS;
        #else
            return PSA_ERROR_NOT_SUPPORTED;
        #endif
    }
    /* Check ECC key types */
    else if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(type) || PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(type)) {
        psa_ecc_family_t curve = PSA_KEY_TYPE_ECC_GET_FAMILY(type);
        switch (curve) {
            case PSA_ECC_FAMILY_SECP_R1:
            #ifdef HAVE_ECC
                return PSA_SUCCESS;
            #else
                return PSA_ERROR_NOT_SUPPORTED;
            #endif
            
            case PSA_ECC_FAMILY_SECP_K1:
            #if defined(HAVE_ECC) && defined(HAVE_ECC_KOBLITZ)
                return PSA_SUCCESS;
            #else
                return PSA_ERROR_NOT_SUPPORTED;
            #endif
            
            case PSA_ECC_FAMILY_BRAINPOOL_P_R1:
            #if defined(HAVE_ECC) && defined(HAVE_BRAINPOOL)
                return PSA_SUCCESS;
            #else
                return PSA_ERROR_NOT_SUPPORTED;
            #endif
            
            case PSA_ECC_FAMILY_MONTGOMERY:
            #if defined(HAVE_CURVE25519) || defined(HAVE_CURVE448)
                return PSA_SUCCESS;
            #else
                return PSA_ERROR_NOT_SUPPORTED;
            #endif
            
            case PSA_ECC_FAMILY_TWISTED_EDWARDS:
            #if defined(HAVE_ED25519) || defined(HAVE_ED448)
                return PSA_SUCCESS;
            #else
                return PSA_ERROR_NOT_SUPPORTED;
            #endif
            
            default:
                return PSA_ERROR_NOT_SUPPORTED;
        }
    }
    /* Check post-quantum key types */
    else if (is_pq) {
        return psa_pq_check_key_type_supported(type);
    }
    
    return PSA_ERROR_NOT_SUPPORTED;
}

/* Check if an asymmetric key size is valid for the given key type */
psa_status_t psa_asymmetric_check_key_size_valid(psa_key_type_t type, size_t bits)
{
    int is_pq = 0;

    if (type == PSA_KEY_TYPE_ML_KEM_KEY_PAIR ||
        type == PSA_KEY_TYPE_ML_KEM_PUBLIC_KEY ||
        type == PSA_KEY_TYPE_ML_DSA_KEY_PAIR ||
        type == PSA_KEY_TYPE_ML_DSA_PUBLIC_KEY) {
        is_pq = 1;
    }
#ifdef PSA_KEY_TYPE_LMS_KEY_PAIR
    if (type == PSA_KEY_TYPE_LMS_KEY_PAIR) {
        is_pq = 1;
    }
#endif
#ifdef PSA_KEY_TYPE_LMS_PUBLIC_KEY
    if (type == PSA_KEY_TYPE_LMS_PUBLIC_KEY) {
        is_pq = 1;
    }
#endif
#ifdef PSA_KEY_TYPE_XMSS_KEY_PAIR
    if (type == PSA_KEY_TYPE_XMSS_KEY_PAIR) {
        is_pq = 1;
    }
#endif
#ifdef PSA_KEY_TYPE_XMSS_PUBLIC_KEY
    if (type == PSA_KEY_TYPE_XMSS_PUBLIC_KEY) {
        is_pq = 1;
    }
#endif

    /* Check RSA key types */
    if (type == PSA_KEY_TYPE_RSA_KEY_PAIR || type == PSA_KEY_TYPE_RSA_PUBLIC_KEY) {
        #ifndef NO_RSA
            /* Check key size */
            if (bits < 2048 || bits > 4096 || (bits % 8) != 0) {
                return PSA_ERROR_INVALID_ARGUMENT;
            }
            return PSA_SUCCESS;
        #else
            return PSA_ERROR_NOT_SUPPORTED;
        #endif
    }
    /* Check ECC key types */
    else if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(type) || PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(type)) {
        psa_ecc_family_t curve = PSA_KEY_TYPE_ECC_GET_FAMILY(type);
        switch (curve) {
            case PSA_ECC_FAMILY_SECP_R1:
            #ifdef HAVE_ECC
                /* Check key size */
                switch (bits) {
                    case 192:
                    #ifdef HAVE_ECC192
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case 224:
                    #ifdef HAVE_ECC224
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case 256:
                    #ifdef HAVE_ECC256
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case 384:
                    #ifdef HAVE_ECC384
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case 521:
                    #ifdef HAVE_ECC521
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    default:
                        return PSA_ERROR_INVALID_ARGUMENT;
                }
            #else
                return PSA_ERROR_NOT_SUPPORTED;
            #endif
            
            case PSA_ECC_FAMILY_SECP_K1:
            #if defined(HAVE_ECC) && defined(HAVE_ECC_KOBLITZ)
                /* Check key size */
                switch (bits) {
                    case 192:
                    #ifdef HAVE_ECC192
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case 224:
                    #ifdef HAVE_ECC224
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case 256:
                    #ifdef HAVE_ECC256
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    default:
                        return PSA_ERROR_INVALID_ARGUMENT;
                }
            #else
                return PSA_ERROR_NOT_SUPPORTED;
            #endif
            
            case PSA_ECC_FAMILY_BRAINPOOL_P_R1:
            #if defined(HAVE_ECC) && defined(HAVE_BRAINPOOL)
                /* Check key size */
                switch (bits) {
                    case 256:
                    case 384:
                    case 512:
                        return PSA_SUCCESS;
                    
                    default:
                        return PSA_ERROR_INVALID_ARGUMENT;
                }
            #else
                return PSA_ERROR_NOT_SUPPORTED;
            #endif
            
            case PSA_ECC_FAMILY_MONTGOMERY:
            #if defined(HAVE_CURVE25519) || defined(HAVE_CURVE448)
                /* Check key size */
                switch (bits) {
                    case 255:
                    #ifdef HAVE_CURVE25519
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case 448:
                    #ifdef HAVE_CURVE448
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    default:
                        return PSA_ERROR_INVALID_ARGUMENT;
                }
            #else
                return PSA_ERROR_NOT_SUPPORTED;
            #endif
            
            case PSA_ECC_FAMILY_TWISTED_EDWARDS:
            #if defined(HAVE_ED25519) || defined(HAVE_ED448)
                /* Check key size */
                switch (bits) {
                    case 255:
                    #ifdef HAVE_ED25519
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    case 448:
                    #ifdef HAVE_ED448
                        return PSA_SUCCESS;
                    #else
                        return PSA_ERROR_NOT_SUPPORTED;
                    #endif
                    
                    default:
                        return PSA_ERROR_INVALID_ARGUMENT;
                }
            #else
                return PSA_ERROR_NOT_SUPPORTED;
            #endif
            
            default:
                return PSA_ERROR_NOT_SUPPORTED;
        }
    }
    /* Check post-quantum key types */
    else if (is_pq) {
        return psa_pq_check_key_size_valid(type, bits);
    }
    
    return PSA_ERROR_NOT_SUPPORTED;
}

/* Get wolfCrypt hash type from PSA algorithm */
int wc_psa_get_hash_type(psa_algorithm_t alg)
{
    psa_algorithm_t hash_alg = PSA_ALG_SIGN_GET_HASH(alg);

    if (PSA_ALG_IS_RSA_OAEP(alg)) {
        hash_alg = PSA_ALG_RSA_OAEP_GET_HASH(alg);
    }
    
    switch (hash_alg) {
        case PSA_ALG_MD5:
            return WC_HASH_TYPE_MD5;
        
        case PSA_ALG_SHA_1:
            return WC_HASH_TYPE_SHA;
        
        case PSA_ALG_SHA_224:
            return WC_HASH_TYPE_SHA224;
        
        case PSA_ALG_SHA_256:
            return WC_HASH_TYPE_SHA256;
        
        case PSA_ALG_SHA_384:
            return WC_HASH_TYPE_SHA384;
        
        case PSA_ALG_SHA_512:
            return WC_HASH_TYPE_SHA512;
        
        case PSA_ALG_SHA_512_224:
            return WC_HASH_TYPE_SHA512_224;
        
        case PSA_ALG_SHA_512_256:
            return WC_HASH_TYPE_SHA512_256;
        
        default:
            return WC_HASH_TYPE_NONE;
    }
}

/* Get wolfCrypt RSA padding type from PSA algorithm */
int wc_psa_get_rsa_padding(psa_algorithm_t alg)
{
#ifdef NO_RSA
    (void)alg;
    return 0;
#else
    if (PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg)) {
        return WC_RSA_PKCSV15_PAD;
    }
    else if (PSA_ALG_IS_RSA_PSS(alg)) {
        return WC_RSA_PSS_PAD;
    }
    else if (alg == PSA_ALG_RSA_PKCS1V15_CRYPT) {
        return WC_RSA_PKCSV15_PAD;
    }
    else if (PSA_ALG_IS_RSA_OAEP(alg)) {
        return WC_RSA_OAEP_PAD;
    }
    
    return 0;
#endif
}

/* Get wolfCrypt ECC curve ID from PSA key type and size */
#if defined(HAVE_ECC)
int wc_psa_get_ecc_curve_id(psa_key_type_t type, size_t bits)
{
    psa_ecc_family_t curve = PSA_KEY_TYPE_ECC_GET_FAMILY(type);
    
    switch (curve) {
        case PSA_ECC_FAMILY_SECP_R1:
            switch (bits) {
                case 192:
                #ifdef HAVE_ECC192
                    return ECC_SECP192R1;
                #else
                    return ECC_CURVE_INVALID;
                #endif
                
                case 224:
                #ifdef HAVE_ECC224
                    return ECC_SECP224R1;
                #else
                    return ECC_CURVE_INVALID;
                #endif
                
                case 256:
                    return ECC_SECP256R1;
                
                case 384:
                    return ECC_SECP384R1;
                
                case 521:
                    return ECC_SECP521R1;
                
                default:
                    return ECC_CURVE_INVALID;
            }
        
        case PSA_ECC_FAMILY_SECP_K1:
            switch (bits) {
                case 192:
                #if defined(HAVE_ECC192) && defined(HAVE_ECC_KOBLITZ)
                    return ECC_SECP192K1;
                #else
                    return ECC_CURVE_INVALID;
                #endif
                
                case 224:
                #if defined(HAVE_ECC224) && defined(HAVE_ECC_KOBLITZ)
                    return ECC_SECP224K1;
                #else
                    return ECC_CURVE_INVALID;
                #endif
                
                case 256:
                    return ECC_SECP256K1;
                
                default:
                    return ECC_CURVE_INVALID;
            }
        
        case PSA_ECC_FAMILY_BRAINPOOL_P_R1:
            switch (bits) {
                case 256:
                    return ECC_BRAINPOOLP256R1;
                
                case 384:
                    return ECC_BRAINPOOLP384R1;
                
                case 512:
                    return ECC_BRAINPOOLP512R1;
                
                default:
                    return ECC_CURVE_INVALID;
            }

        case PSA_ECC_FAMILY_MONTGOMERY:
            switch (bits) {
                case 255:
                #ifdef HAVE_CURVE25519
                    return ECC_X25519;
                #else
                    return ECC_CURVE_INVALID;
                #endif

                case 448:
                #ifdef HAVE_CURVE448
                    return ECC_X448;
                #else
                    return ECC_CURVE_INVALID;
                #endif

                default:
                    return ECC_CURVE_INVALID;
            }
        
        default:
            return ECC_CURVE_INVALID;
    }
}
#else
int wc_psa_get_ecc_curve_id(psa_key_type_t type, size_t bits)
{
    (void)type;
    (void)bits;
    return -1;
}
#endif

#endif /* WOLFSSL_PSA_ENGINE */
