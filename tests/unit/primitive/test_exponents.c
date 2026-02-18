#include <stdio.h>
#include "primitive/exponents.h"

int main() {
    printf("=== Testing exponents ===\n");
    
    // Test positive exponent
    double result1 = exponents(2.0f, 3.0f);
    printf("2^3 = %.2f (expected: 8.00)\n", result1);
    
    // Test zero exponent
    double result2 = exponents(5.0f, 0.0f);
    printf("5^0 = %.2f (expected: 1.00)\n", result2);
    
    // Test negative exponent
    double result3 = exponents(2.0f, -2.0f);
    printf("2^-2 = %.4f (expected: 0.2500)\n", result3);
    
    // Test fractional exponent
    double result4 = exponents(4.0f, 0.5f);
    printf("4^0.5 = %.2f (expected: 2.00)\n", result4);
    
    // Test base zero
    double result5 = exponents(0.0f, 5.0f);
    printf("0^5 = %.2f (expected: 0.00)\n", result5);
    
    return 0;
}
