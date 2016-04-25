

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include <ctype.h>

#ifndef PROXY_PARSE
#define PROXY_PARSE

#define DEBUG 0


struct ParsedRequest {
     char *method; 
     char *protocol; 
     char *host; 
     char *port; 
     char *path;
     char *version;
     char *buf;
     size_t buflen;
     struct ParsedHeader *headers;
     size_t headersused;
     size_t headerslen;
};


struct ParsedHeader {
     char * key;
     size_t keylen;
     char * value;
     size_t valuelen;
};


/* Create an empty parsing object to be used exactly once for parsing a single
 * request buffer */
struct ParsedRequest* ParsedRequest_create();

/* Parse the request buffer in buf given that buf is of length buflen */
int ParsedRequest_parse(struct ParsedRequest * parse, const char *buf,
			int buflen);

/* Destroy the parsing object. */
void ParsedRequest_destroy(struct ParsedRequest *pr);

int ParsedRequest_unparse(struct ParsedRequest *pr, char *buf, 
			  size_t buflen);


int ParsedRequest_unparse_headers(struct ParsedRequest *pr, char *buf, 
				  size_t buflen);

/* Total length including request line, headers and the trailing \r\n*/
size_t ParsedRequest_totalLen(struct ParsedRequest *pr);

/* Length including headers, if any, and the trailing \r\n but excluding the
 * request line. 
 */
size_t ParsedHeader_headersLen(struct ParsedRequest *pr);

/* Set, get, and remove null-terminated header keys and values */
int ParsedHeader_set(struct ParsedRequest *pr, const char * key, 
		      const char * value);
struct ParsedHeader* ParsedHeader_get(struct ParsedRequest *pr, 
				      const char * key);
int ParsedHeader_remove (struct ParsedRequest *pr, const char * key);

/* debug() prints out debugging info if DEBUG is set to 1 */
void debug(const char * format, ...);



#endif

