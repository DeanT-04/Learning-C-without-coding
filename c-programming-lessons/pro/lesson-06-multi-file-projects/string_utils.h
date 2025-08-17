#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stddef.h>

// String manipulation functions
void string_to_upper(char *str);
void string_to_lower(char *str);
void string_reverse(char *str);
size_t string_length(const char *str);
char* string_duplicate(const char *str);
char* string_trim(const char *str);

// String analysis functions
int count_words(const char *str);
int count_characters(const char *str, char ch);
int string_contains(const char *str, const char *substr);
int string_starts_with(const char *str, const char *prefix);
int string_ends_with(const char *str, const char *suffix);

// String operations
void string_concat(const char *str1, const char *str2, char *result, size_t result_size);
int string_compare_ignore_case(const char *str1, const char *str2);
char* string_replace(const char *str, const char *old_substr, const char *new_substr);
void string_split(const char *str, char delimiter, char results[][100], int *count);

// String validation
int is_numeric(const char *str);
int is_alphabetic(const char *str);
int is_alphanumeric(const char *str);
int is_email_valid(const char *email);

#endif // STRING_UTILS_H