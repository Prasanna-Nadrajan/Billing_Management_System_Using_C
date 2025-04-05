#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to decode URL-encoded strings
void url_decode(char *src, char *dest) {
    char *p = src;
    char code[3] = {0};
    while (*p) {
        if (*p == '%') {
            strncpy(code, ++p, 2);
            *dest++ = (char) strtol(code, NULL, 16);
            p += 2;
        } else if (*p == '+') {
            *dest++ = ' ';
            p++;
        } else {
            *dest++ = *p++;
        }
    }
    *dest = '\0';
}

void print_html_header() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><link rel=\"stylesheet\" type=\"text/css\" href=\"/styles.css\"></head><body><div class=\"container\">");
}

void print_html_footer() {
    printf("</div></body></html>");
}

void save_to_file(const char *customer_name, const char *customer_email) {
    FILE *file = fopen("C:/Apache24/htdocs/customers.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        printf("<h1>Unable to open file</h1>");
        return;
    }
    fprintf(file, "Customer: %s, Email: %s\n", customer_name, customer_email);
    fclose(file);
}

void handle_form_submission() {
    // For POST method, read from standard input
    int content_length = atoi(getenv("CONTENT_LENGTH"));
    char data[content_length + 1];
    fgets(data, content_length + 1, stdin);

    char customer_name[100] = {0};
    char customer_email[100] = {0};
    char decoded_data[200];
    url_decode(data, decoded_data);

    int parsed_items = sscanf(decoded_data, "customer_name=%[^&]&customer_email=%s", customer_name, customer_email);

    if (parsed_items == 2) {
        printf("<h1>Customer Added</h1>");
        printf("<p>Name: %s</p>", customer_name);
        printf("<p>Email: %s</p>", customer_email);
        save_to_file(customer_name, customer_email);
    } else {
        printf("<h1>Error parsing input data</h1>");
    }
}

int main() {
    print_html_header();
    handle_form_submission();
    print_html_footer();
    return 0;
}

