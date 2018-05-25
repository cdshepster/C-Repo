#pragma once

// ------------------------------------------------------------------
//
// Adapted From: http://stackoverflow.com/questions/5905822/function-to-find-the-nth-digit-of-pi
// Other references:
//		http://bellard.org/pi/pi_n2/pi_n2.html
//		https://web.archive.org/web/20150627225748/http://en.literateprograms.org/Pi_with_the_BBP_formula_%28Python%29
//
// ------------------------------------------------------------------
/* #define HAS_LONG_LONG */

//#ifdef HAS_LONG_LONG
	#define mul_mod(a,b,m) (( (long long) (a) * (long long) (b) ) % (m))
//#else
//	#define mul_mod(a,b,m) std::fmod( (double) a * (double) b, m)
//#endif

unsigned int computePiDigit(int n);
unsigned long long piDigitHex(unsigned long long n);
