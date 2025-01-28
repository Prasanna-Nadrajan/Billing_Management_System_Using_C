#include <stdio.h>
#include <stdlib.h>

// Function to print the HTML header with internal styles
void print_html_header() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Payment List</title><link rel=\"stylesheet\" type=\"text/css\" href=\"/styles.css\"></head><body><div class=\"container\">");
}

// Function to print the HTML footer
void print_html_footer() {
    printf("</div></body></html>");
}

// Function to generate the payment data table
void generate_payment_table() {
    FILE *file = fopen("C:/Apache24/htdocs/payments.txt", "r");
    if (!file) {
        perror("Error opening file");
        printf("<p>Error loading payment data</p>");
        return;
    }

    printf("<h1>Payment List</h1>");
    printf("<table><thead><tr><th>Customer Name</th><th>Amount</th></tr></thead><tbody>");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char customer_name[100];
        char amount[100];
        sscanf(line, "Customer: %[^,], Amount: %[^\n]", customer_name, amount);
        printf("<tr><td>%s</td><td>%s</td></tr>", customer_name, amount);
    }

    printf("</tbody></table>");
    fclose(file);
}

int main() {
    print_html_header();
    generate_payment_table();
    print_html_footer();
    return 0;
}
