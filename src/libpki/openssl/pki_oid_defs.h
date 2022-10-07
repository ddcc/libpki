/* OpenCA libpki package
* (c) 2000-2006 by Massimiliano Pala and OpenCA Group
* All Rights Reserved
*
* ===================================================================
* Released under OpenCA LICENSE
*/

#ifndef OQS_H
#include <oqs/oqs.h>
#endif

#ifndef _LIBPKI_OID_DEFS_H
#define _LIBPKI_OID_DEFS_H

// GENERAL
# define LEVEL_OF_ASSURANCE_OID   		    "1.3.6.1.4.1.18227.50.1"
# define LEVEL_OF_ASSURANCE_NAME            "levelOfAssurance"
# define LEVEL_OF_ASSURANCE_DESC            "Level Of Assurance"

# define CERTIFICATE_USAGE_OID   		    "1.3.6.1.4.1.18227.50.2"
# define CERTIFICATE_USAGE_NAME             "certificateUsage"
# define CERTIFICATE_USAGE_DESC             "Certificate Usage"

# define CERTIFICATE_TEMPLATE_OID   		"1.3.6.1.4.1.18227.50.3"
# define CERTIFICATE_TEMPLATE_NAME          "certificateTemplate"
# define CERTIFICATE_TEMPLATE_DESC          "Certificate Template"

// PEN
# define OPENCA_OID							"1.3.6.1.4.1.18227"
# define OPENCA_NAME                        "OpenCA"
# define OPENCA_DESC                        "OpenCA Labs Private Enterprise Number"

// GENERIC
# define OPENCA_ALG_OID				            OPENCA_OID ".2"
# define OPENCA_ALG_PKEY_OID		            OPENCA_ALG_OID ".1"
# define OPENCA_ALG_SIGS_OID		            OPENCA_ALG_OID ".2"
# define OPENCA_ALG_KEMS_OID		            OPENCA_ALT_OID ".3"
# define OPENCA_ALG_HASH_OID		            OPENCA_ALT_OID ".4"
# define OPENCA_ALG_HMAC_OID		            OPENCA_ALT_OID ".5"
# define OPENCA_ALG_SYM_OID 		            OPENCA_ALT_OID ".6"

// =====================
// Public Key Algorithms
// =====================

// COMPOSITE KEY
# define OPENCA_ALG_PKEY_COMP_OID	            OPENCA_ALG_PKEY_OID ".1"
# define OPENCA_ALG_PKEY_COMP_NAME	            "COMPOSITE"
# define OPENCA_ALG_PKEY_COMP_DESC	            "Composite Key"

// ALT KEY
# define OPENCA_ALG_PKEY_ALT_OID    	        OPENCA_ALG_PKEY_OID ".2"
# define OPENCA_ALG_PKEY_ALT_NAME               "ALTERNATIVE"
# define OPENCA_ALG_PKEY_ALT_DESC               "Multiple Alternative Key"

// PQC
# define OPENCA_ALG_PKEY_PQC_OID    	        OPENCA_ALG_PKEY_OID ".1"

// FALCON
# define OPENCA_ALG_PKEY_PQC_FALCON_OID    	    OPENCA_ALG_PKEY_PQC_OID ".1"
# define OPENCA_ALG_PKEY_PQC_FALCON_NAME   	    "Falcon"
# define OPENCA_ALG_PKEY_PQC_FALCON_DESC   	    "Falcon Lattice-Based Crypto Scheme"

# define OPENCA_ALG_PKEY_PQC_FALCON512_OID    	OPENCA_ALG_PKEY_PQC_FALCON_OID ".1"
# define OPENCA_ALG_PKEY_PQC_FALCON512_NAME     "Falcon512"
# define OPENCA_ALG_PKEY_PQC_FALCON512_DESC    	"Falcon512 Key"

# define OPENCA_ALG_PKEY_PQC_FALCON1024_OID     OPENCA_ALG_PKEY_PQC_FALCON_OID ".2"
# define OPENCA_ALG_PKEY_PQC_FALCON1024_NAME    "Falcon1024"
# define OPENCA_ALG_PKEY_PQC_FALCON1024_DESC    "Falcon1024 Key"

# define OPENCA_ALG_PKEY_PQC_FALCONX_OID     OPENCA_ALG_PKEY_PQC_FALCON_OID ".3"
# define OPENCA_ALG_PKEY_PQC_FALCONX_NAME    "FalconX"
# define OPENCA_ALG_PKEY_PQC_FALCONX_DESC    "FalconX Key"

// DILITHIUM
# define OPENCA_ALG_PKEY_PQC_DILITHIUM_OID    	OPENCA_ALG_PKEY_PQC_OID ".2"
# define OPENCA_ALG_PKEY_PQC_DILITHIUM_NAME     "Dilithium"
# define OPENCA_ALG_PKEY_PQC_DILITHIUM_DESC     "Dilithium Lattice-Based Crypto Scheme"

# define OPENCA_ALG_PKEY_PQC_DILITHIUM3_OID    	OPENCA_ALG_PKEY_PQC_DILITHIUM_OID ".1"
# define OPENCA_ALG_PKEY_PQC_DILITHIUM3_NAME     "Dilithium3"
# define OPENCA_ALG_PKEY_PQC_DILITHIUM3_DESC     "Dilithium3 Key"

# define OPENCA_ALG_PKEY_PQC_DILITHIUM4_OID    	OPENCA_ALG_PKEY_PQC_DILITHIUM_OID ".2"
# define OPENCA_ALG_PKEY_PQC_DILITHIUM4_NAME     "Dilithium4"
# define OPENCA_ALG_PKEY_PQC_DILITHIUM4_DESC     "Dilithium4 Key"

# define OPENCA_ALG_PKEY_PQC_DILITHIUM5_OID    	OPENCA_ALG_PKEY_PQC_DILITHIUM_OID ".3"
# define OPENCA_ALG_PKEY_PQC_DILITHIUM5_NAME     "Dilithium5"
# define OPENCA_ALG_PKEY_PQC_DILITHIUM5_DESC     "Dilithium5 Key"

# define OPENCA_ALG_PKEY_PQC_DILITHIUMX_OID    	OPENCA_ALG_PKEY_PQC_DILITHIUM_OID ".4"
# define OPENCA_ALG_PKEY_PQC_DILITHIUMX_NAME     "DilithiumX"
# define OPENCA_ALG_PKEY_PQC_DILITHIUMX_DESC     "DilithiumX Key"

// ====================
// Composite Signatures
// ====================

# define OPENCA_ALG_SIGS_COMP_OID		        OPENCA_ALG_SIGS_OID ".1"
# define OPENCA_ALG_SIGS_COMP_NAME		        "Composite"
# define OPENCA_ALG_SIGS_COMP_DESC		        "Composite Key Signature"

# define OPENCA_ALG_SIGS_COMP_SHA1_OID	        OPENCA_ALG_SIGS_COMP_OID ".1"
# define OPENCA_ALG_SIGS_COMP_SHA1_NAME		    "CompositeWithSha1"
# define OPENCA_ALG_SIGS_COMP_SHA1_DESC		    "Composite Key Signature With SHA1"

# define OPENCA_ALG_SIGS_COMP_SHA256_OID	    OPENCA_ALG_SIGS_COMP_OID ".2"
# define OPENCA_ALG_SIGS_COMP_SHA256_NAME		"CompositeWithSha256"
# define OPENCA_ALG_SIGS_COMP_SHA256_DESC		"Composite Key Signature With SHA256"

# define OPENCA_ALG_SIGS_COMP_SHA384_OID	    OPENCA_ALG_SIGS_COMP_OID ".3"
# define OPENCA_ALG_SIGS_COMP_SHA384_NAME		"CompositeWithSha384"
# define OPENCA_ALG_SIGS_COMP_SHA384_DESC		"Composite Key Signature With SHA384"

# define OPENCA_ALG_SIGS_COMP_SHA512_OID	    OPENCA_ALG_SIGS_COMP_OID ".4"
# define OPENCA_ALG_SIGS_COMP_SHA512_NAME		"CompositeWithSha512"
# define OPENCA_ALG_SIGS_COMP_SHA512_DESC		"Composite Key Signature With SHA512"

# define OPENCA_ALG_SIGS_COMP_SHA3_256_OID	    OPENCA_ALG_SIGS_COMP_OID ".5"
# define OPENCA_ALG_SIGS_COMP_SHA3_256_NAME		"CompositeWithSha3At256"
# define OPENCA_ALG_SIGS_COMP_SHA3_256_DESC		"Composite Key Signature With SHA3_256"

# define OPENCA_ALG_SIGS_COMP_SHA3_384_OID	    OPENCA_ALG_SIGS_COMP_OID ".6"
# define OPENCA_ALG_SIGS_COMP_SHA3_384_NAME		"CompositeWithSha3At384"
# define OPENCA_ALG_SIGS_COMP_SHA3_384_DESC		"Composite Key Signature With SHA3_384"

# define OPENCA_ALG_SIGS_COMP_SHA3_512_OID	    OPENCA_ALG_SIGS_COMP_OID ".7"
# define OPENCA_ALG_SIGS_COMP_SHA3_512_NAME		"CompositeWithSha3At512"
# define OPENCA_ALG_SIGS_COMP_SHA3_512_DESC		"Composite Key Signature With SHA3_512"

# define OPENCA_ALG_SIGS_COMP_SHAKE128_OID	    OPENCA_ALG_SIGS_COMP_OID ".8"
# define OPENCA_ALG_SIGS_COMP_SHAKE128_NAME		"CompositeWithShake128"
# define OPENCA_ALG_SIGS_COMP_SHAKE128_DESC		"Composite Key Signature With SHAKE128"

# define OPENCA_ALG_SIGS_COMP_SHAKE256_OID	    OPENCA_ALG_SIGS_COMP_OID ".9"
# define OPENCA_ALG_SIGS_COMP_SHAKE256_NAME		"CompositeWithShake256"
# define OPENCA_ALG_SIGS_COMP_SHAKE256_DESC		"Composite Key Signature With SHAKE256"

// ======================
// Alternative Signatures
// ======================

# define OPENCA_ALG_SIGS_ALT_OID		            OPENCA_ALG_SIGS_OID ".2"
# define OPENCA_ALG_SIGS_ALT_NAME		            "MultiSig"
# define OPENCA_ALG_SIGS_ALT_DESC		            "Multiple Alternative Keys Signature"

# define OPENCA_ALG_SIGS_ALT_SHA1_OID		        OPENCA_ALG_SIGS_ALT_OID ".1"
# define OPENCA_ALG_SIGS_ALT_SHA1_NAME		        "MultiSigWithSha1"
# define OPENCA_ALG_SIGS_ALT_SHA1_DESC		        "Multiple Alternative Keys Signature With SHA1"

# define OPENCA_ALG_SIGS_ALT_SHA256_OID		        OPENCA_ALG_SIGS_ALT_OID ".2"
# define OPENCA_ALG_SIGS_ALT_SHA256_NAME		    "MultiSigWithSha256"
# define OPENCA_ALG_SIGS_ALT_SHA256_DESC		    "Multiple Alternative Keys Signature With SHA256"

# define OPENCA_ALG_SIGS_ALT_SHA384_OID		        OPENCA_ALG_SIGS_ALT_OID ".3"
# define OPENCA_ALG_SIGS_ALT_SHA384_NAME		    "MultiSigWithSha384"
# define OPENCA_ALG_SIGS_ALT_SHA384_DESC		    "Multiple Alternative Keys Signature With SHA384"

# define OPENCA_ALG_SIGS_ALT_SHA512_OID		        OPENCA_ALG_SIGS_ALT_OID ".4"
# define OPENCA_ALG_SIGS_ALT_SHA512_NAME		    "MultiSigWithSha512"
# define OPENCA_ALG_SIGS_ALT_SHA512_DESC		    "Multiple Alternative Keys Signature With SHA512"

# define OPENCA_ALG_SIGS_ALT_SHA3_256_OID		    OPENCA_ALG_SIGS_ALT_OID ".5"
# define OPENCA_ALG_SIGS_ALT_SHA3_256_NAME		    "MultiSigWithSha3At256"
# define OPENCA_ALG_SIGS_ALT_SHA3_256_DESC		    "Multiple Alternative Keys Signature With SHA3_256"

# define OPENCA_ALG_SIGS_ALT_SHA3_384_OID		    OPENCA_ALG_SIGS_ALT_OID ".6"
# define OPENCA_ALG_SIGS_ALT_SHA3_384_NAME		    "MultiSigWithSha3At384"
# define OPENCA_ALG_SIGS_ALT_SHA3_384_DESC		    "Multiple Alternative Keys Signature With SHA3_384"

# define OPENCA_ALG_SIGS_ALT_SHA3_512_OID		    OPENCA_ALG_SIGS_ALT_OID ".7"
# define OPENCA_ALG_SIGS_ALT_SHA3_512_NAME		    "MultiSigWithSha3At512"
# define OPENCA_ALG_SIGS_ALT_SHA3_512_DESC		    "Multiple Alternative Keys Signature With SHA3_512"

# define OPENCA_ALG_SIGS_ALT_SHAKE128_OID		    OPENCA_ALG_SIGS_ALT_OID ".8"
# define OPENCA_ALG_SIGS_ALT_SHAKE128_NAME		    "MultiSigWithShake128"
# define OPENCA_ALG_SIGS_ALT_SHAKE128_DESC		    "Multiple Alternative Keys Signatures With SHAKE128"

# define OPENCA_ALG_SIGS_ALT_SHAKE256_OID		    OPENCA_ALG_SIGS_ALT_OID ".9"
# define OPENCA_ALG_SIGS_ALT_SHAKE256_NAME		    "MultiSigWithShake256"
# define OPENCA_ALG_SIGS_ALT_SHAKE256_DESC		    "Multiple Alternative Keys Signature With SHAKE256"

// =======================
// Post-Quantum Signatures
// =======================

# define OPENCA_ALG_SIGS_PQC_OID  OPENCA_ALG_SIGS_OID ".999"

// Dilithium3 and Dilithium5
// -------------------------
# define OPENCA_ALG_SIGS_PQC_DILITHIUM_OID           OPENCA_ALG_SIGS_PQC_OID ".1"

// Dilithium Level 3

# define OPENCA_ALG_SIGS_PQC_DILITHIUM3_OID             OPENCA_ALG_SIGS_PQC_DILITHIUM_OID ".1"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM3_NAME            OQS_SIG_alg_dilithium_3
# define OPENCA_ALG_SIGS_PQC_DILITHIUM3_DESC            OQS_SIG_alg_dilithium_3 " Signature"

# define OPENCA_ALG_SIGS_PQC_DILITHIUM3_SHA256_OID      OPENCA_ALG_SIGS_PQC_DILITHIUM3_OID ".1"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM3_SHA256_NAME     OQS_SIG_alg_dilithium_3 "WithSha256"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM3_SHA256_DESC     OQS_SIG_alg_dilithium_3 " Signature With SHA256"

# define OPENCA_ALG_SIGS_PQC_DILITHIUM3_SHA384_OID      OPENCA_ALG_SIGS_PQC_DILITHIUM3_OID ".2"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM3_SHA384_NAME     OQS_SIG_alg_dilithium_3 "WithSha384"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM3_SHA384_DESC     OQS_SIG_alg_dilithium_3 " Signature With SHA384"

# define OPENCA_ALG_SIGS_PQC_DILITHIUM3_SHA512_OID      OPENCA_ALG_SIGS_PQC_DILITHIUM3_OID ".3"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM3_SHA512_NAME     OQS_SIG_alg_dilithium_3 "WithSha512"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM3_SHA512_DESC     OQS_SIG_alg_dilithium_3 " Signature With SHA512"

# define OPENCA_ALG_SIGS_PQC_DILITHIUM3_SHAKE128_OID    OPENCA_ALG_SIGS_PQC_DILITHIUM3_OID ".4"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM3_SHAKE128_NAME   OQS_SIG_alg_dilithium_3 "WithShake128"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM3_SHAKE128_DESC   OQS_SIG_alg_dilithium_3 " Signature With SHAKE128"

# define OPENCA_ALG_SIGS_PQC_DILITHIUM3_SHAKE256_OID    OPENCA_ALG_SIGS_PQC_DILITHIUM3_OID ".5"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM3_SHAKE256_NAME   OQS_SIG_alg_dilithium_3 "WithShake256"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM3_SHAKE256_DESC   OQS_SIG_alg_dilithium_3 " Signature With SHAKE256"

// Dilithium Level 5

# define OPENCA_ALG_SIGS_PQC_DILITHIUM5_OID             OPENCA_ALG_SIGS_PQC_DILITHIUM_OID ".2"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM5_NAME            OQS_SIG_alg_dilithium_5
# define OPENCA_ALG_SIGS_PQC_DILITHIUM5_DESC            OQS_SIG_alg_dilithium_5 " Signature"

# define OPENCA_ALG_SIGS_PQC_DILITHIUM5_SHA256_OID      OPENCA_ALG_SIGS_PQC_DILITHIUM5_OID ".6"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM5_SHA256_NAME     OQS_SIG_alg_dilithium_5 "WithSha256"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM5_SHA256_DESC     OQS_SIG_alg_dilithium_5 " Signature With SHA256"

# define OPENCA_ALG_SIGS_PQC_DILITHIUM5_SHA384_OID      OPENCA_ALG_SIGS_PQC_DILITHIUM5_OID ".7"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM5_SHA384_NAME     OQS_SIG_alg_dilithium_5 "WithSha384"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM5_SHA384_DESC     OQS_SIG_alg_dilithium_5 " Signature With SHA384"

# define OPENCA_ALG_SIGS_PQC_DILITHIUM5_SHA512_OID      OPENCA_ALG_SIGS_PQC_DILITHIUM5_OID ".8"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM5_SHA512_NAME     OQS_SIG_alg_dilithium_5 "WithSha512"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM5_SHA512_DESC     OQS_SIG_alg_dilithium_5 " Signature With SHA512"

# define OPENCA_ALG_SIGS_PQC_DILITHIUM5_SHAKE128_OID    OPENCA_ALG_SIGS_PQC_DILITHIUM5_OID ".9"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM5_SHAKE128_NAME   OQS_SIG_alg_dilithium_5 "WithShake128"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM5_SHAKE128_DESC   OQS_SIG_alg_dilithium_5 " Signature With SHAKE128"

# define OPENCA_ALG_SIGS_PQC_DILITHIUM5_SHAKE256_OID    OPENCA_ALG_SIGS_PQC_DILITHIUM5_OID ".10"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM5_SHAKE256_NAME   OQS_SIG_alg_dilithium_5 "WithShake256"
# define OPENCA_ALG_SIGS_PQC_DILITHIUM5_SHAKE256_DESC   OQS_SIG_alg_dilithium_5 " Signature With SHAKE256"

// Falcon512 and Falcon1024
// ------------------------

# define OPENCA_ALG_SIGS_PQC_FALCON_OID                 OPENCA_ALG_SIGS_PQC_OID ".2"

// Falcon Level 512

# define OPENCA_ALG_SIGS_PQC_FALCON512_OID              OPENCA_ALG_SIGS_PQC_FALCON_OID ".1"
# define OPENCA_ALG_SIGS_PQC_FALCON512_NAME             "Falcon512"
# define OPENCA_ALG_SIGS_PQC_FALCON512_DESC             "Falcon512 Signature"

# define OPENCA_ALG_SIGS_PQC_FALCON512_SHA256_OID       OPENCA_ALG_SIGS_PQC_FALCON512_OID ".1"
# define OPENCA_ALG_SIGS_PQC_FALCON512_SHA256_NAME      "Falcon512WithSha256"
# define OPENCA_ALG_SIGS_PQC_FALCON512_SHA256_DESC      "Falcon512 Signature With SHA256"

# define OPENCA_ALG_SIGS_PQC_FALCON512_SHA384_OID       OPENCA_ALG_SIGS_PQC_FALCON512_OID ".2"
# define OPENCA_ALG_SIGS_PQC_FALCON512_SHA384_NAME      "Falcon512WithSha384"
# define OPENCA_ALG_SIGS_PQC_FALCON512_SHA384_DESC      "Falcon512 Signature With SHA384"

# define OPENCA_ALG_SIGS_PQC_FALCON512_SHA512_OID       OPENCA_ALG_SIGS_PQC_FALCON512_OID ".3"
# define OPENCA_ALG_SIGS_PQC_FALCON512_SHA512_NAME      "Falcon512WithSha512"
# define OPENCA_ALG_SIGS_PQC_FALCON512_SHA512_DESC      "Falcon512 Signature With SHA512"

# define OPENCA_ALG_SIGS_PQC_FALCON512_SHAKE128_OID     OPENCA_ALG_SIGS_PQC_FALCON512_OID ".4"
# define OPENCA_ALG_SIGS_PQC_FALCON512_SHAKE128_NAME    "Falcon512WithShake128"
# define OPENCA_ALG_SIGS_PQC_FALCON512_SHAKE128_DESC    "Falcon512 Signature With SHAKE128"

# define OPENCA_ALG_SIGS_PQC_FALCON512_SHAKE256_OID     OPENCA_ALG_SIGS_PQC_FALCON512_OID ".5"
# define OPENCA_ALG_SIGS_PQC_FALCON512_SHAKE256_NAME    "Falcon512WithShake256"
# define OPENCA_ALG_SIGS_PQC_FALCON512_SHAKE256_DESC    "Falcon512 Signature With SHAKE256"

// Falcon Level 1024

# define OPENCA_ALG_SIGS_PQC_FALCON1024_OID             OPENCA_ALG_SIGS_PQC_FALCON_OID ".2"
# define OPENCA_ALG_SIGS_PQC_FALCON1024_NAME            "Falcon1024"
# define OPENCA_ALG_SIGS_PQC_FALCON1024_DESC            "Falcon1024 Signature"

# define OPENCA_ALG_SIGS_PQC_FALCON1024_SHA256_OID      OPENCA_ALG_SIGS_PQC_FALCON512_OID ".6"
# define OPENCA_ALG_SIGS_PQC_FALCON1024_SHA256_NAME     "Falcon1024WithSha256"
# define OPENCA_ALG_SIGS_PQC_FALCON1024_SHA256_DESC     "Falcon1024 Signature With SHA256"

# define OPENCA_ALG_SIGS_PQC_FALCON1024_SHA384_OID      OPENCA_ALG_SIGS_PQC_FALCON512_OID ".7"
# define OPENCA_ALG_SIGS_PQC_FALCON1024_SHA384_NAME     "Falcon1024WithSha384"
# define OPENCA_ALG_SIGS_PQC_FALCON1024_SHA384_DESC     "Falcon1024 Signature With SHA384"

# define OPENCA_ALG_SIGS_PQC_FALCON1024_SHA512_OID      OPENCA_ALG_SIGS_PQC_FALCON512_OID ".8"
# define OPENCA_ALG_SIGS_PQC_FALCON1024_SHA512_NAME     "Falcon1024WithSha512"
# define OPENCA_ALG_SIGS_PQC_FALCON1024_SHA512_DESC     "Falcon1024 Signature With SHA512"

# define OPENCA_ALG_SIGS_PQC_FALCON1024_SHAKE128_OID    OPENCA_ALG_SIGS_PQC_FALCON512_OID ".9"
# define OPENCA_ALG_SIGS_PQC_FALCON1024_SHAKE128_NAME   "Falcon1024WithShake128"
# define OPENCA_ALG_SIGS_PQC_FALCON1024_SHAKE128_DESC   "Falcon1024 Signature With SHAKE128"

# define OPENCA_ALG_SIGS_PQC_FALCON1024_SHAKE256_OID    OPENCA_ALG_SIGS_PQC_FALCON512_OID ".10"
# define OPENCA_ALG_SIGS_PQC_FALCON1024_SHAKE256_NAME   "Falcon1024WithShake256"
# define OPENCA_ALG_SIGS_PQC_FALCON1024_SHAKE256_DESC   "Falcon1024 Signature With SHAKE256"

// =======================
// Initialization Function
// =======================

int PKI_X509_OID_init();


#endif // End of _LIBPKI_POST_QUANTUM_SIGS_H
