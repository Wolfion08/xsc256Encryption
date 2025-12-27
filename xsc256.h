#pragma once

#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <errno.h>


typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;
typedef unsigned _BitInt(128) int128;
typedef unsigned _BitInt(256) int256;

#define packed __attribute__((packed))
#define alloc(x)    malloc((x))

#define $1 (int8 *)
#define $2 (int16)
#define $4 (int32)
#define $8 (int64)
#define $16 (int128)
#define $32 (int256)
#define $i (int)
#define $c (char *)
#define $v (void *)

struct s_int192
{
    int256 x : 192;
};
typedef struct s_int192 int192;

// linked list
struct s_roundkey;
typedef struct s_roundkey roundkey;
struct s_roundkey
{
    int8 id : 4;
    int128 subkey;
    int64 round_constant_rc;
    roundkey *next;
} packed;

struct s_state
{
    int8 w[16];
    roundkey *subkeys;
};

typedef struct s_state state;

struct s_semiwords
{
    int8 x : 4;
    int8 y : 4;
    int8 z : 4;
} packed;

typedef struct s_semiwords semiwords;

#define show(x) _Generic((x), \
    int192: showint192,       \
    int128: showint128      \
    roundkey*:showroundkey   \
)($1 #x, (x))

void show_int_128(int8 *, int128);
void show_int_192(int8 *, int192);
void *showroundkey(int8 *, roundkey *);


int128 make_subkey(int8, int128, int64);
roundkey *make_roundkey(int8, int128, int64);
roundkey *gen_subkey(int128);
int192 x_box(int128); // expansion box
int192 s_boxes(int192);
semiwords s_box(semiwords); //
int128 c_box(int192);       // compression box
int128 f(int128);
state *sxcinit(int256);
int main(void);
