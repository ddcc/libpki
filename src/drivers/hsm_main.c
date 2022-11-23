/* HSM Object Management Functions */

#include <libpki/pki.h>

// Small Hack - taps into OpenSSL internals.. needed for setting the right
// algorithm for signing

#ifdef EVP_MD_FLAG_PKEY_METHOD_SIGNATURE
# define ENABLE_AMETH	1
#endif

#ifdef ENABLE_AMETH
typedef struct my_meth_st {
  int pkey_id;
  int pkey_base_id;
  unsigned long pkey_flags;
  char *pem_str;
  char *info;
} LIBPKI_METH;
#endif

/* --------------------------- Static function(s) ------------------------- */

/*
static int __set_algIdentifier (PKI_X509_ALGOR_VALUE   * alg, 
	                            const PKI_DIGEST_ALG   * digest,
	                            const PKI_X509_KEYPAIR * key) {

	PKI_X509_KEYPAIR_VALUE *pkey = NULL;
	  // KeyPair Pointer

	int def_nid;

	int pkey_type = 0;
	int param_type = V_ASN1_UNDEF;
	  // Parameter Type for Signature

	PKI_DIGEST_ALG * md = NULL;
	  // Digest to use

	EVP_MD_CTX *ctx = NULL;
	EVP_PKEY_CTX *pkctx = NULL;
	  // EVP_PKEY_CTX for signing

	// Input Checks
	if (!key || !key->value || !digest || !alg ) 
		return PKI_ERROR(PKI_ERR_PARAM_NULL, NULL);

	// Gets the KeyPair Pointer from the X509 structure
	pkey = key->value;

    if (EVP_PKEY_get_default_digest_nid(pkey, &def_nid) == 2
            && def_nid == NID_undef) {
        // The signing algorithm requires there to be no digest
        md = NULL;
    }

    if ((ctx = EVP_MD_CTX_new()) == NULL) {
		PKI_log_err("Cannot Allocate Digest Context");
        return 0;
	}

    if (!EVP_MD_CTX_init(ctx) || !EVP_DigestSignInit(ctx, &pkctx, md, NULL, pkey)) {
    	PKI_log_err("Cannot Initialize DigestSignInit");
        return 0;
    }

    pkey_type = EVP_MD_CTX_type(ctx);
    PKI_log_err("DEBUG: pkey_type (new) = %d (%s)",
    	pkey_type, PKI_ALGOR_ID_txt(pkey_type));

    
    // if (EVP_PKEY_get_default_digest_nid(pkey, &def_nid) == 2
    // 		&& def_nid == NID_undef) {
    //
    //  // The signing algorithm requires there to be no digest
    //    digest = NULL;
    //
    //	    PKI_log_err("DIGEST ALGORITHM => %p", digest);
    // } else {
    //      PKI_log_err("DIGEST ALGORITHM => %s", 
    //    	PKI_DIGEST_ALG_get_parsed(digest));
    // }

	// Gets the Signature Algorithm
	pkey_type = EVP_MD_pkey_type(digest);
	PKI_log_err("DEBUG: pkey_type (old) = %d", pkey_type);

#ifdef ENABLE_AMETH

	struct my_meth_st *ameth     = NULL;
	  // Pointer to the aMeth structure

	// Gets the Reference to the Key's Method
	if ((ameth = (struct my_meth_st *) pkey->ameth) == NULL)
		return PKI_ERROR(PKI_ERR_POINTER_NULL, "Missing aMeth pointer.");

	// Gets the right parameter
	if (ameth->pkey_flags & ASN1_PKEY_SIGPARAM_NULL) param_type = V_ASN1_NULL;
	else param_type = V_ASN1_UNDEF;

#else // Else for aMeth

	// Special Case for RFC 2459 (Omit Parameters)
	if (pkey_type == PKI_ALGOR_DSA_SHA1) param_type = V_ASN1_NULL;
	else param_type = V_ASN1_UNDEF;

	if (alg->parameter) ASN1_TYPE_free(alg->parameter);
	alg->parameter = NULL;

#endif // End of aMeth

	PKI_log_err("Set Algorithm: pkey_type = %d (%s)",
		pkey_type, PKI_ALGOR_ID_txt(pkey_type));

	// Sets the Algorithms details
	if (!X509_ALGOR_set0(alg, OBJ_nid2obj(pkey_type), param_type, NULL))
		return PKI_ERROR(PKI_ERR_ALGOR_SET, "Cannot set the algorithm");

	// All Done
	return PKI_OK;

}
*/


/*! \brief Returns the errno from the crypto layer */

unsigned long HSM_get_errno (const HSM *hsm )
{
	const HSM *my_hsm = NULL;

	if (!hsm) my_hsm = (HSM *) HSM_OPENSSL_get_default();
	else my_hsm = hsm;

	if ( my_hsm && my_hsm->callbacks && my_hsm->callbacks->get_errno)
	{
		return my_hsm->callbacks->get_errno();
	}

	return 0;
}

/*! \brief Returns the description of the passed error number from the
 *         crypto layer */

char *HSM_get_errdesc ( unsigned long err, const HSM *hsm )
{
	const HSM *my_hsm = NULL;

	// If no hsm was provided, let's get the default one
	if (!hsm) my_hsm = (HSM *) HSM_OPENSSL_get_default();
	else my_hsm = hsm;
	
	// If no error number was provided, let's get the latest
	if (err == 0) err = HSM_get_errno(my_hsm);

	if (my_hsm && my_hsm->callbacks && my_hsm->callbacks->get_errdesc)
	{
		return my_hsm->callbacks->get_errdesc(err, NULL, 0);
	}

	return NULL;
}

/*! \brief Returns the default HSM structure (software)
 *
 * The returned HSM * points to a static structure that does not need
 * to be freed.
 */
 
const HSM *HSM_get_default( void ) {
	return HSM_OPENSSL_get_default();
}

/*! \brief Allocates a new HSM structure
 *
 * Allocates a new HSM structure and initialize the callbacks functions.
 * The driver is the crypto driver to be used (e.g., openssl or kmf),
 * while the name is the name of the HSM (e.g., LunaCA3)
 */

HSM *HSM_new( const char * const dir,
			  const char * const name ) {

	HSM  * hsm   = NULL;
	char * url_s = NULL;
	char * buff  = NULL;

	PKI_CONFIG *conf = NULL;
	char *type = NULL;

	PKI_init_all();

	if( !name ) {
		/* If no name is passed, we generate a new software token */
		return HSM_OPENSSL_new( NULL );
	}

	if((url_s = PKI_CONFIG_find_all( dir, name, PKI_DEFAULT_HSM_DIR )) 
								== NULL ) {
		PKI_log_debug( "Can not find config file (%s/%s)\n", dir, name);
		return (NULL);
	}

	if((conf = PKI_CONFIG_load( url_s )) == NULL ) {
		PKI_log_debug( "Can not load config from %s", url_s );
		goto err;
	}

	if((buff = PKI_Malloc ( BUFF_MAX_SIZE )) == NULL ) {
		goto err;
	}

	/* Let's generate the right searching string with the namespace
	   prefix */
	if((type = PKI_CONFIG_get_value ( conf, "/hsm/type")) == NULL ) {
		/* No type in the config! */
		PKI_log_debug("ERROR, No HSM type in the config!");
		type = strdup("software");
	}

	if( strcmp_nocase(type,"software") == 0 ) {
		if((hsm = HSM_OPENSSL_new( conf )) == NULL ) {
			PKI_log_debug("ERROR, Can not generate software HSM object!");
		} else {
			hsm->type = HSM_TYPE_SOFTWARE;
		}
#ifdef HAVE_ENGINE
	} else if( strcmp_nocase(type,"engine") == 0 ) {
		if((hsm = HSM_ENGINE_new( conf )) == NULL ) {
			PKI_log_debug("ERROR, Can not generate engine HSM object!");
		} else {
			hsm->type = HSM_TYPE_ENGINE;
		}
#endif
	} else if( strcmp_nocase(type,"pkcs11") == 0 ) {
		if((hsm = HSM_PKCS11_new( conf )) == NULL ) {
			PKI_log_debug("ERROR, Can not generate engine HSM object!");
		} else {
			hsm->type = HSM_TYPE_PKCS11;
		}
#ifdef ENABLE_KMF
	} else if( strcmp_nocase(type,"kmf") == 0 ) {
		if((hsm = HSM_KMF_new( conf )) == NULL ) {
			PKI_log_debug("ERROR, Can not generate kmf HSM object!\n");
		} else {
			hsm->type = HSM_TYPE_KMF;
		}
#endif
	} else {
		PKI_log_debug( "Unknown HSM type (%s)", type );
		goto err;
	}

	if ( ( hsm != NULL ) && (HSM_init ( hsm ) != PKI_OK) ) {
		goto err;
	}

	// Let' see if we can enforce the FIPS mode (optional, therefore
	// errors are not fatal if PKI_is_fips_mode return PKI_ERR)
	if (PKI_is_fips_mode() == PKI_OK)
	{
			if (HSM_set_fips_mode(hsm, 1) == PKI_OK)
			{
				PKI_log_debug("HSM created in FIPS mode");
			}
			else
			{
				PKI_log_err("Can not create HSM in FIPS mode");
				goto err;
			}
	}
	else
	{
		PKI_log_debug("HSM created in non-FIPS mode");
	}

	// Free memory
	if (type) PKI_Free(type);
	if (conf) PKI_CONFIG_free(conf);
	if (url_s) PKI_Free(url_s);

	// Returns the value
	return (hsm);

err:

	// Free used memory
	if (conf) PKI_CONFIG_free(conf);
	if (url_s) PKI_Free(url_s);
	if (hsm) HSM_free(hsm);
	if (type) PKI_Free(type);

	// Returns a NULL pointer
	return NULL;
}

/*! \brief Allocates a new HSM structure and initializes it in FIPS mode
 *
 * Allocates a new HSM structure and initialize the callbacks functions
 * in FIPS mode. The driver is the crypto driver to be used (e.g., openssl
 * or kmf), while the name is the name of the HSM (e.g., LunaCA3)
 *
 * If the HSM does not support FIPS mode or other errors occur, this function
 * returns NULL
 */

HSM *HSM_new_fips(const char * const dir,
				  const char * const name) {
	HSM *ret = NULL;

	// Let's invoke the normal initialization
	ret = HSM_new(dir, name);
	if (!ret) return NULL;

	// Checks if the HSM is operating in FIPS mode
	if (PKI_is_fips_mode() == PKI_OK && HSM_is_fips_mode(ret) == PKI_ERR)
	{
		// Since this init requires FIPS mode, let's return an error
		PKI_log_err("Can not create HSM in FIPS mode");
		HSM_free(ret);
		return NULL;
	}

	// Return the HSM
	return ret;
}

int HSM_free ( HSM *hsm ) {

	if( !hsm ) return (PKI_ERR);

	if( hsm && hsm->callbacks && hsm->callbacks->free )
	{
		hsm->callbacks->free ( (void *) hsm, hsm->config );
	}
	else
	{
		/* Error! The driver should provide a free callback! */
		PKI_log_err("hsm (%s) does not provide a free function!", hsm->description );
		if ( hsm ) PKI_Free ( hsm );

		return (PKI_ERR);
	}

	return (PKI_OK);
}

/* -------------------------- HSM Initialization ----------------------- */


/*!
 * \brief Initializes the HSM
 */
int HSM_init( HSM *hsm ) {

	if( !hsm || !hsm->callbacks ) return (PKI_ERR);

	/* Call the init function provided by the hsm itself */
	if( hsm->callbacks->init )
	{
		return (hsm->callbacks->init(hsm, hsm->config ));
	}
	else
	{
		/* No init function is provided (not needed ??!?!) */
		PKI_log_debug("hsm (%s) does not provide an init "
				"function!\n", hsm->description );
	}

	return(PKI_OK);
}

/*!
 * \brief Initializes the HSM in FIPS mode, returns an error if FIPS
 *        mode is not available for the HSM
 */
int HSM_init_fips (HSM *hsm)
{
	// Let's do the normal initialization
	if (HSM_init(hsm) == PKI_ERR) return PKI_ERR;

	// Now let's set the fips mode
	if (!HSM_set_fips_mode(hsm, 1)) return PKI_ERR;

	return (PKI_OK);
}

/* -------------------------- Access control to HSM ----------------------- */

int HSM_login ( HSM *hsm, PKI_CRED *cred ) {

	if (!hsm) return (PKI_ERR);

	if ( hsm->callbacks->login ) {
		return ( hsm->callbacks->login(hsm, cred ));
	} else {
		/* No login required by the HSM */
		PKI_log_debug("No login function for selected HSM");
	}

	return ( PKI_OK );
}

int HSM_logout ( HSM *hsm ) {

	if (!hsm || !hsm->callbacks ) return (PKI_ERR);

	if ( hsm->callbacks && hsm->callbacks->logout ) {
		return ( hsm->callbacks->logout( hsm ));
	} else {
		/* No login required by the HSM */
		PKI_log_debug("No login function for selected HSM");
	}

	return ( PKI_OK );
}


/* -------------------------- FIPS mode for HSM ----------------------- */

int HSM_set_fips_mode(const HSM *hsm, int k)
{
	if (!hsm) hsm = HSM_get_default();
	if (!hsm) return PKI_ERR;

	if (hsm->callbacks && hsm->callbacks->set_fips_mode)
	{
		return hsm->callbacks->set_fips_mode(hsm, k);
	}
	else
	{
		// If no FIPS mode is available, let's return 0 (false)
		return PKI_ERR;
	}
}

int HSM_is_fips_mode(const HSM *hsm)
{
	if (!hsm) hsm = HSM_get_default();
	if (!hsm) return PKI_ERR;

	if (hsm->callbacks && hsm->callbacks->is_fips_mode)
	{
		return hsm->callbacks->is_fips_mode(hsm);
	}
	else
	{
		return PKI_ERR;
	}
}

/* -------------------------- General Crypto HSM ----------------------- */

int HSM_set_sign_algor ( PKI_X509_ALGOR_VALUE *alg, HSM *hsm ) {

	int ret = PKI_OK;

	// Input Checks
	if (!alg) return PKI_ERROR(PKI_ERR_PARAM_NULL, "No algorithm passed!");

	// Sets the algorithm if it is an hardware token
	if (hsm && hsm->callbacks && hsm->callbacks->sign_algor) {

		// Using the HSM callback
		PKI_log_debug("Setting the signature algorithm for selected HSM");
		ret = hsm->callbacks->sign_algor(hsm, alg);
	}

	// All Done
	return (ret);
}

/* ------------------------ General PKI Signing ---------------------------- */

/* !\brief Signs the data from a PKI_MEM structure by using the
 *      passed key and digest algorithm. 
 *
 * This function signs the data passed in the PKI_MEM structure.
 * Use PKI_DIGEST_ALG_NULL for using no hash algorithm when calculating
 * the signature.
 * Use NULL for the digest (PKI_DIGEST_ALG) pointer to use the data signing
 * functions directly (i.e., signing the PKI_MEM data directly instead of
 * first performing the digest calculation and then generating the signture
 * over the digest)
 * 
 * @param der The pointer to a PKI_MEM structure with the data to sign
 * @param digest The pointer to a PKI_DIGEST_ALG method
 * @param key The pointer to the PKI_X509_KEYPAIR used for signing
 * @return A PKI_MEM structure with the signature value.
 */

int PKI_X509_sign(PKI_X509               * x, 
		          const PKI_DIGEST_ALG   * digest,
		          const PKI_X509_KEYPAIR * key) {

	PKI_MEM *der = NULL;
	PKI_MEM *sig = NULL;
	  // Data structure for the signature

	PKI_STRING * sigPtr = NULL;
	  // Pointer for the Signature in the PKIX data

	PKI_X509_KEYPAIR_VALUE * pkey = NULL;
	  // Internal Value

	// Input Checks
	if (!x || !x->value || !key || !key->value ) 
		return PKI_ERROR(PKI_ERR_PARAM_NULL, NULL);

	// Sets the default Algorithm if none is provided
	if (!digest) digest = PKI_DIGEST_ALG_get_default(key);

	// Extracts the internal value
	pkey = PKI_X509_get_value(key);
	if (!pkey) {
		PKI_ERROR(PKI_ERR_PARAM_NULL, "Missing Key's Internal Value");
		return PKI_ERR;
	}

	// Let's Get The signing OID
	int sig_nid = -1;
	int pkey_nid = EVP_PKEY_id(pkey);
	int digest_nid = EVP_MD_nid(digest);

	if (1 != OBJ_find_sigid_by_algs(&sig_nid, digest_nid, pkey_nid)) {
		PKI_DEBUG("Cannot Get The Signing Algorithm for %s with %s",
			PKI_ID_get_txt(pkey_nid), digest ? PKI_ID_get_txt(digest_nid) : "NULL");
	} else {
		// If the find routine returns 1 it was successful, however
		// for PQC it seems to return NID_undef for the sig_nid, this fixes it
		if (sig_nid == NID_undef) sig_nid = EVP_PKEY_id(pkey);
	}

	// Debugging Information
	PKI_DEBUG("Signing Algorithm Should be: %s", PKI_ID_get_txt(sig_nid));
	PKI_DEBUG("Digest Signing Algorithm: %s", PKI_ID_get_txt(digest_nid));

	// Sets the right OID for the signature
	ASN1_item_sign(x->it, 
	               PKI_X509_get_data(x, PKI_X509_DATA_SIGNATURE_ALG1),
                   PKI_X509_get_data(x, PKI_X509_DATA_SIGNATURE_ALG2),
                   NULL,
				   NULL,
                   pkey,
				   ((digest == PKI_DIGEST_ALG_NULL) ? NULL : digest));

	// Retrieves the DER representation of the data to be signed
	if ((der = PKI_X509_get_tbs_asn1(x)) == NULL) {
		// Logs the issue
		PKI_DEBUG("Can not get the DER representation of the PKIX data via tbs func");
		// Builds the DER representation in a PKI_MEM structure
		if ((der = PKI_X509_put_mem(x, PKI_DATA_FORMAT_ASN1, 
		                                           NULL, NULL )) == NULL) {
			// Logs the issue
			PKI_DEBUG("Can not get the DER representation directly, aborting.");
			// Can not encode into DER
			return PKI_ERROR(PKI_ERR_DATA_ASN1_ENCODING, NULL);
		}
	}

	// Generates the Signature
	if ((sig = PKI_sign(der, digest, key)) == NULL) {
		// Error while creating the signature, aborting
		if (der) PKI_MEM_free(der);
		// Report the issue
		return PKI_ERROR(PKI_ERR_SIGNATURE_CREATE, NULL);
	}

	// der work is finished, let's free the memory
	if (der) PKI_MEM_free(der);
	der = NULL;

	// Gets the reference to the X509 signature field
	if ((sigPtr = PKI_X509_get_data(x,
		                            PKI_X509_DATA_SIGNATURE)) == NULL) {
		// Error: Can not retrieve the generated signature, aborting
		PKI_MEM_free (sig);
		// Return the error
		return PKI_ERROR(PKI_ERR_POINTER_NULL, "Can not get signature data");
	}

	// TODO: Check if we need to free this memory or not
	// if (signature->data) PKI_Free(signature->data);

	// Transfer the ownership of the generated signature data (sig)
	// to the signature field in the X509 structure (signature)
	sigPtr->data   = sig->data;
	sigPtr->length = (int) sig->size;

	// Sets the flags into the signature field
	sigPtr->flags &= ~(ASN1_STRING_FLAG_BITS_LEFT|0x07);
	sigPtr->flags |= ASN1_STRING_FLAG_BITS_LEFT;

	// We can not free the data in the sig PKI_MEM because that is
	// actually owned by the signature now, so let's change the
	// data pointer and then free the PKI_MEM data structure
	sig->data = NULL;
	sig->size = 0;

	// Now we can free the signature mem
	PKI_MEM_free(sig);

	return PKI_OK;

}

/*! \brief General signature function on data */

PKI_MEM *PKI_sign(const PKI_MEM          * der,
		          const PKI_DIGEST_ALG   * alg,
		          const PKI_X509_KEYPAIR * key ) {

	PKI_MEM *sig = NULL;
	const HSM *hsm = NULL;

	// Input check
	if (!der || !der->data || !key || !key->value)	{
		PKI_ERROR(PKI_ERR_PARAM_NULL, NULL);
		return NULL;
	}

	// If no HSM is provided, let's get the default one
	hsm = (key->hsm != NULL ? key->hsm : HSM_get_default());

	// Requires the use of the HSM's sign callback
	if (hsm && hsm->callbacks && hsm->callbacks->sign) {

		// Generates the signature by using the HSM callback
		if ((sig = hsm->callbacks->sign(
			           (PKI_MEM *)der, 
			           (PKI_DIGEST_ALG *)alg, 
			           (PKI_X509_KEYPAIR *)key)) == NULL) {

			// Error: Signature was not generated
			PKI_DEBUG("Can not generate signature (returned from sign cb)");
		}

	} else {

		// There is no callback for signing the X509 structure
		PKI_ERROR(PKI_ERR_SIGNATURE_CREATE_CALLBACK,
			  "No sign callback for key's HSM");

		// Free Memory
		PKI_MEM_free(sig);

		// All Done
		return NULL;
	}

	// Let's return the output of the signing function
	return sig;
}

/*!
 * \brief Verifies a PKI_X509 by using a key from a certificate
 */

int PKI_X509_verify_cert(const PKI_X509 *x, const PKI_X509_CERT *cert) {

	const PKI_X509_KEYPAIR *kval = NULL;

	PKI_X509_KEYPAIR *kp = NULL;

	int ret = -1;

	// Input Check
	if (!x || !x->value || !cert || !cert->value)
		return PKI_ERROR(PKI_ERR_PARAM_NULL, NULL);

	// Gets the internal value of the public key from the certificate
	kval = PKI_X509_CERT_get_data(cert, PKI_X509_DATA_PUBKEY);
	if (!kval) return PKI_ERR;

	// Use the internal value to generate a new PKI_X509_KEYPAIR
	kp = PKI_X509_new_value(PKI_DATATYPE_X509_KEYPAIR, 
				            (PKI_X509_KEYPAIR_VALUE *)kval,
				            NULL);

	// Checks if the operation was successful
	if ( !kp ) return PKI_ERR;

	// Verifies the certificate by using the extracted public key
	ret = PKI_X509_verify(x, kp);

	// Take back the ownership of the internal value (avoid freeing
	// the memory when freeing the memory associated with the
	// PKI_X509_KEYPAIR data structure)
	kp->value = NULL;

	// Free the Memory
	PKI_X509_KEYPAIR_free(kp);
	
	return ret;
}

/*!
 * \brief Verifies a signature on a PKI_X509 object (not for PKCS7 ones)
 */

int PKI_X509_verify(const PKI_X509 *x, const PKI_X509_KEYPAIR *key ) {

	int ret = PKI_ERR;
	const HSM *hsm = NULL;

	PKI_MEM *data = NULL;
	PKI_MEM *sig = NULL;

	PKI_STRING *sig_value = NULL;
	PKI_X509_ALGOR_VALUE *alg = NULL;

	// Make sure the library is initialized
	PKI_init_all();

	// Input Checks
	if (!x || !x->value || !key || !key->value) {

		// Checks the X509 structure to verify
		if (!x || !x->value)
			return PKI_ERROR(PKI_ERR_PARAM_NULL, "Missing data to verify");

		// Checks the key value
		if (!key || !key->value)
			return PKI_ERROR(PKI_ERR_PARAM_NULL, "Missing keypair to verify with");
	}

	// Gets the reference to the HSM to use
	hsm = key->hsm != NULL ? key->hsm : HSM_get_default();

	// Gets the algorithm from the X509 data
	if (( alg = PKI_X509_get_data(x, PKI_X509_DATA_ALGORITHM)) == NULL) {

		// Reports the error
		return PKI_ERROR(PKI_ERR_ALGOR_UNKNOWN,
			"Can not get algorithm from object!");
	}

	// Gets the DER representation of the data to be signed

	// if ((data = PKI_X509_get_der_tbs(x)) == NULL) {
	// if ((data = PKI_X509_get_data(x, PKI_X509_DATA_TBS_MEM_ASN1)) == NULL) {
	if ((data = PKI_X509_get_tbs_asn1(x)) == NULL) {
		return PKI_ERROR(PKI_ERR_DATA_ASN1_ENCODING, 
			"Can not get To Be signed object!");
	}

	// Gets a reference to the Signature field in the X509 structure
	if ((sig_value = PKI_X509_get_data(x, 
					PKI_X509_DATA_SIGNATURE)) == NULL) {

		// Free the memory
		PKI_MEM_free(data);

		// We could not get the reference to the signature field
		return PKI_ERROR(PKI_ERR_POINTER_NULL,
			"Can not get Signature field from the X509 object!");
	}

	// Copies the signature data structure from the sig_value (PKI_STRING)
	// of the X509 structure to the sig one (PKI_MEM)
	if ((sig = PKI_MEM_new_data((size_t)sig_value->length,
							(unsigned char *)sig_value->data)) == NULL) {

		// Free memory
		PKI_MEM_free(data);

		// Reports the memory error
		return PKI_ERR;
	}

	// Uses the callback to verify the signature that was copied
	// in the sig (PKI_MEM) structure
	if (hsm && hsm->callbacks && hsm->callbacks->verify) {

		// Debugging Info
		PKI_log_debug( "HSM verify() callback called " );

		// Calls the callback function
		ret = hsm->callbacks->verify(data,
					     sig,
					     alg,
					     (PKI_X509_KEYPAIR *)key );

	} else {

		// If there is no verify callback, let's call the internal one
		ret = PKI_verify_signature(data, sig, alg, key);

	}

	// Free the allocated memory
	if ( data ) PKI_MEM_free ( data );
	if ( sig  ) PKI_MEM_free ( sig  );

	// Provides some additional information in debug mode
	if (ret != PKI_OK) {
		PKI_log_debug("Crypto Layer Error: %s (%d)", 
			HSM_get_errdesc(HSM_get_errno(hsm), hsm), 
			HSM_get_errno(hsm));
	}

	return (ret);
}

/*! \brief Verifies a signature */

int PKI_verify_signature(const PKI_MEM              * data,
                         const PKI_MEM              * sig,
                         const PKI_X509_ALGOR_VALUE * alg,
                         const PKI_X509_KEYPAIR     * key ) {
	int v_code = 0;
	EVP_MD_CTX *ctx = NULL;
	const PKI_DIGEST_ALG *dgst = NULL;

	// Input Checks
	if( !data || !data->data || !sig || !sig->data ||
			 !alg || !key || !key->value )  {

		// Reports the Input Error
		return PKI_ERROR(PKI_ERR_PARAM_NULL, NULL);
	}

	// Gets the Digest Algorithm to verify with
	if ((dgst = PKI_X509_ALGOR_VALUE_get_digest(alg)) == PKI_ID_UNKNOWN) {

		// Reports the error
		return PKI_ERROR(PKI_ERR_ALGOR_UNKNOWN,  NULL);
	}

	// Creates and Initializes a new crypto context (CTX)
	if ((ctx = EVP_MD_CTX_new()) == NULL) {

		// Can not alloc memory, let's report the error
		PKI_ERROR(PKI_ERR_MEMORY_ALLOC, NULL);
	}

	// Initializes the new CTX
	EVP_MD_CTX_init(ctx);

	// Initializes the Verify Function
	if ((EVP_VerifyInit_ex(ctx,dgst, NULL)) == 0) {

		// Error in initializing the signature verification function
		PKI_log_err("Signature Verify Initialization (Crypto Layer Error): %s (%d)", 
			HSM_get_errdesc(HSM_get_errno(NULL), NULL), 
			HSM_get_errno(NULL));

		// Done working
		goto err;
	}

	// Updates the Verify function
	if ((v_code = EVP_VerifyUpdate(ctx, (unsigned char *)data->data,
					data->size)) <= 0 ) {

		// Reports the error
		PKI_log_err("Signature Verify Update (Crypto Layer Error): %s (%d - %d)", 
			HSM_get_errdesc(HSM_get_errno(NULL), NULL), v_code, 
			HSM_get_errno(NULL));

		// Done working
		goto err;
	}

	// Finalizes the Verify function
	if ((v_code = EVP_VerifyFinal(ctx, (unsigned char *)sig->data,
                        (unsigned int)sig->size, key->value )) <= 0 ) {

		// Reports the error
		PKI_log_err("Signature Verify Final Failed (Crypto Layer Error): %s (%d - %d)", 
			HSM_get_errdesc(HSM_get_errno(NULL), NULL), v_code,
			HSM_get_errno(NULL));

		// Done working
		goto err;
	}

	// Free the memory
#if OPENSSL_VERSION_NUMBER < 0x1010000fL
	EVP_MD_CTX_cleanup(ctx);
#else
	EVP_MD_CTX_reset(ctx);
#endif
	EVP_MD_CTX_free(ctx);

	// All Done
	return PKI_OK;

err:
	// Free Memory
	if (ctx) {
#if OPENSSL_VERSION_NUMBER < 0x1010000fL
		EVP_MD_CTX_cleanup(ctx);
#else
		EVP_MD_CTX_reset(ctx);
#endif
		EVP_MD_CTX_free(ctx);
	}

	// Returns the error
	return PKI_ERR;
}

/* ----------------------- General Obj Management ------------------------ */

/*! \brief Gets a stack of X509 objects from the URL in the HSM */

PKI_X509_STACK *HSM_X509_STACK_get_url ( PKI_DATATYPE type, URL *url, 	
						PKI_DATA_FORMAT format, PKI_CRED *cred, HSM *hsm ) {

	PKI_STACK *ret = NULL;

	if( !url ) return ( NULL );

	if( url->proto != URI_PROTO_ID ) return NULL;

	if( !hsm ) hsm = (HSM * ) HSM_get_default();

	if( hsm  && hsm->callbacks && hsm->callbacks->x509_sk_get_url ) { 
		ret = hsm->callbacks->x509_sk_get_url( type, url, format, cred, hsm );
	};

        return ( ret );
}

/*! \brief Stores a stack of PKI_X509 objects in the specified URL/HSM */

int HSM_X509_STACK_put_url ( PKI_X509_STACK *sk, URL *url, 
						PKI_CRED *cred, HSM *hsm ) {

	int ret = PKI_OK;

	if( !url || !sk ) return PKI_ERR;

	if ( url->proto != URI_PROTO_ID ) return PKI_ERR;

	if( !hsm ) hsm = (HSM *) HSM_get_default();

	if( hsm  && hsm->callbacks && hsm->callbacks->x509_sk_add_url ) { 
		ret = hsm->callbacks->x509_sk_add_url( sk, url, cred, hsm );
	};

        return ( ret );
}

/*! \brief Stores the contents of a stack of MEM to the specified URL/HSM */

int HSM_MEM_STACK_put_url ( PKI_MEM_STACK *sk, URL *url, PKI_DATATYPE type,
						PKI_CRED *cred, HSM *hsm ) {
	int i = 0;
	int ret = PKI_OK;

	PKI_MEM *mem = NULL;
	PKI_X509 *x_obj = NULL;
	PKI_X509_STACK *obj_sk = NULL;

	if(( obj_sk = PKI_STACK_new_type( type )) == NULL ) {
		return PKI_ERR;
	}

	for ( i = 0; i < PKI_STACK_MEM_elements ( sk ); i++ ) {
		PKI_X509_STACK *mem_obj_sk = NULL;

		/* Gets the PKI_MEM container from the stack */
		if((mem = PKI_STACK_MEM_get_num ( sk, i )) == NULL ) {
			continue;
		}

		/* Gets the objects (multiple, possibly) from each PKI_MEM */
		if((mem_obj_sk = PKI_X509_STACK_get_mem ( mem, type, 
						PKI_DATA_FORMAT_UNKNOWN, cred, hsm )) == NULL ) {
			continue;
		}

		/* Builds the stack of PKI_X509 objects */
		while ((x_obj = PKI_STACK_X509_pop ( mem_obj_sk )) != NULL ) {
			/* Push the Object on the Stack */
			PKI_STACK_X509_push ( obj_sk, x_obj );
		}
	}

	/* Now Put the stack of objects in the HSM */
	ret = HSM_X509_STACK_put_url ( sk, url, cred, hsm );

	/* Clean the stack of Objects we created */
	while ( (x_obj = PKI_STACK_X509_pop ( sk )) != NULL ) {
		PKI_X509_free ( x_obj );
	}
	PKI_STACK_X509_free ( sk );

	/* Return value */
	return ret;
}

/*! \brief Deletes a Stack of Objects that are stored in a HSM */

int HSM_X509_STACK_del ( PKI_X509_STACK *sk ) {

	int ret = PKI_ERR;
	int i = 0;

	// HSM *hsm = NULL;
	// HSM *def_hsm = NULL;

	PKI_X509 *obj = NULL;

	if ( !sk ) return ( PKI_ERR );

	for ( i = 0; i < PKI_STACK_X509_elements ( sk ); i++ ) {
		obj = PKI_STACK_X509_get_num ( sk, i );

		if (!obj || !obj->value ) continue;

		if ( obj->ref ) {
			ret = HSM_X509_del_url ( obj->type, obj->ref, 
							obj->cred, obj->hsm );

			if ( ret == PKI_ERR ) return PKI_ERR;
		}
	}

	return PKI_OK;
}

/*! \brief Deletes the contents of the specified URL in the HSM */

int HSM_X509_del_url ( PKI_DATATYPE type, URL *url, PKI_CRED *cred, HSM *hsm ) {

	int ret = PKI_OK;

	if( !url ) return ( PKI_ERR );

	if( !hsm ) hsm = (HSM *) HSM_get_default();

	if( hsm  && hsm->callbacks && hsm->callbacks->x509_del_url ) { 
		ret = hsm->callbacks->x509_del_url( type, url, cred, hsm );
	};

        return ( ret );
}

/*! \brief Returns the callbacks for the specific HSM */

const PKI_X509_CALLBACKS * HSM_X509_get_cb ( PKI_DATATYPE type, HSM *hsm ) {

	if ( !hsm || !hsm->callbacks ) return HSM_OPENSSL_X509_get_cb (type);

	return hsm->callbacks->x509_get_cb ( type );
}

