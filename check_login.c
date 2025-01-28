/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the path to the users file
#define USERS_FILE "C:/Apache24/htdocs/users.txt"

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
    printf("<html><head>"
        "<title>Login Check</title>"
        "<link rel=\"stylesheet\" type=\"text/css\" href=\"/styles.css\">"
        "</head><body><div class=\"container\">");
}

// Function to print the HTML footer
void print_html_footer() {
    printf("</div></body></html>");
}

// Function to check if the provided credentials are valid
int check_credentials(const char *username, const char *password) {
    FILE *file = fopen(USERS_FILE, "r");
    if (!file) {
        perror("Error opening users file");
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char stored_username[100];
        char stored_password[100];
        sscanf(line, "%[^:]:%s", stored_username, stored_password);
        if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int main() {
    // Print HTML header
    print_html_header();

    // Read the POST data
    int content_length = atoi(getenv("CONTENT_LENGTH"));
    char data[content_length + 1];
    fgets(data, content_length + 1, stdin);

    // Decode the URL-encoded data
    char decoded_data[256];
    url_decode(data, decoded_data);

    // Parse the username and password
    char username[100] = {0};
    char password[100] = {0};
    sscanf(decoded_data, "username=%[^&]&password=%s", username, password);

    // Check if the credentials are correct
    if (check_credentials(username, password)) {
        // Credentials are correct, redirect to home_page.html
        printf("<meta http-equiv=\"refresh\" content=\"0;url=/home_page.html\">");
    } else {
        // Credentials are incorrect, show error message
        printf("<h1>Incorrect Username or Password</h1><p>Please try again.</p>");
        printf("<a class=\"button\" href=\"/index.html\">Go back</a>");
    }

    // Print HTML footer
    print_html_footer();

    return 0;
}
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the path to the users file
#define USERS_FILE "C:/Apache24/htdocs/users.txt"

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
    printf("<html><head>"
        "<title>Login Check</title>"
        "<link rel=\"stylesheet\" type=\"text/css\" href=\"/styles.css\">"
        "</head><body><div class=\"container\">");
}

// Function to print the HTML footer
void print_html_footer() {
    printf("</div></body></html>");
}

// Function to check if the provided credentials are valid and return the user role
int check_credentials(const char *username, const char *password, char *role) {
    FILE *file = fopen(USERS_FILE, "r");
    if (!file) {
        perror("Error opening users file");
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char stored_username[100];
        char stored_password[100];
        char stored_role[10];
        sscanf(line, "%[^:]:%[^:]:%s", stored_username, stored_password, stored_role);
        if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) {
            strcpy(role, stored_role);
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int main() {
    // Print HTML header
    print_html_header();

    // Read the POST data
    int content_length = atoi(getenv("CONTENT_LENGTH"));
    char data[content_length + 1];
    fgets(data, content_length + 1, stdin);

    // Decode the URL-encoded data
    char decoded_data[256];
    url_decode(data, decoded_data);

    // Parse the username and password
    char username[100] = {0};
    char password[100] = {0};
    sscanf(decoded_data, "username=%[^&]&password=%s", username, password);

    // Check if the credentials are correct and get the user role
    char role[10] = {0};
    if (check_credentials(username, password, role)) {
        // Credentials are correct, redirect based on role
        if (strcmp(role, "admin") == 0) {
            printf("<meta http-equiv=\"refresh\" content=\"0;url=/admin.html\">");
        } else if (strcmp(role, "user") == 0) {
            printf("<meta http-equiv=\"refresh\" content=\"0;url=/user.html\">");
        } else {
            printf("<h1>Unknown Role</h1><p>The user role is not recognized.</p>");
            printf("<a class=\"button\" href=\"/index.html\">Go back</a>");
        }
    } else {
        // Credentials are incorrect, show error message
        printf("<h1>Incorrect Username or Password</h1><p>Please try again.</p>");
        printf("<a class=\"button\" href=\"/index.html\">Go back</a>");
    }

    // Print HTML footer
    print_html_footer();

    return 0;
}
