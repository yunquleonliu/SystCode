/**
 * Problem 36: Runtime Reflection in C
 * Type information at runtime.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

// Type IDs
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_STRUCT
} TypeKind;

typedef struct Field {
    const char* name;
    TypeKind type;
    size_t offset;
    size_t size;
} Field;

typedef struct TypeInfo {
    const char* name;
    TypeKind kind;
    size_t size;
    Field* fields;
    int num_fields;
} TypeInfo;

// Macro to get field offset
#define FIELD_OFFSET(type, field) offsetof(type, field)
#define FIELD_SIZE(type, field) sizeof(((type*)0)->field)

// Example struct to reflect
typedef struct {
    int id;
    float value;
    char name[32];
} Person;

// Build reflection info for Person
Field person_fields[] = {
    {"id",    TYPE_INT,    FIELD_OFFSET(Person, id),    FIELD_SIZE(Person, id)},
    {"value", TYPE_FLOAT,  FIELD_OFFSET(Person, value), FIELD_SIZE(Person, value)},
    {"name",  TYPE_STRING, FIELD_OFFSET(Person, name),  FIELD_SIZE(Person, name)},
};

TypeInfo person_type = {
    "Person",
    TYPE_STRUCT,
    sizeof(Person),
    person_fields,
    3
};

// Reflection API
void* get_field_ptr(void* obj, TypeInfo* type, const char* field_name) {
    for (int i = 0; i < type->num_fields; i++) {
        if (strcmp(type->fields[i].name, field_name) == 0) {
            return (char*)obj + type->fields[i].offset;
        }
    }
    return NULL;
}

void set_int_field(void* obj, TypeInfo* type, const char* name, int value) {
    int* ptr = get_field_ptr(obj, type, name);
    if (ptr) *ptr = value;
}

void set_float_field(void* obj, TypeInfo* type, const char* name, float value) {
    float* ptr = get_field_ptr(obj, type, name);
    if (ptr) *ptr = value;
}

void set_string_field(void* obj, TypeInfo* type, const char* name, const char* value) {
    char* ptr = get_field_ptr(obj, type, name);
    if (ptr) strncpy(ptr, value, 31);
}

int get_int_field(void* obj, TypeInfo* type, const char* name) {
    int* ptr = get_field_ptr(obj, type, name);
    return ptr ? *ptr : 0;
}

void print_object(void* obj, TypeInfo* type) {
    printf("%s {\n", type->name);
    for (int i = 0; i < type->num_fields; i++) {
        Field* f = &type->fields[i];
        void* ptr = (char*)obj + f->offset;
        
        printf("  %s: ", f->name);
        switch (f->type) {
            case TYPE_INT:    printf("%d", *(int*)ptr); break;
            case TYPE_FLOAT:  printf("%.2f", *(float*)ptr); break;
            case TYPE_STRING: printf("\"%s\"", (char*)ptr); break;
            default: printf("?");
        }
        printf("\n");
    }
    printf("}\n");
}

void* create_instance(TypeInfo* type) {
    return calloc(1, type->size);
}

int main() {
    printf("=== Runtime Reflection ===\n\n");
    
    // Create instance using reflection
    Person* p = create_instance(&person_type);
    
    // Set fields using reflection
    set_int_field(p, &person_type, "id", 42);
    set_float_field(p, &person_type, "value", 3.14f);
    set_string_field(p, &person_type, "name", "Alice");
    
    // Print using reflection
    printf("Object created via reflection:\n");
    print_object(p, &person_type);
    
    // Query type info
    printf("\nType Info:\n");
    printf("  Name: %s\n", person_type.name);
    printf("  Size: %zu bytes\n", person_type.size);
    printf("  Fields: %d\n", person_type.num_fields);
    
    free(p);
    return 0;
}