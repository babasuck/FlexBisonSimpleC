#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setupLLVM() {
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();
    LLVMInitializeNativeAsmParser();

    GlobalContext = LLVMContextCreate();
    GlobalModule = LLVMModuleCreateWithNameInContext("test_module", GlobalContext);
    GlobalBuilder = LLVMCreateBuilderInContext(GlobalContext);
}

// Функция для создания узла целочисленного литерала
ASTNode* createIntNode(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_INTEGER;
    node->data.intValue = value;
    node->llvmValue = LLVMConstInt(LLVMInt32TypeInContext(GlobalContext), value, 0);
    return node;
}

// Функция для создания узла литерала с плавающей точкой
ASTNode* createDoubleNode(double value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_DOUBLE;
    node->data.doubleValue = value;
    node->llvmValue = LLVMConstReal(LLVMDoubleTypeInContext(GlobalContext), value);
    return node;
}

// Функция для создания узла логического литерала
ASTNode* createBoolNode(bool value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_BOOL;
    node->data.boolValue = value;
    node->llvmValue = LLVMConstInt(LLVMInt1TypeInContext(GlobalContext), value, 0);
    return node;
}

// Функция для создания узла идентификатора
ASTNode* createIdentifierNode(char *identifier) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_IDENTIFIER;
    node->data.identifier = strdup(identifier);

    node->llvmValue = LLVMGetNamedGlobal(GlobalModule, identifier);

    if (!node->llvmValue) {
        LLVMTypeRef varType = LLVMInt32TypeInContext(GlobalContext);
        node->llvmValue = LLVMAddGlobal(GlobalModule, varType, identifier);
        LLVMSetInitializer(node->llvmValue, LLVMConstInt(varType, 0, 0));
    }

    return node;
}

// Функция для создания узла присваивания
ASTNode* createAssignmentNode(char *identifier, ASTNode *expression) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_ASSIGNMENT;
    node->data.assignment.identifier = strdup(identifier);
    node->data.assignment.expression = expression;

    LLVMValueRef var = LLVMGetNamedGlobal(GlobalModule, identifier);

    if (!var) {
        node->llvmValue = NULL;
        return node;
    }

    node->llvmValue = LLVMBuildStore(GlobalBuilder, expression->llvmValue, var);

    return node;
}

// Функция для создания узла бинарной операции
ASTNode* createBinaryOpNode(char op, ASTNode *left, ASTNode *right) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_BINARY_OP;
    node->data.binaryOp.op = op;
    node->data.binaryOp.left = left;
    node->data.binaryOp.right = right;

    LLVMValueRef lValue = left->llvmValue;
    LLVMValueRef rValue = right->llvmValue;

    switch (op) {
        case '+':
            node->llvmValue = LLVMBuildAdd(GlobalBuilder, lValue, rValue, "addtmp");
            break;
        case '-':
            node->llvmValue = LLVMBuildSub(GlobalBuilder, lValue, rValue, "subtmp");
            break;
        case '*':
            node->llvmValue = LLVMBuildMul(GlobalBuilder, lValue, rValue, "multmp");
            break;
        case '/':
            node->llvmValue = LLVMBuildSDiv(GlobalBuilder, lValue, rValue, "divtmp");
            break;
        default:
            node->llvmValue = NULL;
            break;
    }

    return node;
}

// Функция для создания узла объявления переменной
ASTNode* createVariableDeclarationNode(char *type, char *identifier) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_VARIABLE_DECLARATION;
    node->data.variableDeclaration.type = strdup(type);
    node->data.variableDeclaration.identifier = strdup(identifier);

    LLVMTypeRef varType = LLVMInt32TypeInContext(GlobalContext);
    LLVMValueRef var = LLVMAddGlobal(GlobalModule, varType, identifier);
    LLVMSetInitializer(var, LLVMConstInt(varType, 0, 0)); 
    node->llvmValue = var;

    return node;
}

void printNode(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case AST_INTEGER:
            printf("Integer: %d\n", node->data.intValue);
            break;
        case AST_DOUBLE:
            printf("Double: %f\n", node->data.doubleValue);
            break;
        case AST_BOOL:
            printf("Bool: %s\n", node->data.boolValue ? "true" : "false");
            break;
        case AST_IDENTIFIER:
            printf("Identifier: %s\n", node->data.identifier);
            break;
        case AST_BINARY_OP:
            printf("Binary Op: %c\n", node->data.binaryOp.op);
            printNode(node->data.binaryOp.left);
            printNode(node->data.binaryOp.right);
            break;
        case AST_ASSIGNMENT:
            printf("Assignment to %s\n", node->data.assignment.identifier);
            printNode(node->data.assignment.expression);
            break;
        case AST_VARIABLE_DECLARATION:
            printf("Declaration of %s: %s\n", node->data.variableDeclaration.type, node->data.variableDeclaration.identifier);
            break;
    }
}
