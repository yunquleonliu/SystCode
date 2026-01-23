/**
 * Problem 33: Mark-Sweep Garbage Collector
 * Automatic memory management with tracing GC.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_OBJECTS 256
#define STACK_SIZE 256

typedef enum {
    OBJ_INT,
    OBJ_PAIR
} ObjectType;

typedef struct Object {
    ObjectType type;
    bool marked;
    struct Object* next;  // For allocation list
    
    union {
        int value;
        struct {
            struct Object* head;
            struct Object* tail;
        };
    };
} Object;

typedef struct {
    Object* first_object;
    int num_objects;
    int max_objects;
    
    Object* stack[STACK_SIZE];
    int stack_size;
} VM;

VM* vm_create() {
    VM* vm = calloc(1, sizeof(VM));
    vm->max_objects = 8;  // Start with small threshold
    return vm;
}

void vm_push(VM* vm, Object* obj) {
    if (vm->stack_size < STACK_SIZE) {
        vm->stack[vm->stack_size++] = obj;
    }
}

Object* vm_pop(VM* vm) {
    if (vm->stack_size > 0) {
        return vm->stack[--vm->stack_size];
    }
    return NULL;
}

void gc_mark(Object* obj) {
    if (obj == NULL || obj->marked) return;
    
    obj->marked = true;
    
    if (obj->type == OBJ_PAIR) {
        gc_mark(obj->head);
        gc_mark(obj->tail);
    }
}

void gc_mark_all(VM* vm) {
    for (int i = 0; i < vm->stack_size; i++) {
        gc_mark(vm->stack[i]);
    }
}

void gc_sweep(VM* vm) {
    Object** obj = &vm->first_object;
    while (*obj) {
        if (!(*obj)->marked) {
            Object* unreached = *obj;
            *obj = unreached->next;
            printf("  Collecting object at %p\n", (void*)unreached);
            free(unreached);
            vm->num_objects--;
        } else {
            (*obj)->marked = false;
            obj = &(*obj)->next;
        }
    }
}

void gc(VM* vm) {
    int before = vm->num_objects;
    printf("GC: %d objects before\n", before);
    
    gc_mark_all(vm);
    gc_sweep(vm);
    
    printf("GC: %d objects after (freed %d)\n", vm->num_objects, before - vm->num_objects);
    
    vm->max_objects = vm->num_objects * 2;
}

Object* vm_new_object(VM* vm, ObjectType type) {
    if (vm->num_objects >= vm->max_objects) {
        gc(vm);
    }
    
    Object* obj = calloc(1, sizeof(Object));
    obj->type = type;
    obj->marked = false;
    obj->next = vm->first_object;
    vm->first_object = obj;
    vm->num_objects++;
    
    return obj;
}

Object* vm_new_int(VM* vm, int value) {
    Object* obj = vm_new_object(vm, OBJ_INT);
    obj->value = value;
    return obj;
}

Object* vm_new_pair(VM* vm) {
    Object* obj = vm_new_object(vm, OBJ_PAIR);
    obj->head = NULL;
    obj->tail = NULL;
    return obj;
}

void vm_destroy(VM* vm) {
    vm->stack_size = 0;
    gc(vm);  // Free remaining
    free(vm);
}

int main() {
    printf("=== Mark-Sweep GC ===\n\n");
    
    VM* vm = vm_create();
    
    // Create some objects
    printf("Creating objects...\n");
    vm_push(vm, vm_new_int(vm, 1));
    vm_push(vm, vm_new_int(vm, 2));
    
    Object* pair = vm_new_pair(vm);
    pair->head = vm_new_int(vm, 3);
    pair->tail = vm_new_int(vm, 4);
    vm_push(vm, pair);
    
    printf("Stack size: %d, Total objects: %d\n\n", vm->stack_size, vm->num_objects);
    
    // Pop some, making them unreachable
    printf("Popping objects (making them unreachable)...\n");
    vm_pop(vm);  // Pop pair
    vm_pop(vm);  // Pop int
    
    printf("\nTriggering GC...\n");
    gc(vm);
    
    vm_destroy(vm);
    return 0;
}