#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
/* 
 * Check whether "cp" is a valid ascii representation
 * of an Internet address and convert to a binary address.
 * Returns 1 if the address is valid, 0 if not.
 * This replaces inet_addr, the return value from which
 * cannot distinguish between failure and a local broadcast address.
 */

#undef htonl
#undef ntohl

static inline unsigned short bswap_16(unsigned short x) {
  return (x>>8) | (x<<8);
}

static inline unsigned int bswap_32(unsigned int x) {
  return (bswap_16(x&0xffff)<<16) | (bswap_16(x>>16));
}

static inline unsigned long long bswap_64(unsigned long long x) {
  return (((unsigned long long)bswap_32(x&0xffffffffull))<<32) |
(bswap_32(x>>32));
}

uint32_t my_htonl (x) 
     uint32_t x;{
#if BYTE_ORDER == BIG_ENDIAN
    return x;
#elif BYTE_ORDER == LITTLE_ENDIAN
    return bswap_32 (x);
#else
# error "What kind of system is this?"
#endif
}

int my_inet_aton(const char *cp, struct in_addr *ap){
    int dots = 0;
    register u_long acc = 0, addr = 0;

    do {
	register char cc = *cp;

	switch (cc) {
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	    acc = acc * 10 + (cc - '0');
	    break;

	case '.':
	    if (++dots > 3) {
		return 0;
	    }
	    /* Fall through */

	case '\0':
	    if (acc > 255) {
		return 0;
	    }
	    addr = addr << 8 | acc;
	    acc = 0;
	    break;

	default:
	    return 0;
	}
    } while (*cp++) ;

    /* Normalize the address */
    if (dots < 3) {
        addr <<= 8 * (3 - dots) ;        // 比如你只写了为形式 192.2.2
    }

    printf("before invoking htonl : %lu\n",addr);
    /* Store it if requested */
    if (ap) {
	ap->s_addr = my_htonl(addr);
    }

    return 1;    
}

static __thread char buffer[18]; 

char * my_inet_ntoa (struct in_addr in){
  unsigned char *bytes = (unsigned char *) &in;
  snprintf (buffer, sizeof (buffer), "%d.%d.%d.%d",
            bytes[0], bytes[1], bytes[2], bytes[3]);
 
  unsigned int sum = bytes[0] * 256 * 256 * 256 + bytes[1] * 256 * 256  + bytes[2] * 256 + bytes[3];
  printf("sum based on bytes    : %u\n",sum);
  return buffer;
}

int main(){
    struct in_addr Intap;
    my_inet_aton("192.168.0.1", &Intap);
    printf("after invoking htonl  : %u\n",Intap.s_addr);
    
    my_inet_ntoa(Intap);
    printf("buff is %s\n",buffer);
}
