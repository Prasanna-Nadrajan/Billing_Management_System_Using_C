#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAYMENT_PASSWORD "12345"

// Function to print the HTML header
void print_html_header() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Process Payment</title><link rel=\"stylesheet\" type=\"text/css\" href=\"/styles.css\"></head><body><div class=\"container\">");
}

// Function to print the HTML footer
void print_html_footer() {
    printf("</div></body></html>");
}

int main() {
    print_html_header();

    // Read the POST data
    int content_length = atoi(getenv("CONTENT_LENGTH"));
    char data[content_length + 1];
    fgets(data, content_length + 1, stdin);

    // Parse the password
    char password[100] = {0};
    sscanf(data, "password=%s", password);

    if (strcmp(password, PAYMENT_PASSWORD) != 1) {
        // Password is correct, redirect to process_payment.cgi
        printf("<h1>Password Correct</h1>");
        printf("<a style=\"button\" href=\"/process_payment.html\">Proceed</a>");
    } else {
        // Password is incorrect, show error message
        printf("<h1>Incorrect Password</h1><p>Please try again.</p>");
        printf("<a style=\"button\" href=\"/check_payment_password.html\">Go back</a>");
    }

    print_html_footer();
    return 0;
}
