#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "string_utils.h"
#include "config.h"

// String manipulation functions
void string_to_upper(char *str) {
    DEBUG_PRINT("Converting string to uppercase: %s", str);
    if (str == NULL) return;
    
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

void string_to_lower(char *str) {
    DEBUG_PRINT("Converting string to lowercase: %s", str);
    if (str == NULL) return;
    
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

void string_reverse(char *str) {
    DEBUG_PRINT("Reversing string: %s", str);
    if (str == NULL) return;
    
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

size_t string_length(const char *str) {
    if (str == NULL) return 0;
    
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    DEBUG_PRINT("String length: %zu", len);
    return len;
}

char* string_duplicate(const char *str) {
    DEBUG_PRINT("Duplicating string: %s", str);
    if (str == NULL) return NULL;
    
    size_t len = strlen(str);
    char *duplicate = malloc(len + 1);
    if (duplicate == NULL) {
        DEBUG_PRINT("Memory allocation failed for string duplication");
        return NULL;
    }
    
    strcpy(duplicate, str);
    return duplicate;
}

char* string_trim(const char *str) {
    DEBUG_PRINT("Trimming string: '%s'", str);
    if (str == NULL) return NULL;
    
    // Find start of non-whitespace
    while (isspace(*str)) {
        str++;
    }
    
    if (*str == '\0') {
        // String is all whitespace
        char *result = malloc(1);
        if (result) result[0] = '\0';
        return result;
    }
    
    // Find end of non-whitespace
    const char *end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) {
        end--;
    }
    
    // Allocate and copy trimmed string
    size_t len = end - str + 1;
    char *result = malloc(len + 1);
    if (result == NULL) {
        DEBUG_PRINT("Memory allocation failed for string trimming");
        return NULL;
    }
    
    strncpy(result, str, len);
    result[len] = '\0';
    return result;
}

// String analysis functions
int count_words(const char *str) {
    DEBUG_PRINT("Counting words in: %s", str);
    if (str == NULL) return 0;
    
    int count = 0;
    int in_word = 0;
    
    while (*str) {
        if (isspace(*str)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
        str++;
    }
    
    DEBUG_PRINT("Word count: %d", count);
    return count;
}

int count_characters(const char *str, char ch) {
    DEBUG_PRINT("Counting character '%c' in: %s", ch, str);
    if (str == NULL) return 0;
    
    int count = 0;
    while (*str) {
        if (*str == ch) {
            count++;
        }
        str++;
    }
    
    DEBUG_PRINT("Character count: %d", count);
    return count;
}

int string_contains(const char *str, const char *substr) {
    DEBUG_PRINT("Checking if '%s' contains '%s'", str, substr);
    if (str == NULL || substr == NULL) return 0;
    
    return strstr(str, substr) != NULL;
}

int string_starts_with(const char *str, const char *prefix) {
    DEBUG_PRINT("Checking if '%s' starts with '%s'", str, prefix);
    if (str == NULL || prefix == NULL) return 0;
    
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

int string_ends_with(const char *str, const char *suffix) {
    DEBUG_PRINT("Checking if '%s' ends with '%s'", str, suffix);
    if (str == NULL || suffix == NULL) return 0;
    
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);
    
    if (suffix_len > str_len) return 0;
    
    return strcmp(str + str_len - suffix_len, suffix) == 0;
}

// String operations
void string_concat(const char *str1, const char *str2, char *result, size_t result_size) {
    DEBUG_PRINT("Concatenating '%s' and '%s'", str1, str2);
    if (str1 == NULL || str2 == NULL || result == NULL) return;
    
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    
    if (len1 + len2 + 1 > result_size) {
        DEBUG_PRINT("Result buffer too small for concatenation");
        return;
    }
    
    strcpy(result, str1);
    strcat(result, str2);
}

int string_compare_ignore_case(const char *str1, const char *str2) {
    DEBUG_PRINT("Comparing '%s' and '%s' (ignore case)", str1, str2);
    if (str1 == NULL && str2 == NULL) return 0;
    if (str1 == NULL) return -1;
    if (str2 == NULL) return 1;
    
    while (*str1 && *str2) {
        char c1 = tolower(*str1);
        char c2 = tolower(*str2);
        
        if (c1 != c2) {
            return c1 - c2;
        }
        
        str1++;
        str2++;
    }
    
    return tolower(*str1) - tolower(*str2);
}

char* string_replace(const char *str, const char *old_substr, const char *new_substr) {
    DEBUG_PRINT("Replacing '%s' with '%s' in '%s'", old_substr, new_substr, str);
    if (str == NULL || old_substr == NULL || new_substr == NULL) return NULL;
    
    size_t old_len = strlen(old_substr);
    size_t new_len = strlen(new_substr);
    size_t str_len = strlen(str);
    
    // Count occurrences
    int count = 0;
    const char *temp = str;
    while ((temp = strstr(temp, old_substr)) != NULL) {
        count++;
        temp += old_len;
    }
    
    if (count == 0) {
        return string_duplicate(str);
    }
    
    // Calculate new string length
    size_t new_str_len = str_len + count * (new_len - old_len);
    char *result = malloc(new_str_len + 1);
    if (result == NULL) {
        DEBUG_PRINT("Memory allocation failed for string replacement");
        return NULL;
    }
    
    // Perform replacement
    char *dest = result;
    const char *src = str;
    
    while ((temp = strstr(src, old_substr)) != NULL) {
        // Copy part before match
        size_t prefix_len = temp - src;
        strncpy(dest, src, prefix_len);
        dest += prefix_len;
        
        // Copy replacement
        strcpy(dest, new_substr);
        dest += new_len;
        
        // Move source pointer
        src = temp + old_len;
    }
    
    // Copy remaining part
    strcpy(dest, src);
    
    return result;
}

void string_split(const char *str, char delimiter, char results[][100], int *count) {
    DEBUG_PRINT("Splitting string '%s' by delimiter '%c'", str, delimiter);
    if (str == NULL || results == NULL || count == NULL) return;
    
    *count = 0;
    const char *start = str;
    const char *end = str;
    
    while (*end) {
        if (*end == delimiter || *(end + 1) == '\0') {
            size_t len = end - start;
            if (*(end + 1) == '\0' && *end != delimiter) {
                len++;  // Include last character if not delimiter
            }
            
            if (len > 0 && len < 100) {
                strncpy(results[*count], start, len);
                results[*count][len] = '\0';
                (*count)++;
            }
            
            start = end + 1;
        }
        end++;
    }
    
    DEBUG_PRINT("Split into %d parts", *count);
}

// String validation
int is_numeric(const char *str) {
    DEBUG_PRINT("Checking if '%s' is numeric", str);
    if (str == NULL || *str == '\0') return 0;
    
    // Skip leading whitespace
    while (isspace(*str)) str++;
    
    // Check for optional sign
    if (*str == '+' || *str == '-') str++;
    
    // Must have at least one digit
    if (!isdigit(*str)) return 0;
    
    // Check remaining characters
    while (*str) {
        if (!isdigit(*str) && *str != '.') {
            // Skip trailing whitespace
            while (isspace(*str)) str++;
            return *str == '\0';
        }
        str++;
    }
    
    return 1;
}

int is_alphabetic(const char *str) {
    DEBUG_PRINT("Checking if '%s' is alphabetic", str);
    if (str == NULL || *str == '\0') return 0;
    
    while (*str) {
        if (!isalpha(*str) && !isspace(*str)) {
            return 0;
        }
        str++;
    }
    
    return 1;
}

int is_alphanumeric(const char *str) {
    DEBUG_PRINT("Checking if '%s' is alphanumeric", str);
    if (str == NULL || *str == '\0') return 0;
    
    while (*str) {
        if (!isalnum(*str) && !isspace(*str)) {
            return 0;
        }
        str++;
    }
    
    return 1;
}

int is_email_valid(const char *email) {
    DEBUG_PRINT("Validating email: %s", email);
    if (email == NULL) return 0;
    
    // Simple email validation
    const char *at = strchr(email, '@');
    if (at == NULL) return 0;  // No @ symbol
    
    if (at == email) return 0;  // @ at beginning
    
    const char *dot = strrchr(at, '.');
    if (dot == NULL) return 0;  // No dot after @
    
    if (dot == at + 1) return 0;  // Dot immediately after @
    
    if (strlen(dot) < 3) return 0;  // Domain extension too short
    
    return 1;  // Basic validation passed
}