#include <stdio.h>
#include <stdlib.h>

// Function to print the HTML header with internal styles
void print_html_header() {
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Customer List</title><link rel=\"stylesheet\" type=\"text/css\" href=\"/styles.css\"></head><body><div class=\"container\">");
}

// Function to print the HTML footer
void print_html_footer() {
    printf("</div></body></html>");
}

// Function to generate the customer data table
void generate_customer_table() {
    FILE *file = fopen("C:/Apache24/htdocs/customers.txt", "r");
    if (!file) {
        perror("Error opening file");
        printf("<p>Error loading customer data</p>");
        return;
    }

    printf("<h1>Customer List</h1>");
    printf("<table><thead><tr><th>Customer Name</th><th>Customer Email</th></tr></thead><tbody>");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char customer_name[100];
        char customer_email[100];
        sscanf(line, "Customer: %[^,], Email: %[^\n]", customer_name, customer_email);
        printf("<tr><td>%s</td><td>%s</td></tr>", customer_name, customer_email);
    }

    printf("</tbody></table>");
    fclose(file);
}

int main() {
    print_html_header();
    generate_customer_table();
    print_html_footer();
    return 0;
}

/*<style>"
           "body { font-family: Arial, sans-serif; background-color: #f2f2f2; margin: 0; padding: 0; display: flex; justify-content: center; align-items: center; height: 100vh; }"
           ".container { background-color: white; padding: 20px; border-radius: 8px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); max-width: 600px; width: 100%%; }"
           "h1 { text-align: center; color: #333; }"
           "table { width: 100%%; border-collapse: collapse; margin-top: 20px; text-align:center}"
           "table, th, td { border: 1px solid #ddd; }"
           "th, td { padding: 12px; text-align: ; }"
           "th { background-color: #f4f4f4; color: #333; }"
           "tr:nth-child(even) { background-color: #f9f9f9; }"
           "</style>*/