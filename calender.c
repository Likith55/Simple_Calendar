#include <stdio.h>
#include <stdlib.h>

struct Date {
    int dd, mm, yy;
};

// Function to check for leap year
int isLeapYear(int year) {
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}

// Get number of days in a month
int getDaysInMonth(int mm, int yy) {
    switch (mm) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return isLeapYear(yy) ? 29 : 28;
        default: return 0;
    }
}

// Return day of the week using Zeller’s Congruence (adjusted)
int calculateDayOfWeek(int dd, int mm, int yy) {
    if (mm < 3) {
        mm += 12;
        yy -= 1;
    }
    int k = yy % 100;
    int j = yy / 100;
    int h = (dd + 13*(mm + 1)/5 + k + k/4 + j/4 + 5*j) % 7;
    return (h + 6) % 7;  // Adjust: 0 = Sunday, ..., 6 = Saturday
}

// Return day name string
char* getDayName(int day) {
    char* names[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return names[day];
}

// Print monthly calendar
void printCalendar(int mm, int yy) {
    int days = getDaysInMonth(mm, yy);
    int startDay = calculateDayOfWeek(1, mm, yy);

    printf("\n  Calendar - %02d/%d\n", mm, yy);
    printf("  Sun Mon Tue Wed Thu Fri Sat\n");

    // Print initial spaces
    for (int i = 0; i < startDay; i++) {
        printf("    ");
    }

    // Print the days
    for (int d = 1; d <= days; d++) {
        printf("%4d", d);
        if ((startDay + d) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

// Main menu
int main() {
    struct Date date;
    int choice;

    while (1) {
        printf("\n=== Simple Calendar ===\n");
        printf("1. Find Day of a Date\n");
        printf("2. Print Calendar of a Month\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter date (DD MM YYYY): ");
                scanf("%d %d %d", &date.dd, &date.mm, &date.yy);
                if (date.mm < 1 || date.mm > 12 || date.dd < 1 || date.dd > getDaysInMonth(date.mm, date.yy)) {
                    printf("Invalid date.\n");
                } else {
                    int day = calculateDayOfWeek(date.dd, date.mm, date.yy);
                    printf("The day is: %s\n", getDayName(day));
                }
                break;
            case 2:
                printf("Enter month and year (MM YYYY): ");
                scanf("%d %d", &date.mm, &date.yy);
                if (date.mm < 1 || date.mm > 12 || date.yy < 1) {
                    printf("Invalid month or year.\n");
                } else {
                    printCalendar(date.mm, date.yy);
                }
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
