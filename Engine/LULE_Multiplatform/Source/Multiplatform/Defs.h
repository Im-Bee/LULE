#ifndef LULE_TYPEDEFS_H
#define LULE_TYPEDEFS_H

#if _WIN32 || _WIN64
	typedef bool  LBOOL;
	typedef CHAR  LCHAR;
	typedef WCHAR LWCHAR;
	
	typedef INT8  LINT8;
	typedef INT32 LINT16;
	typedef INT32 LINT32;
	typedef INT64 LINT64;
	
	typedef UINT8  LUINT8;
	typedef UINT32 LUINT16;
	typedef UINT32 LUINT32;
	typedef UINT64 LUINT64;

#elif __GNUC__
	typedef bool    LBOOL;
	typedef char    LCHAR;
	typedef wchar_t LWCHAR;
	
	typedef __int8_t   LINT8;
	typedef __int32_t  LINT16;
	typedef __int32_t  LINT32;
	typedef __int64_t  LINT64;
	
	typedef __uint8_t  LUINT8;
	typedef __uint32_t  LUINT32;
	typedef __uint32_t LUINT32;
	typedef __uint64_t LUINT64;
#else
#   error "Couldn't detect the system, _LUL_ types are not defined."
#endif

#define LQUARTER (0.25)
#define LHALF (0.5)

#define LMEM_KiB(x) ((LUINT64)(x * 1024))
#define LMEM_MiB(x) (LMEM_KiB(x * 1024))
#define LMEM_GiB(x) (LMEM_MiB(x * 1024))

#define LULE_PATH_MAX_SIZE ((LUINT8)(0xFF)) // 255
#define LULE_MESSAGE_MAX_SIZE ((LUINT32)(0x400)) // 1024

#endif // !LULE_TYPEDEFS_H
