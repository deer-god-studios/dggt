#ifndef _DGGT_MATH_UTILS_H_

#include <cmath>
#include "types/dggt_types.h"

template <typename T>
static const T PI=T(3.141592653589793238);

template <typename T>
T max(const T& val0,const T& val1)
{
	return val0>val1?val0:val1;
}

template <typename T>
T min(const T& val0,const T& val1)
{
	return val0<val1?val0:val1;
}

template <typename T>
T sq(T val)
{
	return val*val;
}

template <typename T>
T pow(T val,uint32 p)
{
	if (p==0)
	{
		return T(1);
	}
	else
	{
		return val*pow(val,p-1);
	}
}

template <typename T>
T pow2(uint32 p)
{
	return T(1<<p);
}

inline real32 sqrt(real32 val)
{
	return std::sqrt(val);
}

inline real64 sqrt(real64 val)
{
	return std::sqrt(val);
}

inline real32 cosine(real32 val)
{
	return (real32)cos((real64)val);
}
inline real32 sine(real32 val)
{
	return (real32)sin((real64)val);
}
inline real64 cosine(real64 val)
{
	return cos(val);
}
template <typename T>
T cosine(T val)
{
	return T(cosine(real64(val))); 
}

inline real64 sine(real64 val)
{
	return sin(val);
}

template <typename T>
T sine(T val)
{
	return T(sine(real64(val))); 
}

enum intvl_ends
{
	OPN_INTVL=0,
	CLSD_INTVL=1,
	L_CLSD_INTVL=2,
	R_CLSD_INTVL=3,
	L_OPN_INTVL=R_CLSD_INTVL,
	R_OPN_INTVL=L_CLSD_INTVL,
};

template <typename T=real32>
inline bool32 intvl(T val,
		T leftP,T rightP,intvl_ends ends=CLSD_INTVL)
{
	bool32 result=0;
	switch(ends)
	{
		case OPN_INTVL:
			{
				result=val>leftP&&val<rightP;
			} break;
		case CLSD_INTVL:
			{
				result=val>=leftP&&val<=rightP;
			} break;
		case R_CLSD_INTVL:
			{
				result=val>leftP&&val<=rightP;
			} break;
		case L_CLSD_INTVL:
			{
				result=val>=leftP&&val<rightP;
			} break;
	}
	return result;
}

template <typename T=real32>
inline bool32 intvl_0n(T val,T n,intvl_ends ends=CLSD_INTVL)
{
	return intvl(val,T(0),n,ends);
}


template <typename T=real32>
inline bool32 intvl_01(T val,intvl_ends ends=CLSD_INTVL)
{
	return intvl_0n(val,T(1),ends);
}

template <typename T=real32>
inline bool32 intvl_centered(T val,
		T n,intvl_ends ends=CLSD_INTVL)
{
	return intvl(val,-n,n,ends);
}

template <typename T=real32>
inline bool32 intvl_unit_disk(T val,intvl_ends ends=CLSD_INTVL)
{
	return intvl_centered(val,T(1),ends);
}

#define _DGGT_MATH_UTILS_H_
#endif
