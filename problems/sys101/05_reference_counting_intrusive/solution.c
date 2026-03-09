/**
 * Problem 05: Intrusive Reference Counting
 * Objects embed the refcount - no separate allocation.
 * Uses atomic operations for thread safety.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdatomic.h>
#include <string.h>
#include <assert.h>

// Intrusive refcount base - embed this in your objects
typedef struct {
    atomic_int refcount;
    void (*destructor)(void*);
} RefCounted;

// Macro to get container from embedded RefCounted
#define container_of(ptr, type, member) \
    ((type*)((char*)(ptr) - offsetof(type, member)))

void ref_init(RefCounted* rc, void (*destructor)(void*)) {
    atomic_init(&rc->refcount, 1);
    rc->destructor = destructor;
}

void ref_acquire(RefCounted* rc) {
    if (!rc) return;
    atomic_fetch_add(&rc->refcount, 1);
}

void ref_release(RefCounted* rc) {
    if (!rc) return;
    if (atomic_fetch_sub(&rc->refcount, 1) == 1) {
        // Last reference, call destructor
        if (rc->destructor) {
            rc->destructor(rc);
        }
    }
}

int ref_count(RefCounted* rc) {
    return atomic_load(&rc->refcount);
}

// -----------------------------------------------------------------------------
// Example: Reference-counted String
// -----------------------------------------------------------------------------

typedef struct {
    RefCounted rc;  // Embedded refcount
    size_t length;
    char data[];    // Flexible array
} RcString;

static void rc_string_destroy(void* ptr) {
    RcString* s = container_of(ptr, RcString, rc);
    printf("  [Destructor called for \"%s\"]\n", s->data);
    free(s);
}

RcString* rc_string_create(const char* str) {
    size_t len = strlen(str);
    RcString* s = (RcString*)malloc(sizeof(RcString) + len + 1);
    if (!s) return NULL;
    
    ref_init(&s->rc, rc_string_destroy);
    s->length = len;
    memcpy(s->data, str, len + 1);
    return s;
}

RcString* rc_string_clone(RcString* s) {
    if (!s) return NULL;
    ref_acquire(&s->rc);
    return s;
}

void rc_string_release(RcString* s) {
    if (!s) return;
    ref_release(&s->rc);
}

// -----------------------------------------------------------------------------
// Example: Reference-counted Buffer
// -----------------------------------------------------------------------------

typedef struct {
    RefCounted rc;
    size_t size;
    void* data;
} RcBuffer;

static void rc_buffer_destroy(void* ptr) {
    RcBuffer* b = container_of(ptr, RcBuffer, rc);
    printf("  [Buffer destructor, size=%zu]\n", b->size);
    free(b->data);
    free(b);
}

RcBuffer* rc_buffer_create(size_t size) {
    RcBuffer* b = (RcBuffer*)malloc(sizeof(RcBuffer));
    if (!b) return NULL;
    
    b->data = malloc(size);
    if (!b->data) {
        free(b);
        return NULL;
    }
    
    ref_init(&b->rc, rc_buffer_destroy);
    b->size = size;
    return b;
}

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

void test_basic_refcount() {
    printf("Test: Basic reference counting... ");
    
    RcString* s = rc_string_create("Hello");
    assert(s != NULL);
    assert(ref_count(&s->rc) == 1);
    
    RcString* s2 = rc_string_clone(s);
    assert(s2 == s);  // Same pointer
    assert(ref_count(&s->rc) == 2);
    
    rc_string_release(s2);
    assert(ref_count(&s->rc) == 1);
    
    rc_string_release(s);  // Should trigger destructor
    
    printf("PASSED\n");
}

void test_multiple_refs() {
    printf("Test: Multiple references... ");
    
    RcBuffer* b = rc_buffer_create(1024);
    assert(b != NULL);
    
    // Simulate multiple owners
    ref_acquire(&b->rc);
    ref_acquire(&b->rc);
    assert(ref_count(&b->rc) == 3);
    
    ref_release(&b->rc);
    ref_release(&b->rc);
    assert(ref_count(&b->rc) == 1);
    
    ref_release(&b->rc);  // Final release
    
    printf("PASSED\n");
}

void test_container_of_macro() {
    printf("Test: container_of macro... ");
    
    RcString* s = rc_string_create("Test");
    RefCounted* rc = &s->rc;
    
    RcString* recovered = container_of(rc, RcString, rc);
    assert(recovered == s);
    assert(strcmp(recovered->data, "Test") == 0);
    
    rc_string_release(s);
    printf("PASSED\n");
}

int main() {
    printf("=== Intrusive Reference Counting Tests ===\n\n");
    test_basic_refcount();
    test_multiple_refs();
    test_container_of_macro();
    printf("\nAll tests passed!\n");
    return 0;
}
