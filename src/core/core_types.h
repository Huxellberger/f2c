
#ifndef CORE_TYPES_H
#define CORE_TYPES_H

#include <stdint.h>
#include <string.h>

#include <sanitizer/asan_interface.h> 

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef int8_t S8;
typedef int16_t S16;
typedef int32_t S32;
typedef int64_t S64;

typedef int8_t B8;
typedef int16_t B16;
typedef int32_t B32;
typedef int64_t B64;

typedef float F32;
typedef long F64; 

#define true 1
#define false 0

#define defer(begin, end) for(int _i_ = ((begin), 0); !_i_; _i_+=1, (end))

#define KB(n) ((U64)(n) << 10)
#define MB(n) ((U64)(n) << 20)
#define GB(n) ((U64)(n) << 30)
#define TB(n) ((U64)(n) << 40)

#define Million(d) (1000000 * (d))
#define Thousand(d) (1000 * (d))

#define zero_struct {0}

#define read_only __attribute__((section(".rodata"))) 

#define stringify(x) #x
#define join(x, y) x##y

#define c_memcpy(dst, src, size) memmove((dst), (src), (size))
#define c_memset(dst, byte, size) memset((dst), (byte), (size))

#define c_memzero(dst, size) memset((dst), 0, (size))

// Address Sanitizing: Use this to "poison memory" (e.g a write will crash gracefully)
#if __has_feature(address_sanitizer) || defined(__SANITIZE_ADDRESS__)
#define asan_poison_mem(addr, size) __asan_poison_memory_region((addr), (size))
#define asan_unpoison_mem(addr, size) __asan_unpoison_memory_region((addr), (size))
#else 
#define asan_poison_mem(addr, size) 
#define asan_unpoison_mem(addr, size)
#endif 

#define Trap() __builtin_debugtrap()

// JH: Only in debug please
#define Assert(x) do{if(!(x)){Trap();}}while(0) 

#define AlignPow2(x, b) (((x) + (b) - 1)&(~((b) - 1)))

#define llist_push(element, lList) ((element)->next = (lList)) 

#endif // CORE_TYPES_H
