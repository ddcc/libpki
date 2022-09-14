/* PKI_X509_CRL object management */

#ifndef _LIBPKI_PKI_X509_CRL_H
#define _LIBPKI_PKI_X509_CRL_H

/* PKI_X509_CRL_ENTRY */
PKI_X509_CRL_ENTRY * PKI_X509_CRL_ENTRY_new(const PKI_X509_CERT *cert,
					    PKI_X509_CRL_REASON reason, 
					    const PKI_TIME *revDate, 
					    const PKI_X509_PROFILE *profile);

PKI_X509_CRL_ENTRY * PKI_X509_CRL_ENTRY_new_serial(
					   const char *serial, 
					   PKI_X509_CRL_REASON reason, 
					   const PKI_TIME *revDate, 
					   const PKI_X509_PROFILE *profile);

int PKI_X509_CRL_ENTRY_free ( PKI_X509_CRL_ENTRY *entry );

/* PKI CRL lookup functions */
const PKI_X509_CRL_ENTRY * PKI_X509_CRL_lookup(const PKI_X509_CRL *x, 
					       const PKI_INTEGER *s );

const PKI_X509_CRL_ENTRY * PKI_X509_CRL_lookup_serial(const PKI_X509_CRL *x,
						      const char *serial);

const PKI_X509_CRL_ENTRY * PKI_X509_CRL_lookup_cert(const PKI_X509_CRL *x, 
						    const PKI_X509_CERT *cert );

const PKI_X509_CRL_ENTRY * PKI_X509_CRL_lookup_long(const PKI_X509_CRL *x,
						    long long s );

/* PKI CRL Reason Codes */
int PKI_X509_CRL_REASON_CODE_num ( void );
int PKI_X509_CRL_REASON_CODE_get ( const char * st );
const char *PKI_X509_CRL_REASON_CODE_get_parsed ( int reason );
const char *PKI_X509_CRL_REASON_CODE_get_descr ( int reason );

/* PKI CRL */
PKI_X509_CRL *PKI_X509_CRL_new_null ( void );
void PKI_X509_CRL_free_void( void *x );

PKI_X509_CRL *PKI_X509_CRL_new (const PKI_X509_KEYPAIR *pkey,
				const PKI_X509_CERT *cert,
				const char * crlNum_s,
				unsigned long validity, 
				const PKI_X509_CRL_ENTRY_STACK *sk,
                        	const PKI_X509_PROFILE *profile,
				const PKI_CONFIG *oids,
				HSM *hsm);

int PKI_X509_CRL_free ( PKI_X509_CRL * x );
int PKI_X509_CRL_add_extension(PKI_X509_CRL *x, PKI_X509_EXTENSION *ext);

PKI_MEM * PKI_X509_CRL_tbs_asn1(PKI_X509_CRL *x);

const void * PKI_X509_CRL_get_data ( const PKI_X509_CRL *x,
		                     PKI_X509_DATA type );

char * PKI_X509_CRL_get_parsed(const PKI_X509_CRL *x,
			       PKI_X509_DATA type );

#endif
