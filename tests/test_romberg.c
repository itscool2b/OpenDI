#include <stdio.h>
#include <math.h>
#include "calculus/romberg.h"

// Test function: f(x) = x^2, integral from 0 to 1 = 1/3
double test_func1(double x) {
    return x * x;
}

// Test function: f(x) = sin(x), integral from 0 to pi = 2
double test_func2(double x) {
    return sin(x);
}

// Test function: f(x) = 1, integral from 0 to 1 = 1 (constant)
double test_func3(double x) {
    return 1.0;
}

// Test function: f(x) = x, integral from 0 to 1 = 0.5 (linear)
double test_func4(double x) {
    return x;
}

// Test function: f(x) = e^x, integral from 0 to 1 = e - 1
double test_func5(double x) {
    return exp(x);
}

// Test function: f(x) = x^3, integral from 0 to 2 = 4
double test_func6(double x) {
    return x * x * x;
}

// Test function: f(x) = 1/x, integral from 1 to e = 1
double test_func7(double x) {
    return 1.0 / x;
}

// Test function: f(x) = cos(x), integral from 0 to pi/2 = 1
double test_func8(double x) {
    return cos(x);
}

int main() {
    printf("=== Testing romberg_integrate ===\n\n");
    
    double eps = 1e-10;
    int k_max = 20;
    double result, expected, error;
    int passed = 0, failed = 0;
    
    // Test 1: f(x) = x^2 from 0 to 1, expected = 1/3
    printf("Test 1: f(x) = x^2, [0, 1]\n");
    result = romberg_integrate(test_func1, 0.0, 1.0, eps, k_max);
    expected = 1.0 / 3.0;
    error = fabs(result - expected);
    printf("  Result:   %.12f\n", result);
    printf("  Expected: %.12f\n", expected);
    printf("  Error:    %.2e %s\n\n", error, error < 1e-8 ? "PASS" : "FAIL");
    if (error < 1e-8) passed++; else failed++;
    
    // Test 2: f(x) = sin(x) from 0 to pi, expected = 2
    printf("Test 2: f(x) = sin(x), [0, pi]\n");
    result = romberg_integrate(test_func2, 0.0, M_PI, eps, k_max);
    expected = 2.0;
    error = fabs(result - expected);
    printf("  Result:   %.12f\n", result);
    printf("  Expected: %.12f\n", expected);
    printf("  Error:    %.2e %s\n\n", error, error < 1e-8 ? "PASS" : "FAIL");
    if (error < 1e-8) passed++; else failed++;
    
    // Test 3: f(x) = 1 (constant) from 0 to 1, expected = 1
    printf("Test 3: f(x) = 1, [0, 1] (constant)\n");
    result = romberg_integrate(test_func3, 0.0, 1.0, eps, k_max);
    expected = 1.0;
    error = fabs(result - expected);
    printf("  Result:   %.12f\n", result);
    printf("  Expected: %.12f\n", expected);
    printf("  Error:    %.2e %s\n\n", error, error < 1e-8 ? "PASS" : "FAIL");
    if (error < 1e-8) passed++; else failed++;
    
    // Test 4: f(x) = x (linear) from 0 to 1, expected = 0.5
    printf("Test 4: f(x) = x, [0, 1] (linear)\n");
    result = romberg_integrate(test_func4, 0.0, 1.0, eps, k_max);
    expected = 0.5;
    error = fabs(result - expected);
    printf("  Result:   %.12f\n", result);
    printf("  Expected: %.12f\n", expected);
    printf("  Error:    %.2e %s\n\n", error, error < 1e-8 ? "PASS" : "FAIL");
    if (error < 1e-8) passed++; else failed++;
    
    // Test 5: f(x) = e^x from 0 to 1, expected = e - 1
    printf("Test 5: f(x) = e^x, [0, 1]\n");
    result = romberg_integrate(test_func5, 0.0, 1.0, eps, k_max);
    expected = exp(1.0) - 1.0;
    error = fabs(result - expected);
    printf("  Result:   %.12f\n", result);
    printf("  Expected: %.12f\n", expected);
    printf("  Error:    %.2e %s\n\n", error, error < 1e-8 ? "PASS" : "FAIL");
    if (error < 1e-8) passed++; else failed++;
    
    // Test 6: f(x) = x^3 from 0 to 2, expected = 4
    printf("Test 6: f(x) = x^3, [0, 2]\n");
    result = romberg_integrate(test_func6, 0.0, 2.0, eps, k_max);
    expected = 4.0;
    error = fabs(result - expected);
    printf("  Result:   %.12f\n", result);
    printf("  Expected: %.12f\n", expected);
    printf("  Error:    %.2e %s\n\n", error, error < 1e-8 ? "PASS" : "FAIL");
    if (error < 1e-8) passed++; else failed++;
    
    // Test 7: f(x) = 1/x from 1 to e, expected = 1
    printf("Test 7: f(x) = 1/x, [1, e]\n");
    result = romberg_integrate(test_func7, 1.0, exp(1.0), eps, k_max);
    expected = 1.0;
    error = fabs(result - expected);
    printf("  Result:   %.12f\n", result);
    printf("  Expected: %.12f\n", expected);
    printf("  Error:    %.2e %s\n\n", error, error < 1e-8 ? "PASS" : "FAIL");
    if (error < 1e-8) passed++; else failed++;
    
    // Test 8: f(x) = cos(x) from 0 to pi/2, expected = 1
    printf("Test 8: f(x) = cos(x), [0, pi/2]\n");
    result = romberg_integrate(test_func8, 0.0, M_PI / 2.0, eps, k_max);
    expected = 1.0;
    error = fabs(result - expected);
    printf("  Result:   %.12f\n", result);
    printf("  Expected: %.12f\n", expected);
    printf("  Error:    %.2e %s\n\n", error, error < 1e-8 ? "PASS" : "FAIL");
    if (error < 1e-8) passed++; else failed++;
    
    // Test 9: Edge case - zero interval [a, a]
    printf("Test 9: Edge case - zero interval [1, 1]\n");
    result = romberg_integrate(test_func1, 1.0, 1.0, eps, k_max);
    expected = 0.0;
    error = fabs(result - expected);
    printf("  Result:   %.12f\n", result);
    printf("  Expected: %.12f\n", expected);
    printf("  Error:    %.2e %s\n\n", error, error < 1e-8 ? "PASS" : "FAIL");
    if (error < 1e-8) passed++; else failed++;
    
    // Test 10: Edge case - negative interval [b, a] where b > a
    printf("Test 10: Edge case - reversed interval [1, 0]\n");
    result = romberg_integrate(test_func1, 1.0, 0.0, eps, k_max);
    expected = -1.0 / 3.0;  // Should be negative of integral from 0 to 1
    error = fabs(result - expected);
    printf("  Result:   %.12f\n", result);
    printf("  Expected: %.12f\n", expected);
    printf("  Error:    %.2e %s\n\n", error, error < 1e-8 ? "PASS" : "FAIL");
    if (error < 1e-8) passed++; else failed++;
    
    // Test 11: Large interval
    printf("Test 11: Large interval - f(x) = x, [0, 1000]\n");
    result = romberg_integrate(test_func4, 0.0, 1000.0, eps, k_max);
    expected = 500000.0;  // 0.5 * 1000^2
    error = fabs(result - expected);
    printf("  Result:   %.12f\n", result);
    printf("  Expected: %.12f\n", expected);
    printf("  Error:    %.2e %s\n\n", error, error < 1e-6 ? "PASS" : "FAIL");
    if (error < 1e-6) passed++; else failed++;
    
    // Test 12: Small interval
    printf("Test 12: Small interval - f(x) = x^2, [0, 0.001]\n");
    result = romberg_integrate(test_func1, 0.0, 0.001, eps, k_max);
    expected = 1e-9 / 3.0;  // (0.001)^3 / 3
    error = fabs(result - expected);
    printf("  Result:   %.12e\n", result);
    printf("  Expected: %.12e\n", expected);
    printf("  Error:    %.2e %s\n\n", error, error < 1e-12 ? "PASS" : "FAIL");
    if (error < 1e-12) passed++; else failed++;
    
    // Test 13: Relaxed epsilon (less precision)
    printf("Test 13: Relaxed epsilon - f(x) = x^2, [0, 1], eps=1e-3\n");
    result = romberg_integrate(test_func1, 0.0, 1.0, 1e-3, k_max);
    expected = 1.0 / 3.0;
    error = fabs(result - expected);
    printf("  Result:   %.12f\n", result);
    printf("  Expected: %.12f\n", expected);
    printf("  Error:    %.2e %s\n\n", error, error < 1e-3 ? "PASS" : "FAIL");
    if (error < 1e-3) passed++; else failed++;
    
    // Test 14: Very strict epsilon
    printf("Test 14: Strict epsilon - f(x) = x^2, [0, 1], eps=1e-14\n");
    result = romberg_integrate(test_func1, 0.0, 1.0, 1e-14, k_max);
    expected = 1.0 / 3.0;
    error = fabs(result - expected);
    printf("  Result:   %.12f\n", result);
    printf("  Expected: %.12f\n", expected);
    printf("  Error:    %.2e %s\n\n", error, error < 1e-10 ? "PASS" : "FAIL");
    if (error < 1e-10) passed++; else failed++;
    
    printf("=== Summary ===\n");
    printf("Passed: %d\n", passed);
    printf("Failed: %d\n", failed);
    
    return failed > 0 ? 1 : 0;
}
