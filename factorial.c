
 #include <stdio.h>

 /**
  * Recursive factorial function
  * 
  * @param n: The number to calculate factorial for
  * @return: n! (factorial of n)
  * 
  * Memory layout during execution:
  * - Each call creates a new stack frame
  * - Stack frame contains: return address, saved registers, local variables
  * - Stack grows downward (from high to low addresses)
  */
 int factorial(int n) {
     // Base case: factorial(0) = 1, factorial(1) = 1
     if (n <= 1) {
         return 1;
     }
     
     // Recursive case: n! = n * (n-1)!
     return n * factorial(n - 1);
 }
 
 
 int main() {
     printf("=== Recursive Factorial Calculator ===\n\n");
     
     // Test cases
     int test_values[] = {0, 1, 3, 5};
     int num_tests = sizeof(test_values) / sizeof(test_values[0]);
     
     for (int i = 0; i < num_tests; i++) {
         int n = test_values[i];
         int result = factorial(n);
         
         printf("factorial(%d) = %d\n", n, result);
     }
     
     printf("\n=== Detailed Example: factorial(5) ===\n");
     printf("Call Stack Visualization:\n\n");
     
     printf("Step 1: main() calls factorial(5)\n");
     printf("  Stack: [main] -> [factorial(5)]\n\n");
     
     printf("Step 2: factorial(5) calls factorial(4)\n");
     printf("  Stack: [main] -> [factorial(5)] -> [factorial(4)]\n\n");
     
     printf("Step 3: factorial(4) calls factorial(3)\n");
     printf("  Stack: [main] -> [factorial(5)] -> [factorial(4)] -> [factorial(3)]\n\n");
     
     printf("Step 4: factorial(3) calls factorial(2)\n");
     printf("  Stack: [main] -> [factorial(5)] -> [factorial(4)] -> [factorial(3)] -> [factorial(2)]\n\n");
     
     printf("Step 5: factorial(2) calls factorial(1)\n");
     printf("  Stack: [main] -> [factorial(5)] -> [factorial(4)] -> [factorial(3)] -> [factorial(2)] -> [factorial(1)]\n\n");
     
     printf("Step 6: factorial(1) returns 1 (base case)\n");
     printf("  Stack: [main] -> [factorial(5)] -> [factorial(4)] -> [factorial(3)] -> [factorial(2)]\n");
     printf("  factorial(2) computes: 2 * 1 = 2\n\n");
     
     printf("Step 7: factorial(2) returns 2\n");
     printf("  Stack: [main] -> [factorial(5)] -> [factorial(4)] -> [factorial(3)]\n");
     printf("  factorial(3) computes: 3 * 2 = 6\n\n");
     
     printf("Step 8: factorial(3) returns 6\n");
     printf("  Stack: [main] -> [factorial(5)] -> [factorial(4)]\n");
     printf("  factorial(4) computes: 4 * 6 = 24\n\n");
     
     printf("Step 9: factorial(4) returns 24\n");
     printf("  Stack: [main] -> [factorial(5)]\n");
     printf("  factorial(5) computes: 5 * 24 = 120\n\n");
     
     printf("Step 10: factorial(5) returns 120\n");
     printf("  Stack: [main]\n");
     printf("  Final result: 120\n\n");
     
     return 0;
 }