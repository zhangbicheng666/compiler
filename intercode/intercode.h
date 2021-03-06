#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include "../ast/AST.h"
#include"../symtab/fssymtab.h"

enum ARGTYPE
{
    NULL_ARG = 0,       // null
    TEMP,               // temp
    VAR,                // var
    FUNC_MAIN,          // FUNCTION main
    FUNC,               // FUNCTION
    ARG_CONSTANT,       // #
    ARR,                // arr
    LABEL,              // label
    ARG_STRUCT,         // struct
};

enum USAGE
{
    ORIGIN = 0,         // normal    
    ADDRESS,            // &
    CONTENT,            // *
};

enum OPTYPE
{
    NULL_TYPE = 0,      // null
    DOP_ADD,            // +
    DOP_MINUS,          // -
    DOP_MULTIPLY,        // *
    DOP_DIVIDE,         // /
    DOP_MOD,            // %
    DOP_POW,            // ^
    DOP_ASSIGNMENT,     // =
    DOP_GETVALUE,       // []
    OP_READ,            // CALL cin
    OP_PRINT,           // CALL cout
    RELOP_L,            // >
    RELOP_S,            // <
    RELOP_EQUALS,       // ==
    RELOP_LOE,          // <=
    RELOP_SOE,          // >=
    JUMP_L,             // IF > GOTO
    JUMP_S,             // IF < GOTO
    JUMP_EQUALS,        // IF == GOTO
    JUMP_UNEQUAL,       // IF != GOTO
    JUMP_LOE,           // IF <= GOTO
    JUMP_SOE,           // IF >= GOTO
    FJUMP_L,            // IFNOT > GOTO
    FJUMP_S,            // IFNOT < GOTO
    FJUMP_EQUALS,       // IFNOT == GOTO
    FJUMP_UNEQUAL,      // IFNOT != GOTO
    FJUMP_LOE,          // IFNOT <= GOTO
    FJUMP_SOE,          // IFNOT >= GOTO
    FUNC_DEF,           // FUNCTION func_name
    END_FUNC,           // END func_name
    FUNCTION_CALL,      // CALL func_name
    PARAM,              // PARAM
    ARG,                // ARG
    OP_LABEL,           // LABEL
    GOTO,               // GOTO
    ARRAY_DECLARATION,  // DEC 
    OP_RETURN,          // RETURN
    STRUCT_DEFINITION,  // struct
};

std::string itos(int n);

class VarPair 
{
public:
    USAGE usage;
    ARGTYPE type;
    int index;
    std::string name;
    std::string struct_name;
    VarPair();
    VarPair(ARGTYPE type, int index);
    VarPair(ARGTYPE type, std::string name);
    VarPair(ARGTYPE type, int index, std::string name);
    VarPair(ARGTYPE type, int index, std::string var_name, std::string struct_name);
};

class InterCode 
{
private:
    VarPair result;
    OPTYPE op;
    VarPair arg1;
    VarPair arg2;
    static std::string toString(VarPair arg);
public:
    InterCode();
    InterCode(OPTYPE op);
    InterCode(OPTYPE op, VarPair result);
    InterCode(VarPair arg, OPTYPE op, VarPair result);
    InterCode(VarPair arg1, VarPair arg2, OPTYPE op, VarPair result);
    void setResult(VarPair result);
    void setOperator(OPTYPE op);
    void setArgFirst(VarPair arg1);
    void setArgSecond(VarPair arg2);
    VarPair getResult();
    OPTYPE getOperator();
    VarPair getArgFirst();
    VarPair getArgSecond();

    std::string printCode();
};

class Varlistnode 
{
private:
    std::vector<VarPair> varlist;
    Varlistnode* father;
public:
    Varlistnode();
    Varlistnode(Varlistnode* father);
    void addVar(VarPair vp);
    VarPair findVar(std::string name);
    Varlistnode* getFather();
};

class InterCodeList
{
private:
    static int label_count;                 // counter for label
    static int temp_count;                  // counter for TEMP
    static int var_count;                   // counter for VAR
    static int arr_count;                   // counter for ARR
    static int func_count;                  // counter for FUNC
    struct_symtab* struct_tab;
    std::vector<InterCode> list;
    Varlistnode* root_list;
    std::unordered_map<int, int> constant_pool;
    void classify();
    void arithmetic(ASTNode* root, Varlistnode* vlist, VarPair temp_result);
    void fake_arithmetic(ASTNode* root, Varlistnode* vlist);
    void makeConditions(ASTNode* condition, VarPair success, VarPair failure, int codetype, Varlistnode* vlist);
    void addConst(int value, int index);
    int checkConst(int value);
    void read(ASTNode* root, Varlistnode* vlist, VarPair break_label, VarPair continue_label);
    void label_recycle();
public:
    InterCodeList(struct_symtab* tab);
    int getListSize();
    void read(ASTNode* root);
    void printCodeList();
};
