#pragma once
#include <stdbool.h>
#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>

typedef struct ASTNode ASTNode;

// Определение типов узлов AST
typedef enum {
    AST_INTEGER,
    AST_DOUBLE,
    AST_BOOL,
    AST_IDENTIFIER,
    AST_BINARY_OP,
    AST_ASSIGNMENT,
    AST_VARIABLE_DECLARATION
} NodeType;

// Структура для бинарных операций
struct BinaryOpNode {
    char op;              // Оператор
    ASTNode *left;        // Левый операнд
    ASTNode *right;       // Правый операнд
};

// Структура для присваиваний
struct AssignmentNode {
    char *identifier;     // Идентификатор переменной
    ASTNode *expression;  // Выражение для присваивания
};

// Структура для объявления переменных
struct VariableDeclarationNode {
    char *type;           // Тип переменной
    char *identifier;     // Идентификатор переменной
};

struct ASTNode {
    NodeType type;       
    LLVMValueRef llvmValue;
    union {
        int intValue;                            
        double doubleValue;                     
        bool boolValue;                          
        char *identifier;                       
        struct BinaryOpNode binaryOp;            
        struct AssignmentNode assignment;        
        struct VariableDeclarationNode variableDeclaration; 
    } data;
};

// Прототипы функций для работы с AST
ASTNode* createIntNode(int value);
ASTNode* createDoubleNode(double value);
ASTNode* createBoolNode(bool value);
ASTNode* createIdentifierNode(char *identifier);
ASTNode* createAssignmentNode(char *identifier, ASTNode *expression);
ASTNode* createBinaryOpNode(char op, ASTNode *left, ASTNode *right);
ASTNode* createVariableDeclarationNode(char *type, char *identifier);
void printNode(ASTNode *node);
void setupLLVM();
void saveIRToFile(const char* filename);