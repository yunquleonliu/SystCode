#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    const char* method;
    size_t method_len;
    const char* path;
    size_t path_len;
    int minor_version;
} HttpRequest;

// Zero-copy parser
// Returns 1 on success, 0 on incomplete/error
int parse_request(const char* data, size_t len, HttpRequest* req) {
    // 1. Check for double CRLF (End of headers)
    const char* end_of_headers = strstr(data, "\r\n\r\n");
    if (!end_of_headers) return 0; // Not a full request yet

    const char* p = data;
    
    // 2. Method
    const char* space1 = strchr(p, ' ');
    if (!space1) return 0;
    
    req->method = p;
    req->method_len = space1 - p;
    
    // 3. Path
    p = space1 + 1;
    const char* space2 = strchr(p, ' ');
    if (!space2) return 0;
    
    req->path = p;
    req->path_len = space2 - p;
    
    // 4. Version (HTTP/1.x)
    p = space2 + 1;
    if (strncmp(p, "HTTP/1.", 7) == 0) {
        req->minor_version = p[7] - '0';
    } else {
        req->minor_version = -1;
    }
    
    return 1;
}

void solution() {}

int main() {
    const char* raw = 
        "GET /api/users/123 HTTP/1.1\r\n"
        "Host: example.com\r\n"
        "User-Agent: my-client\r\n"
        "\r\n"
        "BODY IGNORED";
        
    HttpRequest req;
    printf("Parsing:\n%s\n---\n", raw);
    
    if (parse_request(raw, strlen(raw), &req)) {
        char method[16];
        char path[128];
        
        snprintf(method, sizeof(method), "%.*s", (int)req.method_len, req.method);
        snprintf(path, sizeof(path), "%.*s", (int)req.path_len, req.path);
        
        printf("Method: %s\n", method);
        printf("Path:   %s\n", path);
        printf("Ver:    1.%d\n", req.minor_version);
        
        if (strcmp(method, "GET") == 0 && strcmp(path, "/api/users/123") == 0) {
            printf("Test Passed\n");
            return 0;
        }
    }
    
    printf("Test Failed\n");
    return 0;
}
