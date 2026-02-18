#include <stdio.h>
#include <math.h>
#include "calculus/forwarddiff.h"

// Test function: f(x) = x^2, f'(x) = 2x
double test_func1(double x) {
    return x * x;
}

// Test function: f(x) = sin(x), f'(x) = cos(x)
double test_func2(double x) {
    return sin(x);
}

// Test function: f(x) = 3x + 2, f'(x) = 3
double test_func3(double x) {
    return 3 * x + 2;
}

int main() {
    printf("=== Testing forwarddiff ===\n");
    
    double h = 0.0001;
    
    // Test f(x) = x^2 at x = 3, expected f'(3) = 6
    double result1 = forwarddiff(test_func1, 3.0, h);
    printf("f(x)=x^2 at x=3: f'(3) ≈ %.4f (expected: ~6.00, error: %.4f)\n", 
           result1, fabs(result1 - 6.0));
    
    // Test f(x) = x^2 at x = 0, expected f'(0) = 0
    double result2 = forwarddiff(test_func1, 0.0, h);
    printf("f(x)=x^2 at x=0: f'(0) ≈ %.4f (expected: ~0.00, error: %.4f)\n", 
           result2, fabs(result2 - 0.0));
    
    // Test f(x) = sin(x) at x = 0, expected f'(0) = cos(0) = 1
    double result3 = forwarddiff(test_func2, 0.0, h);
    printf("f(x)=sin(x) at x=0: f'(0) ≈ %.4f (expected: ~1.00, error: %.4f)\n", 
           result3, fabs(result3 - 1.0));
    
    // Test f(x) = 3x + 2 at x = 5, expected f'(5) = 3
    double result4 = forwarddiff(test_func3, 5.0, h);
    printf("f(x)=3x+2 at x=5: f'(5) ≈ %.4f (expected: ~3.00, error: %.4f)\n", 
           result4, fabs(result4 - 3.0));
    
    // Test h = 0 edge case
    double result5 = forwarddiff(test_func1, 3.0, 0.0);
    printf("h=0 edge case: result = %.2f (expected: 0.00)\n", result5);
    
    return 0;
}
