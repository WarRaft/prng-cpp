```
//----- (00000001402ECF90) ----------------------------------------------------
void __fastcall NTempest::CRndSeed::SetSeed(NTempest::CRndSeed *this, unsigned int seed)
{
this->rndacc = seed;
this->rndvls = ((seed + 17 * (seed / 0x2F)) << 26) | ((seed % 0x35) << 18) | (4 * (seed % 0x3D)) | ((seed % 0x3B) << 10);
}

//----- (00000001402ED010) ----------------------------------------------------
void __fastcall NTempest::CRndSeed::SetSeed(NTempest::CRndSeed *this, char *password)
{
unsigned __int64 v3; // r8
unsigned int v4; // ecx
unsigned int v5; // r9d
__int64 v6; // rax

v3 = -1i64;
do
++v3;
while ( password[v3] );
v4 = (unsigned __int8)*password;
v5 = 1;
if ( v3 > 1 )
{
v6 = 1i64;
do
{
++v5;
v4 = (v4 ^ (31277 * v4)) + (unsigned __int8)password[v6];
v6 = v5;
}
while ( v5 < v3 );
}
this->rndacc = v4;
this->rndvls = ((v4 + 17 * (v4 / 0x2F)) << 26) | ((v4 % 0x35) << 18) | (4 * (v4 % 0x3D)) | ((v4 % 0x3B) << 10);
}

//----- (00000001402A1640) ----------------------------------------------------
__int64 __fastcall NTempest::CRandom::uint32_(NTempest::CRndSeed *seed)
{
unsigned int rndvls; // edx
int v2; // ebx
int v3; // r11d
int v4; // r10d
signed int v5; // ebx
int v6; // r11d
int v7; // r10d
int v8; // r8d
int v9; // r8d
unsigned int v10; // edx
__int64 result; // rax

rndvls = seed->rndvls;
v2 = 184;
v3 = 200;
v4 = 212;
if ( HIBYTE(rndvls) >= 4u )
v2 = -4;
v5 = HIBYTE(rndvls) + v2;
if ( (rndvls & 0xFF0000) >= 0xC0000 )
v3 = -12;
v6 = BYTE2(rndvls) + v3;
if ( BYTE1(rndvls) >= 0x18u )
v4 = -24;
v7 = BYTE1(rndvls) + v4;
v8 = 216;
if ( (unsigned __int8)rndvls >= 0x1Cu )
v8 = -28;
v9 = (unsigned __int8)rndvls + v8;
v10 = seed->rndacc
+ (*(const unsigned int *)((char *)NTempest::gnoise32_ + v9) ^ __ROL4__(
*(const unsigned int *)((char *)NTempest::gnoise32_
+ v7),
3) ^ __ROL4__(
*(const unsigned int *)((char *)NTempest::gnoise32_ + v6),
2) ^ __ROL4__(
*(const unsigned int *)((char *)NTempest::gnoise32_ + v5),
1));
seed->rndvls = v9 | ((v7 | ((v6 | (v5 << 8)) << 8)) << 8);
result = v10;
seed->rndacc = v10;
return result;
}

//----- (0000000140B2D450) ----------------------------------------------------
void __fastcall RandomReset(unsigned int seed)
{
__int64 v2; // rdi
__int64 v3; // rbp
__int64 v4; // rsi
int v5; // r11d
int v6; // r10d
int v7; // ebx
signed int v8; // ebx
int v9; // r11d
int v10; // r10d
int v11; // r8d
int v12; // r8d
int v13; // edx
NTempest::CRndSeed base; // [rsp+58h] [rbp+10h] BYREF

v2 = *(_QWORD *)(PropGet(PROP_APPLICATION)[4] + 264i64);
if ( v2 )
{
NTempest::CRndSeed::SetSeed(&base, seed);
v3 = 45i64;
v4 = 9640i64;
do
{
v5 = 200;
v6 = 212;
v7 = 184;
if ( HIBYTE(base.rndvls) >= 4u )
v7 = -4;
v8 = HIBYTE(base.rndvls) + v7;
if ( BYTE2(base.rndvls) >= 0xCu )
v5 = -12;
v9 = BYTE2(base.rndvls) + v5;
if ( BYTE1(base.rndvls) >= 0x18u )
v6 = -24;
v10 = BYTE1(base.rndvls) + v6;
v11 = 216;
if ( LOBYTE(base.rndvls) >= 0x1Cu )
v11 = -28;
v12 = LOBYTE(base.rndvls) + v11;
v13 = __ROL4__(*(const unsigned int *)((char *)NTempest::gnoise32_ + v8), 1);
base.rndvls = v12 | ((v10 | ((v9 | (v8 << 8)) << 8)) << 8);
base.rndacc += *(const unsigned int *)((char *)NTempest::gnoise32_ + v12) ^ __ROL4__(
*(const unsigned int *)((char *)NTempest::gnoise32_ + v10),
3) ^ __ROL4__(
*(const unsigned int *)((char *)NTempest::gnoise32_ + v9),
2) ^ v13;
NTempest::CRndSeed::SetSeed((NTempest::CRndSeed *)(v4 + v2), base.rndacc);
v4 += 8i64;
--v3;
}
while ( v3 );
}
else
{
SErrSetLastError(0x57u);
}
}

//----- (000000014068E4C0) ----------------------------------------------------
void __fastcall SetRandomSeed(unsigned int seed)
{
NIpse::CThreadData *v1; // rbx
unsigned int v2; // eax

v1 = NIpse::CThreadData::s_;
NTempest::CRndSeed::SetSeed(&NIpse::CThreadData::s_->rnd_seed, seed);
v2 = NTempest::CRandom::uint32_(&v1->rnd_seed);
RandomReset(v2);
}
```
