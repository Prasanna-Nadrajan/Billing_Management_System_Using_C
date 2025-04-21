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
    printf("<html><head><link rel=\"stylesheet\" type=\"text/css\" href=\"/styles.css\"></head><body><div class=\"container\">");
}

// Function to print the HTML footer
void print_html_footer() {
    printf("</div></body></html>");
}

// Function to save payment data to a file
void save_to_file(const char *customer_name, const char *amount) {
    FILE *file = fopen("C:/Apache24/htdocs/payments.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        printf("<h1>Unable to open file</h1>");
        return;
    }
    fprintf(file, "Customer: %s, Amount: %s\n", customer_name, amount);
    fclose(file);
    // Function to save bill data to a file

    FILE *file1 = fopen("C:/Apache24/htdocs/bills.txt", "a");
    if (file1 == NULL) {
        perror("Error opening file");
        printf("<h1>Unable to open file</h1>");
        return;
    }
    fprintf(file1, "Customer: %s, Amount: %s\n", customer_name, amount);
    fclose(file1);

}

// Function to handle form submission
void handle_form_submission() {
    // Read the POST data
    int content_length = atoi(getenv("CONTENT_LENGTH"));
    char data[content_length + 1];
    fgets(data, content_length + 1, stdin);

    // Decode the URL-encoded data
    char customer_name[100] = {0};
    char amount[100] = {0};
    char decoded_data[200];
    url_decode(data, decoded_data);

    // Parse the data
    int parsed_items = sscanf(decoded_data, "customer_name=%[^&]&amount=%s", customer_name, amount);

    // Print the response
    if (parsed_items == 2) {
        printf("<h1>Payment Processed</h1>");
        printf("<p>Customer Name: %s</p>", customer_name);
        printf("<p>Amount: %s</p>", amount);
        save_to_file(customer_name, amount);
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
