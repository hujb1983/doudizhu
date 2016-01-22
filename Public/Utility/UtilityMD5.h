#ifndef _UtilityMD5_H_
#define _UtilityMD5_H_

#include <string>
#include <fstream>
#include <cstring>

/* Type define */
typedef unsigned char byte;
typedef unsigned int bit32;

using std::string;
using std::ifstream;

/* MD5 declaration. */
class UtilityMD5 {
public:
	UtilityMD5();
	UtilityMD5(const void *input, size_t length);
	UtilityMD5(const string &str);
	UtilityMD5(ifstream &in);
	void update(const void *input, size_t length);
	void update(const string &str);
	void update(ifstream &in);
	const byte* digest();
	string toString();
	void reset();
private:
	void update(const byte *input, size_t length);
	void final();
	void transform(const byte block[64]);
	void encode(const bit32 *input, byte *output, size_t length);
	void decode(const byte *input, bit32 *output, size_t length);
	string bytesToHexString(const byte *input, size_t length);

	/* class uncopyable */
	UtilityMD5(const UtilityMD5&);
	UtilityMD5& operator=(const UtilityMD5&);
private:
	bit32 _state[4];	/* state (ABCD) */
	bit32 _count[2];	/* number of bits, modulo 2^64 (low-order word first) */
	byte _buffer[64];	/* input buffer */
	byte _digest[16];	/* message digest */
	bool _finished;		/* calculate finished ? */

	static const byte PADDING[64];	/* padding for calculate */
	static const char HEX[16];
	static const size_t BUFFER_SIZE = 1024;
};

#endif // _YOND_MD5_H_INCLUDED_