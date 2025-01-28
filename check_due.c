#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to print the HTML header with internal styles
void print_html_header() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Check Due Payments</title><style>"
           "body { font-family: Arial, sans-serif; background-color: #f2f2f2; margin: 0; padding: 0; display: flex; justify-content: center; align-items: center; height: 100vh; }"
           ".container { background-color: white; padding: 20px; border-radius: 8px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); max-width: 600px; width: 100%%; }"
           "h1 { text-align: center; color: #333; }"
           "table { width: 100%%; border-collapse: collapse; margin-top: 20px; }"
           "table, th, td { border: 1px solid #ddd; }"
           "th, td { padding: 12px; text-align: left; }"
           "th { background-color: #f4f4f4; color: #333; }"
           "tr:nth-child(even) { background-color: #f9f9f9; }"
           "</style></head><body><div class=\"container\">");
}

// Function to print the HTML footer
void print_html_footer() {
    printf("</div></body></html>");
}

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

// Function to check dues for a given customer name
void check_dues(const char *customer_name) {
    FILE *file = fopen("C:/Apache24/htdocs/dues.txt", "r");
    if (!file) {
        perror("Error opening dues file");
        printf("<p>Error loading due payments data</p>");
        return;
    }

    printf("<h1>Due Payments for %s</h1>", customer_name);
    printf("<table><thead><tr><th>Customer Name</th><th>Due Amount</th></tr></thead><tbody>");

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        char stored_customer_name[100];
        char due_amount[100];
        sscanf(line, "Customer: %[^,], Due Amount: %[^\n]", stored_customer_name, due_amount);

        // Check if the stored customer name matches the entered customer name
        if (strcmp(stored_customer_name, customer_name) == 0) {
            printf("<tr><td>%s</td><td>%s</td></tr>", stored_customer_name, due_amount);
            found = 1;
        }
    }

    if (!found) {
        printf("<tr><td colspan=\"2\">No due payments found for %s</td></tr>", customer_name);
    }

    printf("</tbody></table>");
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
    char decoded_data[200];
    url_decode(data, decoded_data);

    // Parse the data
    sscanf(decoded_data, "customer_name=%s", customer_name);

    // Check dues for the entered customer name
    check_dues(customer_name);
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
