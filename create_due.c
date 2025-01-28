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

// Function to print the HTML header
void print_html_header() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Create Due Payment</title><style>"
           "body { font-family: Arial, sans-serif; background-color: #f2f2f2; margin: 0; padding: 0; display: flex; justify-content: center; align-items: center; height: 100vh; }"
           ".container { background-color: white; padding: 20px; border-radius: 8px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); max-width: 600px; width: 100%%; }"
           "h1 { text-align: center; color: #333; }"
           "</style></head><body><div class=\"container\">");
}

// Function to print the HTML footer
void print_html_footer() {
    printf("</div></body></html>");
}

// Function to save due payments data to a file
void save_due_payment(const char *customer_name, const char *due_amount) {
    FILE *file = fopen("C:/Apache24/htdocs/dues.txt", "a");
    if (file == NULL) {
        perror("Error opening dues file");
        printf("<p>Error saving due payment</p>");
        return;
    }
    fprintf(file, "Customer: %s, Due Amount: %s\n", customer_name, due_amount);
    fclose(file);
}

// Function to handle form submission
void handle_form_submission() {
    // Read the POST data
    int content_length = atoi(getenv("CONTENT_LENGTH"));
    char data[content_length + 1];
    fgets(data, content_length + 1, stdin);

    // Decode the URL-encoded data
    char customer_name[100] = {0};
    char due_amount[100] = {0};
    char decoded_data[200];
    url_decode(data, decoded_data);

    // Parse the data
    int parsed_items = sscanf(decoded_data, "customer_name=%[^&]&due_amount=%s", customer_name, due_amount);

    // Print the response and save the due payment
    if (parsed_items == 2) {
        printf("<h1>Due Payment Created</h1>");
        printf("<p>Customer Name: %s</p>", customer_name);
        printf("<p>Due Amount: %s</p>", due_amount);
        save_due_payment(customer_name, due_amount);
    } else {
        printf("<h1>Error parsing input data</h1>");
    }
}

int main() {
    // Print HTML header
    print_html_header();

    // Handle form submission
    handle_form_submission();

    // Print HTML footer
    print_html_footer();
    return 0;
}
