#include "StdAfx.h"
#include ".\md5class.h"

CMd5Class::CMd5Class(void)
{
}

CMd5Class::~CMd5Class(void)
{
}

const char * CMd5Class::Hex2ASC(const BYTE *Hex, int Len)
{
	static char ASC[4096 * 2];
	int i;

	for (i = 0; i < Len; i++)
	{
		ASC[i * 2] = "0123456789ABCDEF"[Hex[i] >> 4];
		ASC[i * 2 + 1] = "0123456789ABCDEF"[Hex[i] & 0x0F];
	}
	ASC[i * 2] = '\0';
	return ASC;
}


const char * CMd5Class::md5(const char * str)
{
	MD5_CTX ctx;
	const unsigned char * buf = reinterpret_cast<const unsigned char *>(str);
	int len = strlen(str);
	HINSTANCE hDLL;
	if ( (hDLL = LoadLibrary(_T("advapi32.dll"))) > 0 )
	{

		MD5Init = (PMD5Init)GetProcAddress(hDLL,"MD5Init");
		MD5Update = (PMD5Update)GetProcAddress(hDLL,"MD5Update");
		MD5Final = (PMD5Final)GetProcAddress(hDLL,"MD5Final");

		MD5Init(&ctx);
		MD5Update(&ctx, buf, len);
		MD5Final(&ctx);
	}
	return Hex2ASC(ctx.digest, 16);
}

