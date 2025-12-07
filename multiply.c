

 #include <stdio.h>

 /**
  * Recursive multiplication function
  * Implements: a * b = a + a + ... + a (b times)
  * 
  * @param a: First operand (the number to add repeatedly)
  * @param b: Second operand (how many times to add)
  * @return: a * b
  * 
  * Example: multiply(3, 4) = 3 + 3 + 3 + 3 = 12
  */
 int multiply(int a, int b) {
     // Base case: anything multiplied by 0 is 0
     if (b == 0) {
         return 0;
     }
     
     // Handle negative multiplier
     if (b < 0) {
         return -multiply(a, -b);
     }
     
     // Recursive case: a * b = a + (a * (b-1))
     return a + multiply(a, b - 1);
 }
 
 /**
  * Main driver program
  * 
  * Tests recursive multiplication with various inputs
  */
 int main() {
     printf("=== Recursive Multiplication ===\n\n");
     
     // Test cases
     printf("Test Cases:\n");
     printf("multiply(3, 4) = %d (expected: 12)\n", multiply(3, 4));
     printf("multiply(5, 6) = %d (expected: 30)\n", multiply(5, 6));
     printf("multiply(7, 2) = %d (expected: 14)\n", multiply(7, 2));
     printf("multiply(10, 0) = %d (expected: 0)\n", multiply(10, 0));
     
     printf("\n=== Detailed Example: multiply(3, 4) ===\n");
     printf("Computing: 3 * 4 using recursion\n\n");
     
     printf("Call Sequence:\n");
     printf("1. main() calls multiply(3, 4)\n");
     printf("   Stack: [main] -> [multiply(3,4)]\n\n");
     
     printf("2. multiply(3, 4) calls multiply(3, 3)\n");
     printf("   Stack: [main] -> [multiply(3,4)] -> [multiply(3,3)]\n\n");
     
     printf("3. multiply(3, 3) calls multiply(3, 2)\n");
     printf("   Stack: [main] -> [multiply(3,4)] -> [multiply(3,3)] -> [multiply(3,2)]\n\n");
     
     printf("4. multiply(3, 2) calls multiply(3, 1)\n");
     printf("   Stack: [main] -> [multiply(3,4)] -> [multiply(3,3)] -> [multiply(3,2)] -> [multiply(3,1)]\n\n");
     
     printf("5. multiply(3, 1) calls multiply(3, 0)\n");
     printf("   Stack: [main] -> [multiply(3,4)] -> [multiply(3,3)] -> [multiply(3,2)] -> [multiply(3,1)] -> [multiply(3,0)]\n\n");
     
     printf("Return Sequence:\n");
     printf("6. multiply(3, 0) returns 0 (base case)\n");
     printf("   Stack: [main] -> [multiply(3,4)] -> [multiply(3,3)] -> [multiply(3,2)] -> [multiply(3,1)]\n");
     printf("   multiply(3,1) computes: 3 + 0 = 3\n\n");
     
     printf("7. multiply(3, 1) returns 3\n");
     printf("   Stack: [main] -> [multiply(3,4)] -> [multiply(3,3)] -> [multiply(3,2)]\n");
     printf("   multiply(3,2) computes: 3 + 3 = 6\n\n");
     
     printf("8. multiply(3, 2) returns 6\n");
     printf("   Stack: [main] -> [multiply(3,4)] -> [multiply(3,3)]\n");
     printf("   multiply(3,3) computes: 3 + 6 = 9\n\n");
     
     printf("9. multiply(3, 3) returns 9\n");
     printf("   Stack: [main] -> [multiply(3,4)]\n");
     printf("   multiply(3,4) computes: 3 + 9 = 12\n\n");
     
     printf("10. multiply(3, 4) returns 12\n");
     printf("    Stack: [main]\n");
     printf("    Final result: 12\n\n");
     
     return 0;
 }