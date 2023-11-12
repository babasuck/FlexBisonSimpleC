#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Функция для создания узла целочисленного литерала
ASTNode* createIntNode(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_INTEGER;
    node->data.intValue = value;
    printNode(node);
    return node;
}

// Функция для создания узла литерала с плавающей точкой
ASTNode* createDoubleNode(double value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_DOUBLE;
    node->data.doubleValue = value;
    printNode(node);
    return node;
}

// Функция для создания узла логического литерала
ASTNode* createBoolNode(bool value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_BOOL;
    node->data.boolValue = value;
    printNode(node);
    return node;
}

// Функция для создания узла идентификатора
ASTNode* createIdentifierNode(char *identifier) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_IDENTIFIER;
    node->data.identifier = strdup(identifier);
    printNode(node);
    return node;
}

// Функция для создания узла присваивания
ASTNode* createAssignmentNode(char *identifier, ASTNode *expression) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_ASSIGNMENT;
    node->data.assignment.identifier = strdup(identifier);
    node->data.assignment.expression = expression;
    printNode(node);
    return node;
}

// Функция для создания узла бинарной операции
ASTNode* createBinaryOpNode(char op, ASTNode *left, ASTNode *right) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_BINARY_OP;
    node->data.binaryOp.op = op;
    node->data.binaryOp.left = left;
    node->data.binaryOp.right = right;
    printNode(node);
    return node;
}

// Функция для создания узла объявления переменной
ASTNode* createVariableDeclarationNode(char *type, char *identifier) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_VARIABLE_DECLARATION;
    node->data.variableDeclaration.type = strdup(type);
    node->data.variableDeclaration.identifier = strdup(identifier);
    printNode(node);
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
