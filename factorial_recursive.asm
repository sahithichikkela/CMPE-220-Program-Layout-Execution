start:
    LOAD #5
    CALL factorial
    HALT

factorial:
    CMP #1
    JZ base_case
    
    PUSH A
    SUB #1
    CALL factorial
    
    MOV A B
    POP A
    MUL B
    RET

base_case:
    LOAD #1
    RET