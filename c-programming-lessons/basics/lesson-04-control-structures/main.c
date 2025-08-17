#include <stdio.h>

int main() {
    printf("=== Control Structures in C ===\n\n");
    
    // 1. Basic if statement
    printf("1. Basic if statement:\n");
    int age = 18;
    if (age >= 18) {
        printf("   You are an adult (age: %d)\n", age);
    }
    printf("\n");
    
    // 2. if-else statement
    printf("2. if-else statement:\n");
    int temperature = 25;
    if (temperature > 30) {
        printf("   It's hot today! (%d°C)\n", temperature);
    } else {
        printf("   It's not too hot today (%d°C)\n", temperature);
    }
    printf("\n");
    
    // 3. if-else if-else chain
    printf("3. if-else if-else chain:\n");
    int score = 85;
    if (score >= 90) {
        printf("   Grade: A (score: %d)\n", score);
    } else if (score >= 80) {
        printf("   Grade: B (score: %d)\n", score);
    } else if (score >= 70) {
        printf("   Grade: C (score: %d)\n", score);
    } else if (score >= 60) {
        printf("   Grade: D (score: %d)\n", score);
    } else {
        printf("   Grade: F (score: %d)\n", score);
    }
    printf("\n");
    
    // 4. Nested if statements
    printf("4. Nested if statements:\n");
    int user_age = 25;
    int has_license = 1; // 1 for true, 0 for false
    
    if (user_age >= 18) {
        printf("   You are old enough to drive\n");
        if (has_license) {
            printf("   You can drive legally!\n");
        } else {
            printf("   But you need a license first\n");
        }
    } else {
        printf("   You are too young to drive (age: %d)\n", user_age);
    }
    printf("\n");
    
    // 5. Logical operators in conditions
    printf("5. Logical operators in conditions:\n");
    int hour = 14;
    int is_weekend = 0;
    
    if (hour >= 9 && hour <= 17 && !is_weekend) {
        printf("   Office hours: Open\n");
    } else {
        printf("   Office hours: Closed\n");
    }
    printf("\n");
    
    // 6. Basic switch statement
    printf("6. Basic switch statement:\n");
    int day = 3;
    switch (day) {
        case 1:
            printf("   Monday\n");
            break;
        case 2:
            printf("   Tuesday\n");
            break;
        case 3:
            printf("   Wednesday\n");
            break;
        case 4:
            printf("   Thursday\n");
            break;
        case 5:
            printf("   Friday\n");
            break;
        case 6:
            printf("   Saturday\n");
            break;
        case 7:
            printf("   Sunday\n");
            break;
        default:
            printf("   Invalid day number: %d\n", day);
            break;
    }
    printf("\n");
    
    // 7. Switch with character
    printf("7. Switch with character:\n");
    char grade = 'B';
    switch (grade) {
        case 'A':
        case 'a':
            printf("   Excellent work!\n");
            break;
        case 'B':
        case 'b':
            printf("   Good job!\n");
            break;
        case 'C':
        case 'c':
            printf("   Average performance\n");
            break;
        case 'D':
        case 'd':
            printf("   Below average\n");
            break;
        case 'F':
        case 'f':
            printf("   Failed\n");
            break;
        default:
            printf("   Invalid grade: %c\n", grade);
            break;
    }
    printf("\n");
    
    // 8. Switch without break (fall-through)
    printf("8. Switch fall-through example:\n");
    int month = 12;
    printf("   Month %d is in ", month);
    switch (month) {
        case 12:
        case 1:
        case 2:
            printf("Winter\n");
            break;
        case 3:
        case 4:
        case 5:
            printf("Spring\n");
            break;
        case 6:
        case 7:
        case 8:
            printf("Summer\n");
            break;
        case 9:
        case 10:
        case 11:
            printf("Fall\n");
            break;
        default:
            printf("an invalid month\n");
            break;
    }
    printf("\n");
    
    // 9. Ternary operator (conditional operator)
    printf("9. Ternary operator:\n");
    int number = 42;
    printf("   %d is %s\n", number, (number % 2 == 0) ? "even" : "odd");
    
    int max_value = (10 > 5) ? 10 : 5;
    printf("   Maximum of 10 and 5 is: %d\n", max_value);
    printf("\n");
    
    // 10. Complex condition example
    printf("10. Complex condition example:\n");
    int student_age = 20;
    float gpa = 3.5;
    int credits = 120;
    
    if ((student_age >= 18) && (gpa >= 3.0) && (credits >= 120)) {
        printf("   Student is eligible for graduation\n");
    } else {
        printf("   Student needs to meet more requirements:\n");
        if (student_age < 18) {
            printf("   - Must be at least 18 years old\n");
        }
        if (gpa < 3.0) {
            printf("   - Must have GPA of at least 3.0\n");
        }
        if (credits < 120) {
            printf("   - Must have at least 120 credits\n");
        }
    }
    
    return 0;
}