```C++
__int64 __fastcall GetRandomInt(unsigned int lowBound, int highBound)
{
  unsigned int v5; // eax
  int v6; // edx

  if ( lowBound == highBound )
    return lowBound;
  v5 = NTempest::CRandom::uint32_(&NIpse::CThreadData::s_->rnd_seed);
  v6 = lowBound - highBound;
  if ( (int)lowBound <= highBound )
    v6 = highBound - lowBound;
  return (unsigned int)(lowBound + (((unsigned int)(v6 + 1) * (unsigned __int64)v5) >> 32));
}

__int64 __fastcall GetRandomReal(const unreal *lowBound, const unreal *highBound)
{
  const unreal *v5; // r8
  unreal *p_result; // rcx
  const unreal *v7; // rdx
  const unreal *v8; // rax
  unreal a; // [rsp+20h] [rbp-18h] BYREF
  unreal v10; // [rsp+24h] [rbp-14h] BYREF
  unreal v11; // [rsp+28h] [rbp-10h] BYREF
  unreal result; // [rsp+50h] [rbp+18h] BYREF
  unreal b; // [rsp+58h] [rbp+20h] BYREF

  result.bits = operator-(&result, lowBound, highBound)->bits & 0x7FFFFFFF;
  if ( *((float *)&s_description.m_syncDataHistorys.sdHistory[143].turnBlocks + 4) > result.fp )
    return lowBound->bits;
  v5 = highBound;
  p_result = &result;
  v7 = lowBound;
  if ( lowBound->fp > highBound->fp )
  {
    p_result = &b;
  }
  else
  {
    v5 = lowBound;
    v7 = highBound;
  }
  a.bits = operator-(p_result, v7, v5)->bits;
  result.bits = NTempest::CRandom::uint32_(&NIpse::CThreadData::s_->rnd_seed) & 0x7FFFFF | 0x3F800000;
  operator+(&b, &result, &u_n1);
  v8 = operator*(&v10, &a, &b);
  return operator+(&v11, lowBound, v8)->bits;
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
                                                                       *(const unsigned int *)((char *)NTempest::gnoise32_ + v7), 3) 
                                                                   ^ __ROL4__(
                                                                              *(const unsigned int *)((char *)NTempest::gnoise32_ + v6), 2)
                                                                   ^ __ROL4__(
                                                                   *(const unsigned int *)((char *)NTempest::gnoise32_ + v5), 1)
                                                                   );
  seed->rndvls = v9 | ((v7 | ((v6 | (v5 << 8)) << 8)) << 8);
  result = v10;
  seed->rndacc = v10;
  return result;
}

const unsigned int NTempest::gnoise32_[64] =
{
  2569475214u,
  147303165u,
  524216021u,
  3663051766u,
  1783275637u,
  4288134632u,
  2679938014u,
  1184991873u,
  1675823982u,
  1567390326u,
  3395933064u,
  632899523u,
  1067625347u,
  3128705446u,
  26586341u,
  3238645630u,
  1903190745u,
  33938317u,
  1424983844u,
  808965318u,
  2076908496u,
  3973637304u,
  3702378057u,
  3298076947u,
  229521807u,
  249385496u,
  2247490168u,
  1840239192u,
  995340964u,
  3192956241u,
  301215228u,
  4044789832u,
  1715330950u,
  791561310u,
  392890166u,
  3058444683u,
  3881798114u,
  3777079245u,
  3982870861u,
  597487358u,
  79134003u,
  1076533918u,
  4082831539u,
  2451339138u,
  1461603872u,
  2349232674u,
  4218629223u,
  3205153369u,
  217668729u,
  1746016808u,
  1108948084u,
  4169449649u,
  2635460664u,
  1866134112u,
  2448134324u,
  1630895901u,
  1443050074u,
  2469119395u,
  1128992640u,
  1021356279u,
  644141462u,
  1338787287u,
  3051991240u,
  3929134592u
}; // idb

```
