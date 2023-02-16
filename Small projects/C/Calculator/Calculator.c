#include <stdio.h>

int main() {
    char operator;
    double num1, num2, result;

    printf("Gebe einen Operator an (+, -, *, /): ");
    scanf("%c", &operator);

    printf("Gebe zwei werte ein (Nummer1 Nummer2): ");
    scanf("%lf %lf", &num1, &num2);

    switch (operator) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                printf("Error: Cannot divide by zero\n");
                return 1;
            }
            result = num1 / num2;
            break;
        default:
            printf("Error: Invalid operator\n");
            return 1;
    }

    printf("%.2lf %c %.2lf = %.2lf\n", num1, operator, num2, result);

    return 0;
}
