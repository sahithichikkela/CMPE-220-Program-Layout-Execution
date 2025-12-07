; ======================================================================
; RECURSIVE MULTIPLICATION IMPLEMENTATION
; For Software CPU Emulator
; ======================================================================
;
; Function: multiply(a, b)
;   if (b == 0) return 0
;   else return a + multiply(a, b-1)
;
; Convention:
;   B = a (multiplicand) – never modified
;   A = b (multiplier)   – decremented in recursion
;   Result is always returned in A.
; ======================================================================

; ======================================================================
; MAIN PROGRAM (Driver)
; ======================================================================
main:
    LOAD #3
    MOV A B

    LOAD #4

    CALL multiply

    HALT

; ======================================================================
; MULTIPLY FUNCTION (recursive)
; multiply(a, b):
;   if (b == 0) return 0
;   else return a + multiply(a, b-1)
; ======================================================================
multiply:
    CMP #0
    JZ mult_base

    PUSH A
    SUB #1
    CALL multiply

    MOV A C
    POP A
    LOAD B
    ADD C
    RET

mult_base:
    LOAD #0
    RET
