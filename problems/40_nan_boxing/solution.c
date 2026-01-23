/**
 * Problem 40: NaN Boxing
 * Encoding multiple types in 64-bit IEEE 754 doubles.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

// NaN boxing layout for 64-bit:
// Doubles: Normal IEEE 754 double
// NaN: Exponent all 1s, mantissa non-zero
// We use quiet NaN (bit 51 set) and encode type in bits 48-50

#define QNAN_BITS    0x7FFC000000000000ULL  // Quiet NaN with type bits clear
#define SIGN_BIT     0x8000000000000000ULL
#define TAG_MASK     0x0007000000000000ULL  // Bits 48-50 for type
#define PAYLOAD_MASK 0x0000FFFFFFFFFFFFULL  // 48 bits for payload

typedef enum {
    TAG_NAN     = 0,  // Real NaN
    TAG_NIL     = 1,
    TAG_FALSE   = 2,
    TAG_TRUE    = 3,
    TAG_INT     = 4,  // 48-bit signed integer
    TAG_POINTER = 5,  // 48-bit pointer (x86-64 canonical)
    TAG_SYMBOL  = 6,  // Interned symbol ID
} ValueTag;

typedef union {
    double as_double;
    uint64_t as_bits;
} Value;

// Type checking
static inline bool is_double(Value v) {
    return (v.as_bits & QNAN_BITS) != QNAN_BITS;
}

static inline bool is_nil(Value v) {
    return v.as_bits == (QNAN_BITS | (TAG_NIL << 48));
}

static inline bool is_bool(Value v) {
    uint64_t tag = (v.as_bits & TAG_MASK) >> 48;
    return (v.as_bits & QNAN_BITS) == QNAN_BITS && (tag == TAG_FALSE || tag == TAG_TRUE);
}

static inline bool is_int(Value v) {
    return (v.as_bits & (QNAN_BITS | TAG_MASK)) == (QNAN_BITS | ((uint64_t)TAG_INT << 48));
}

static inline bool is_pointer(Value v) {
    return (v.as_bits & (QNAN_BITS | TAG_MASK)) == (QNAN_BITS | ((uint64_t)TAG_POINTER << 48));
}

// Constructors
static inline Value make_double(double d) {
    Value v;
    v.as_double = d;
    return v;
}

static inline Value make_nil() {
    Value v;
    v.as_bits = QNAN_BITS | ((uint64_t)TAG_NIL << 48);
    return v;
}

static inline Value make_bool(bool b) {
    Value v;
    v.as_bits = QNAN_BITS | ((uint64_t)(b ? TAG_TRUE : TAG_FALSE) << 48);
    return v;
}

static inline Value make_int(int64_t i) {
    Value v;
    v.as_bits = QNAN_BITS | ((uint64_t)TAG_INT << 48) | (i & PAYLOAD_MASK);
    return v;
}

static inline Value make_pointer(void* p) {
    Value v;
    v.as_bits = QNAN_BITS | ((uint64_t)TAG_POINTER << 48) | ((uint64_t)p & PAYLOAD_MASK);
    return v;
}

// Extractors
static inline double as_double(Value v) {
    return v.as_double;
}

static inline bool as_bool(Value v) {
    return ((v.as_bits & TAG_MASK) >> 48) == TAG_TRUE;
}

static inline int64_t as_int(Value v) {
    int64_t i = v.as_bits & PAYLOAD_MASK;
    // Sign extend from 48 bits
    if (i & 0x800000000000ULL) {
        i |= 0xFFFF000000000000ULL;
    }
    return i;
}

static inline void* as_pointer(Value v) {
    return (void*)(v.as_bits & PAYLOAD_MASK);
}

void print_value(Value v) {
    if (is_double(v)) {
        printf("Double: %g\n", as_double(v));
    } else if (is_nil(v)) {
        printf("Nil\n");
    } else if (is_bool(v)) {
        printf("Bool: %s\n", as_bool(v) ? "true" : "false");
    } else if (is_int(v)) {
        printf("Int: %lld\n", (long long)as_int(v));
    } else if (is_pointer(v)) {
        printf("Pointer: %p\n", as_pointer(v));
    } else {
        printf("Unknown type\n");
    }
}

int main() {
    printf("=== NaN Boxing ===\n\n");
    
    printf("sizeof(Value) = %zu bytes\n\n", sizeof(Value));
    
    // Create various values
    Value vals[] = {
        make_double(3.14159),
        make_double(-273.15),
        make_nil(),
        make_bool(true),
        make_bool(false),
        make_int(42),
        make_int(-1000),
        make_pointer((void*)0x12345678),
    };
    
    for (int i = 0; i < 8; i++) {
        printf("[%d] bits=0x%016llx  ", i, (unsigned long long)vals[i].as_bits);
        print_value(vals[i]);
    }
    
    // Arithmetic with doubles
    printf("\nArithmetic test:\n");
    Value a = make_double(10.5);
    Value b = make_double(2.0);
    if (is_double(a) && is_double(b)) {
        Value c = make_double(as_double(a) * as_double(b));
        printf("10.5 * 2.0 = %g\n", as_double(c));
    }
    
    return 0;
}