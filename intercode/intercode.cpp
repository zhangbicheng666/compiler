#include "intercode.h"
#define INT_SIZE 4


std::string itos(int n)
{
    std::ostringstream ostr;
    ostr << n;
    std::string astr = ostr.str();
    return astr;
};

// class VarPair
VarPair::VarPair()
{
    this -> type = NULL_ARG;
    this -> index = -1;
    this -> name = "";
    this -> usage = ORIGIN;
};

VarPair::VarPair(ARGTYPE type, int index)
{
    this -> type = type;
    this -> index = index;
    this -> usage = ORIGIN;
};

VarPair::VarPair(ARGTYPE type, std::string name)
{
    this -> type = type;
    this -> name = name;
    this -> usage = ORIGIN;
};

VarPair::VarPair(ARGTYPE type, int index, std::string name)
{
    this -> type = type;
    this -> index = index;
    this -> name = name;
    this -> usage = ORIGIN;
};

// class InterCode
std::string InterCode::toString(VarPair arg)
{
    std::string p1, p2, p3;
    switch (arg.usage)
    {
        case ORIGIN:
        {
            p1 = "";
            break;
        }
        case ADDRESS:
        {
            p1 = "&";
            break;
        }
        case CONTENT:
        {
            p1 = "*";
            break;
        }
        default:
        {
            p1 = "";
            // Programming Error
            break;
        }
    }
    switch (arg.type)
    {
        case TEMP:
        {
            p2 = "temp";
            break;
        }
        case VAR:
        {
            p2 = "var";
            break;
        }
        case ARGTYPE::ARG_CONSTANT:
        {
            p2 = "#";
            break;
        }
        case ARR:
        {
            p2 = "array";
            break;
        }
        case FUNC:
        {
            p2 = arg.name;
            break;
        }
        case LABEL:
        {
            p2 = "label";
            break;
        }
        default:
        {
            p2 = "";
            // Programming Error
            break;
        }
    }
    // printf("%d", arg.index);
    p3 = itos(arg.index);
    std::string ss = p1 + p2 + p3;
    // printf("(%s, %s, %s)\n", p1.c_str(), p2.c_str(), p3.c_str());
    return ss;
};

InterCode::InterCode()
{
    this -> result = VarPair();
    this -> op = NULL_TYPE;
    this -> arg1 = VarPair();
    this -> arg2 = VarPair();
};

InterCode::InterCode(OPTYPE op)
{
    this -> result = VarPair();
    this -> op = op;
    this -> arg1 = VarPair();
    this -> arg2 = VarPair();
};

InterCode::InterCode(OPTYPE op, VarPair result)
{
    this -> result = result;
    this -> op = op;
    this -> arg1 = VarPair();
    this -> arg2 = VarPair();
};

InterCode::InterCode(VarPair arg, OPTYPE op, VarPair result)
{
    this -> result = result;
    this -> op = op;
    this -> arg1 = arg;
    this -> arg2 = VarPair();
};

InterCode::InterCode(VarPair arg1, VarPair arg2, OPTYPE op, VarPair result)
{
    this -> result = result;
    this -> op = op;
    this -> arg1 = arg1;
    this -> arg2 = arg2;
};

void InterCode::setResult(VarPair result)
{
    this -> result = result;
};

void InterCode::setOperator(OPTYPE op)
{
    this -> op = op;
};

void InterCode::setArgFirst(VarPair arg1)
{
    this -> arg1 = arg1;
};

void InterCode::setArgSecond(VarPair arg2)
{
    this -> arg2 = arg2;
};

VarPair InterCode::getResult()
{
    return this -> result;
};

OPTYPE InterCode::getOperator()
{
    return this -> op;
};

VarPair InterCode::getArgFirst()
{
    return this -> arg1;
};

VarPair InterCode::getArgSecond()
{
    return this -> arg2;
};

std::string InterCode::printCode()
{
    std::string code = "";
    switch (this -> op)
    {
        case DOP_ASSIGNMENT:
        {
            if (this -> arg2.type == NULL_ARG)
            {
                code += toString(this -> result);
                code += " := ";
                code += toString(this -> arg1);
                code += "\n";
            }
            else
            {
                code += toString(this -> arg1);
                code += " := ";
                code += toString(this -> arg2);
                code += "\n";
                code += toString(this -> result);
                code += " := ";
                code += toString(this -> arg1);
                code += "\n";
            }
            break;
        }
        case DOP_ADD:
        {
            code += toString(this -> result);
            code += " := ";
            code += toString(this -> arg1);
            code += " + ";
            code += toString(this -> arg2);
            code += "\n";
            break;
        }
        case DOP_MINUS:
        {
            code += toString(this -> result);
            code += " := ";
            code += toString(this -> arg1);
            code += " - ";
            code += toString(this -> arg2);
            code += "\n";
            break;
        }
        case DOP_MULTIPLY:
        {
            code += toString(this -> result);
            code += " := ";
            code += toString(this -> arg1);
            code += " * ";
            code += toString(this -> arg2);
            code += "\n";
            break;
        }
        case DOP_DIVIDE:
        {
            code += toString(this -> result);
            code += " := ";
            code += toString(this -> arg1);
            code += " / ";
            code += toString(this -> arg2);
            code += "\n";
            break;
        }
        case DOP_GETVALUE:
        {
            code += toString(this -> result);
            code += " := &";
            code += toString(this -> arg1);
            code += " + ";
            code += toString(this -> arg2);
            code += "\n";
            break;
        }
        case FUNC_DEF:
        {
            code += "FUNCTION ";
            code += this -> result.name;
            code += ":\n";
            break;
        }
        case ARRAY_DECLARATION:
        {
            code += "DEC ";
            code += toString(this -> result);
            code += " ";
            code += toString(this -> arg1);
            code += "\n";
            break;
        }
        case OP_READ:
        {
            code += toString(this -> result);
            code += " := CALL cin\n";
            break;
        }
        case OP_PRINT:
        {
            code += "CALL cout\n";
            break;
        }
        case PARAM:
        {
            code += "RARAM ";
            code += toString(this -> result);
            code += "\n";
            break;
        }
        case ARG:
        {
            code += "ARG ";
            code += toString(this -> result);
            code += "\n";
            break;
        }
        case OP_LABEL:
        {
            code += "LABEL ";
            code += toString(this -> result);
            code += " :\n";
            break;
        }
        case GOTO:
        {
            code += "GOTO ";
            code += toString(this -> result);
            code += "\n";
            break;
        }
        case OP_RETURN:
        {
            code += "RETURN ";
            code += toString(this -> result);
            code += "\n";
            break;
        }
        case JUMP_L:
        {
            code += "IF ";
            code += toString(this -> arg1);
            code += " > ";
            code += toString(this -> arg2);
            code += " GOTO ";
            code += toString(this -> result);
            code += "\n";
            break;
        }
        case JUMP_S:
        {
            code += "IF ";
            code += toString(this -> arg1);
            code += " < ";
            code += toString(this -> arg2);
            code += " GOTO ";
            code += toString(this -> result);
            code += "\n";
            break;
        }
        case JUMP_LOE:
        {
            code += "IF ";
            code += toString(this -> arg1);
            code += " >= ";
            code += toString(this -> arg2);
            code += " GOTO ";
            code += toString(this -> result);
            code += "\n";
            break;
        }
        case JUMP_SOE:
        {
            code += "IF ";
            code += toString(this -> arg1);
            code += " <= ";
            code += toString(this -> arg2);
            code += " GOTO ";
            code += toString(this -> result);
            code += "\n";
            break;
        }
        case JUMP_EQUALS:
        {
            code += "IF ";
            code += toString(this -> arg1);
            code += " == ";
            code += toString(this -> arg2);
            code += " GOTO ";
            code += toString(this -> result);
            code += "\n";
            break;
        }
        case JUMP_UNEQUAL:
        {
            code += "IF ";
            code += toString(this -> arg1);
            code += " != ";
            code += toString(this -> arg2);
            code += " GOTO ";
            code += toString(this -> result);
            code += "\n";
            break;
        }
        case FJUMP_L:
        {
            code += "IFNOT ";
            code += toString(this -> arg1);
            code += " > ";
            code += toString(this -> arg2);
            code += " GOTO ";
            code += toString(this -> result);
            code += "\n";
            break;
        }
        case FJUMP_S:
        {
            code += "IFNOT ";
            code += toString(this -> arg1);
            code += " < ";
            code += toString(this -> arg2);
            code += " GOTO ";
            code += toString(this -> result);
            code += "\n";
            break;
        }
        case FJUMP_LOE:
        {
            code += "IFNOT ";
            code += toString(this -> arg1);
            code += " >= ";
            code += toString(this -> arg2);
            code += " GOTO ";
            code += toString(this -> result);
            code += "\n";
            break;
        }
        case FJUMP_SOE:
        {
            code += "IFNOT ";
            code += toString(this -> arg1);
            code += " <= ";
            code += toString(this -> arg2);
            code += " GOTO ";
            code += toString(this -> result);
            code += "\n";
            break;
        }
        case FJUMP_EQUALS:
        {
            code += "IFNOT ";
            code += toString(this -> arg1);
            code += " == ";
            code += toString(this -> arg2);
            code += " GOTO ";
            code += toString(this -> result);
            code += "\n";
            break;
        }
        case FJUMP_UNEQUAL:
        {
            code += "IFNOT ";
            code += toString(this -> arg1);
            code += " != ";
            code += toString(this -> arg2);
            code += " GOTO ";
            code += toString(this -> result);
            code += "\n";
            break;
        }
        case NULL_ARG:
        {
            /* code */
            break;
        }
        default:
        {
            break;
        }
    }
    return code;
};

// class Varlistnode
Varlistnode::Varlistnode()
{
    this -> father = NULL;
};

Varlistnode::Varlistnode(Varlistnode* father)
{
    this -> father = father;
};

void Varlistnode::addVar(VarPair vp)
{
    this -> varlist.push_back(vp);
};

VarPair Varlistnode::findVar(std::string name)
{
    Varlistnode* temp = this;
    while (true)
    {
        std::vector<VarPair>* list = &(temp -> varlist);
        for (auto iter = list -> begin(); iter != list -> end(); iter ++)
        {
            // printf("%s\n", (iter -> name).c_str());
            if (name == iter -> name)
                return VarPair(iter -> type, iter -> index, iter -> name);
        }
        if (temp -> father != NULL)
            temp = temp -> father;
        else 
            break;
    }
    return VarPair();
};

Varlistnode* Varlistnode::getFather()
{
    return this -> father;
};

// class InterCodeList
int InterCodeList::label_count = 0;

int InterCodeList::temp_count = 0;
   
int InterCodeList::var_count = 0;  

int InterCodeList::arr_count = 0;

void InterCodeList::classify()
{
    // to be completed
};

void InterCodeList::arithmetic(ASTNode* root, Varlistnode* vlist, VarPair temp_result)
{
    ASTNode* left = (*(root->getChildren()))[0];
    ASTNode* right = (*(root->getChildren()))[1];
    VarPair left_value;
    VarPair right_value;
    OPTYPE op;
    if (root -> msg == "Assignment Expression")
    { 
        if (left -> msg == "ID Declaration")
        {
            left_value = vlist -> findVar(left -> name);
            if (left_value.type == NULL_ARG)
            {
                printf("%s\n", left -> name.c_str());
                printf("error: variable undefined\n");
                exit(-1);
                // error: variable undefined
            }
            else if (left_value.type == ARR)
            {
                printf("\"%s\": Type \"ARR\"\n", left -> name.c_str());
                printf("error: can't be a left value\n");
                exit(-1);
                // error: can't be a left value
            }
            else
            {
                
            }
        }
        else if (left -> msg == "Const Declaration")
        {
            printf("error: a constant value can't be a left value\n");
            exit(-1);
            // error: a constant value can't be a left value
        }
        else
        {
            left_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(left, vlist, left_value);
        }
        if (right -> msg == "ID Declaration")
        {
            right_value = vlist -> findVar(right -> name);
            if (right_value.type == NULL_ARG)
            {
                printf("%s\n", right -> name.c_str());
                printf("error: variable undefined\n");
                exit(-1);
                // error: variable undefined
            }
            else
            {

            }
        }
        else if (right -> msg == "Const Declaration")
        {
            int const_value = atoi(right -> name.c_str());
            int temp_index = this -> checkConst(const_value);
            if(temp_index == -1)
            {
                this -> addConst(const_value, temp_count);
                right_value = VarPair(TEMP, temp_count++);
                VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                (this->list).push_back(InterCode(constant, DOP_ASSIGNMENT, right_value));
            }
            else
                right_value = VarPair(TEMP, temp_index);
        }
        else
        {
            right_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(right, vlist, right_value);
        }
        op = DOP_ASSIGNMENT;
    }
    else if (root -> msg == "Additive Expression")
    {
        if (left -> msg == "ID Declaration")
        {
            left_value = vlist -> findVar(left -> name);
            if (left_value.type == NULL_ARG)
            {
                printf("%s\n", left -> name.c_str());
                printf("error: variable undefined\n");
                exit(-1);
                // error: variable undefined
            }
            else if (left_value.type == ARR)
            {
                printf("\"%s\": Type \"ARR\"\n", left -> name.c_str());
                printf("error: can't be a left value\n");
                exit(-1);
                // error: can't be a left value
            }
            else
            {
                
            }
        }
        else if (left -> msg == "Const Declaration")
        {
            int const_value = atoi(left -> name.c_str());
            int temp_index = this -> checkConst(const_value);
            if(temp_index == -1)
            {
                this -> addConst(const_value, temp_count);
                left_value = VarPair(TEMP, temp_count++);
                VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, left_value));
            }
            else
                left_value = VarPair(TEMP, temp_index);
        }
        else
        {
            left_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(left, vlist, left_value);
        }
        if (right -> msg == "ID Declaration")
        {
            right_value = vlist -> findVar(right -> name);
            if (right_value.type == NULL_ARG)
            {
                printf("%s\n", right -> name.c_str());
                printf("error: variable undefined\n");
                exit(-1);
                // error: variable undefined
            }
            else
            {
                
            }
        }
        else if (right -> msg == "Const Declaration")
        {
            int const_value = atoi(right -> name.c_str());
            int temp_index = this->checkConst(const_value);
            if(temp_index == -1)
            {
                this -> addConst(const_value, temp_count);
                right_value = VarPair(TEMP, temp_count++);
                VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, right_value));
            }
            else
                right_value = VarPair(TEMP, temp_index);
        }
        else
        {
            right_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(right, vlist, right_value);
        }
        if (root -> name == "arithmetic_op:+")
            op = DOP_ADD;
        else
            op = DOP_MINUS;
    }
    else if (root -> msg == "Multiplicative Expression")
    {
        if (left -> msg == "ID Declaration")
        {
            left_value = vlist -> findVar(left -> name);
            if (left_value.type == NULL_ARG)
            {
                printf("%s\n", left -> name.c_str());
                printf("error: variable undefined\n");
                exit(-1);
                // error: variable undefined
            }
            else if (left_value.type == ARR)
            {
                printf("\"%s\": Type \"ARR\"\n", left -> name.c_str());
                printf("error: can't be a left value\n");
                exit(-1);
                // error: can't be a left value
            }
            else
            {
                
            }
        }
        else if (left -> msg == "Const Declaration")
        {
            int const_value = atoi(left -> name.c_str());
            int temp_index = this -> checkConst(const_value);
            if(temp_index == -1)
            {
                this -> addConst(const_value, temp_count);
                left_value = VarPair(TEMP, temp_count++);
                VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, left_value));
            }
            else
                left_value = VarPair(TEMP, temp_index);
        }
        else
        {
            left_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(left, vlist, left_value);
        }
        if (right -> msg == "ID Declaration")
        {
            right_value = vlist -> findVar(right -> name);
            if (right_value.type == NULL_ARG)
            {
                printf("%s\n", right -> name.c_str());
                printf("error: variable undefined\n");
                exit(-1);
                // error: variable undefined
            }
            else
            {
                
            }
        }
        else if (right -> msg == "Const Declaration")
        {
            int const_value = atoi(right -> name.c_str());
            int temp_index = this->checkConst(const_value);
            if(temp_index == -1)
            {
                this -> addConst(const_value, temp_count);
                right_value = VarPair(TEMP, temp_count++);
                VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, right_value));
            }
            else
                right_value = VarPair(TEMP, temp_index);
        }
        else
        {
            right_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(right, vlist, right_value);
        }
        if (root -> name == "arithmetic_op:*")
            op = DOP_MULTIPLY;
        else if (root -> name == "arithmetic_op:/")
            op = DOP_DIVIDE;
        else if (root -> name == "arithmetic_op:%")
        {
            op = DOP_MOD;
            // if (left -> msg == "Expr")
            //     left_value.usage = CONTENT;
            // if (right -> msg == "Expr")
            //     right_value.usage = CONTENT;
            // VarPair proccess1 = VarPair(TEMP, temp_count++);
            // VarPair proccess2 = VarPair(TEMP, temp_count++);
            // (this -> list).push_back(InterCode(left_value, right_value, DOP_DIVIDE, proccess1));
            // (this -> list).push_back(InterCode(proccess1, right_value, DOP_MULTIPLY, proccess2));
            // (this -> list).push_back(InterCode(left_value, proccess2, DOP_MINUS, temp_result));
        }
        else
        {
            printf("Multiplicative Expression: error: there shouldn't be other possibilities\n");
            exit(-1);
            // error: there shouldn't be other possibilities
        }
    }
    else if (root -> msg == "Pow Expression")
    {
        if (left -> msg == "ID Declaration")
        {
            left_value = vlist -> findVar(left -> name);
            if (left_value.type == NULL_ARG)
            {
                printf("%s\n", left -> name.c_str());
                printf("error: variable undefined\n");
                exit(-1);
                // error: variable undefined
            }
            else if (left_value.type == ARR)
            {
                printf("\"%s\": Type \"ARR\"\n", left -> name.c_str());
                printf("error: can't be a left value\n");
                exit(-1);
                // error: can't be a left value
            }
            else
            {
                
            }
        }
        else if (left -> msg == "Const Declaration")
        {
            int const_value = atoi(left -> name.c_str());
            int temp_index = this -> checkConst(const_value);
            if(temp_index == -1)
            {
                this -> addConst(const_value, temp_count);
                left_value = VarPair(TEMP, temp_count++);
                VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, left_value));
            }
            else
                left_value = VarPair(TEMP, temp_index);
        }
        else
        {
            left_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(left, vlist, left_value);
        }
        if (right -> msg == "ID Declaration")
        {
            right_value = vlist -> findVar(right -> name);
            if (right_value.type == NULL_ARG)
            {
                printf("%s\n", right -> name.c_str());
                printf("error: variable undefined\n");
                exit(-1);
                // error: variable undefined
            }
            else
            {
                
            }
        }
        else if (right -> msg == "Const Declaration")
        {
            int const_value = atoi(right -> name.c_str());
            int temp_index = this -> checkConst(const_value);
            if(temp_index == -1)
            {
                this -> addConst(const_value, temp_count);
                right_value = VarPair(TEMP, temp_count++);
                VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, right_value));
            }
            else
                right_value = VarPair(TEMP, temp_index);
        }
        else
        {
            right_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(right, vlist, right_value);
        }
        op = DOP_POW;
        if (left -> msg == "Expr")
            left_value.usage = CONTENT;
        if (right -> msg == "Expr")
            right_value.usage = CONTENT;
        VarPair if_true = VarPair(LABEL, label_count++);
        VarPair loop_start = VarPair(LABEL, label_count++);
        VarPair loop_leave = VarPair(LABEL, label_count++);
        VarPair constant_zero = VarPair(ARGTYPE::ARG_CONSTANT, 0);
        VarPair counter = VarPair(TEMP, temp_count++);
        (this -> list).push_back(InterCode(constant_zero, DOP_ASSIGNMENT, counter));
        (this -> list).push_back(InterCode(right_value, counter, FJUMP_S, if_true));
        (this -> list).push_back(InterCode(constant_zero, DOP_ASSIGNMENT, temp_result));
        (this -> list).push_back(InterCode(GOTO, loop_leave));
        (this -> list).push_back(InterCode(OP_LABEL, if_true));
        VarPair proccess1 = VarPair(TEMP, temp_count++);
        VarPair counter_inter = VarPair(TEMP, temp_count++);
        VarPair constant_one;
        int temp_index = this -> checkConst(1);
        if(temp_index == -1)
        {
            this -> addConst(1, temp_count);
            constant_one = VarPair(TEMP, temp_count++);
            VarPair one = VarPair(ARGTYPE::ARG_CONSTANT, 1);
            (this -> list).push_back(InterCode(one, DOP_ASSIGNMENT, constant_one));
        }
        else
            constant_one = VarPair(TEMP, temp_index);
        (this -> list).push_back(InterCode(constant_one, DOP_ASSIGNMENT, proccess1));
        (this -> list).push_back(InterCode(constant_one, DOP_ASSIGNMENT, temp_result));
        (this -> list).push_back(InterCode(OP_LABEL, loop_start));
        (this -> list).push_back(InterCode(counter, right_value, FJUMP_S, loop_leave));
        (this -> list).push_back(InterCode(proccess1, left_value, DOP_MULTIPLY, temp_result));
        (this -> list).push_back(InterCode(temp_result, DOP_ASSIGNMENT, proccess1));
        (this -> list).push_back(InterCode(counter, constant_one, DOP_ADD, counter_inter));
        (this -> list).push_back(InterCode(counter_inter, DOP_ASSIGNMENT, counter));
        (this -> list).push_back(InterCode(GOTO, loop_start));
        (this -> list).push_back(InterCode(OP_LABEL, loop_leave));
    }
    else if (root -> msg == "Expr")
    { 
        if (left -> msg == "ID Declaration")
        {
            left_value = vlist -> findVar(left -> name);
            if (left_value.type == NULL_ARG)
            {
                printf("%s\n", left -> name.c_str());
                printf("error: variable undefined\n");
                exit(-1);
                // error: variable undefined
            }
            else
            {
                
            }
        }
        else
        {
            printf("not a correct type with \"[]\"\n");
            exit(-1);
            // error: not a correct type with "[]"
        }
        if (right -> msg == "ID Declaration")
        {
            right_value = vlist -> findVar(right -> name);
            if (right_value.type == NULL_ARG)
            {
                printf("%s\n", right -> name.c_str());
                printf("error: variable undefined\n");
                exit(-1);
                // error: variable undefined
            }
            else
            {
                
            }
        }
        else if (right -> msg == "Const Declaration")
        {
            int const_value = atoi(right -> name.c_str());
            int temp_index = this -> checkConst(const_value);
            if(temp_index == -1)
            {
                this -> addConst(const_value, temp_count);
                right_value = VarPair(TEMP, temp_count++);
                VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, right_value));
            }
            else
                right_value = VarPair(TEMP, temp_index);
        }
        else
        {
            right_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(right, vlist, right_value);
        }
        op = DOP_GETVALUE;
        int temp_index = this -> checkConst(INT_SIZE);
        VarPair width;
        if(temp_index == -1)
        {
            VarPair size = VarPair(ARGTYPE::ARG_CONSTANT, INT_SIZE);
            this -> addConst(INT_SIZE, temp_count);
            width = VarPair(TEMP, temp_count++);
            (this -> list).push_back(InterCode(size, DOP_ASSIGNMENT, width));
        }
        else
            width = VarPair(TEMP, temp_index);
        VarPair raddress = VarPair(TEMP, temp_count++);
        (this -> list).push_back(InterCode(right_value, width, DOP_MULTIPLY, raddress));
        (this -> list).push_back(InterCode(left_value, raddress, op, temp_result));
    }
    // else if (root -> msg == "other")
    // {

    // }
    else
    {
        printf("arithmetic: error: there shouldn't be other possibilities\n");
        exit(-1);
        // error: there shouldn't be other possibilities
    }
    if (left -> msg == "Expr")
        left_value.usage = CONTENT;
    if (right -> msg == "Expr")
        right_value.usage = CONTENT;
    if (root -> msg != "Expr" && root -> msg != "Pow Expression")
        (this -> list).push_back(InterCode(left_value, right_value, op, temp_result));
};

void InterCodeList::fake_arithmetic(ASTNode* root, Varlistnode* vlist)
{
    if (root -> msg == "Assignment Expression")
    {
        this -> read(root, vlist, VarPair(), VarPair());
    }
    else
    {
        std::vector<ASTNode*>* children = root -> getChildren(); 
        for (auto iter = children -> begin(); iter != children -> end(); iter++)
            fake_arithmetic(*iter, vlist);
    }
};

void InterCodeList::makeConditions(ASTNode* condition, VarPair success, VarPair failure, int codetype, Varlistnode* vlist)
{
    if (condition -> msg == "Logical OR Expression")
    {
        std::vector<ASTNode*>* children = condition -> getChildren();
        VarPair new_failure;
        for (auto iter = children -> begin(); iter != children -> end(); iter++)
        {
            if (iter != children -> begin())
                (this -> list).push_back(InterCode(OP_LABEL, new_failure));
            if (iter != children -> end() - 1)
            {
                new_failure = VarPair(LABEL, label_count++);
                this -> makeConditions(*iter, success, new_failure, 1, vlist);
            }
            else
                this -> makeConditions(*iter, success, failure, 1, vlist);
        }
        if (codetype != 1)
            (this -> list).push_back(InterCode(GOTO, failure));
    }
    else if (condition -> msg == "Logical AND Expression")
    {
        std::vector<ASTNode*>* children = condition -> getChildren();
        VarPair new_success;
        for (auto iter = children -> begin(); iter != children -> end(); iter++)
        {
            if (iter != children -> begin())
                (this -> list).push_back(InterCode(OP_LABEL, new_success));
            if (iter != children -> end() - 1)
            {
                new_success = VarPair(LABEL, label_count++);
                this -> makeConditions(*iter, new_success, failure, 2, vlist);
            }
            else
                this -> makeConditions(*iter, new_success, failure, 2, vlist);
        }
        if (codetype != 2)
            (this -> list).push_back(InterCode(GOTO, success));
    }
    else if (condition -> msg == "Logical not expression")
    {
        ASTNode* child = (*(condition -> getChildren()))[0];
        this -> makeConditions(child, failure, success, codetype, vlist);
    }
    else if (condition -> msg == "Equality Expression")
    {
        ASTNode* left = (*(condition->getChildren()))[0];
        ASTNode* right = (*(condition->getChildren()))[1];
        VarPair left_value;
        VarPair right_value;
        OPTYPE op;
        if (left -> msg == "ID Declaration")
        {
            left_value = vlist -> findVar(left -> name);
            if(left_value.type == NULL_ARG)
            {
                printf("%s\n", left -> name.c_str());
                printf("error: variable undefined\n");
                exit(-1);
                // error: variable undefined
            }
            else
            {
                
            }
        }
        else if (left -> msg == "Const Declaration")
        {
            int const_value = atoi(left -> name.c_str());
            int temp_index = this -> checkConst(const_value);
            if(temp_index == -1)
            {
                this -> addConst(const_value, temp_count);
                left_value = VarPair(TEMP, temp_count++);
                VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, left_value));
            }
            else
                left_value = VarPair(TEMP, temp_index);
        }
        else
        {
            left_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(left, vlist, left_value);
        }
        if (right -> msg == "ID Declaration")
        {
            right_value = vlist -> findVar(right -> name);
            if(right_value.type == NULL_ARG)
            {
                printf("%s\n", right -> name.c_str());
                printf("error: variable undefined\n");
                exit(-1);
                // error: variable undefined
            }
            else
            {
                
            }
        }
        else if (right -> msg == "Const Declaration")
        {
            int const_value = atoi(right -> name.c_str());
            int temp_index = this -> checkConst(const_value);
            if(temp_index == -1)
            {
                this -> addConst(const_value, temp_count);
                right_value = VarPair(TEMP, temp_count++);
                VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, right_value));
            }
            else
                right_value = VarPair(TEMP, temp_index);
        }
        else
        {
            right_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(right, vlist, right_value);
        }
        if (condition -> name == "equality_op:==")
        {
            if (codetype != 2)
                op = JUMP_EQUALS;
            else
                op = FJUMP_EQUALS;
        }
        else if (condition -> name == "equality_op:!=")
        {
            if (codetype != 2)
                op = JUMP_UNEQUAL;
            else
                op = FJUMP_UNEQUAL;
        }
        else
        {
            printf("Equality Expression: error: there shouldn't be other possibilities\n");
            exit(-1);
            // error: there shouldn't be other possibilities
        }
        if (codetype != 2)
            (this -> list).push_back(InterCode(left_value, right_value, op, success));
        else
            (this -> list).push_back(InterCode(left_value, right_value, op, failure));
        if (codetype == 0)
            (this -> list).push_back(InterCode(GOTO, failure));
    }
    else if (condition -> msg == "Relational Expression")
    {
        ASTNode* left = (*(condition->getChildren()))[0];
        ASTNode* right = (*(condition->getChildren()))[1];
        VarPair left_value;
        VarPair right_value;
        OPTYPE op;
        if (left -> msg == "ID Declaration")
        {
            left_value = vlist -> findVar(left -> name);
            if(left_value.type == NULL_ARG)
            {
                printf("%s\n", left -> name.c_str());
                printf("error: variable undefined\n");
                exit(-1);
                // error: variable undefined
            }
            else
            {
                
            }
        }
        else if (left -> msg == "Const Declaration")
        {
            int const_value = atoi(left -> name.c_str());
            int temp_index = this -> checkConst(const_value);
            if(temp_index == -1)
            {
                this -> addConst(const_value, temp_count);
                left_value = VarPair(TEMP, temp_count++);
                VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, left_value));
            }
            else
                left_value = VarPair(TEMP, temp_index);
        }
        else
        {
            left_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(left, vlist, left_value);
        }
        if (right -> msg == "ID Declaration")
        {
            right_value = vlist -> findVar(right -> name);
            if(right_value.type == NULL_ARG)
            {
                printf("%s\n", right -> name.c_str());
                printf("error: variable undefined\n");
                exit(-1);
                // error: variable undefined
            }
            else
            {
                
            }
        }
        else if (right -> msg == "Const Declaration")
        {
            int const_value = atoi(right -> name.c_str());
            int temp_index = this -> checkConst(const_value);
            if(temp_index == -1)
            {
                this -> addConst(const_value, temp_count);
                right_value = VarPair(TEMP, temp_count++);
                VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, right_value));
            }
            else
                right_value = VarPair(TEMP, temp_index);
        }
        else
        {
            right_value = VarPair(TEMP, temp_count++);
            this -> arithmetic(right, vlist, right_value);
        }
        if (condition -> name == "relational_op:<")
        {
            if (codetype != 2)
                op = JUMP_S;
            else
                op = FJUMP_S;
        }
        else if (condition -> name == "relational_op:<=")
        {
            if (codetype != 2)
                op = JUMP_SOE;
            else
                op = FJUMP_SOE;
        }
        else if (condition -> name == "relational_op:>")
        {
            if (codetype != 2)
                op = JUMP_L;
            else
                op = FJUMP_L;
        }
        else if (condition -> name == "relational_op:>=")
        {
            if (codetype != 2)
                op = JUMP_LOE;
            else
                op = FJUMP_LOE;
        }
        else
        {
            printf("Relational Expression: error: there shouldn't be other possibilities\n");
            exit(-1);
            // error: there shouldn't be other possibilities
        }
        if (left -> msg == "Expr")
        {
            left_value.usage = CONTENT;
        }
        if (right -> msg == "Expr")
        {
            right_value.usage = CONTENT;
        }
        if (codetype != 2)
            (this -> list).push_back(InterCode(left_value, right_value, op, success));
        else
            (this -> list).push_back(InterCode(left_value, right_value, op, failure));
        if (codetype == 0)
            (this -> list).push_back(InterCode(GOTO, failure));
    }
    else if (condition -> msg == "ID Declaration")
    {
        VarPair var = vlist -> findVar(condition -> name);
        if(var.type == NULL_ARG)
        {
            printf("%s\n", condition -> name.c_str());
            printf("error: variable undefined\n");
            exit(-1);
            // error: variable undefined
        }
        else
        {
            
        }
        VarPair zero_temp;
        int temp_index = this -> checkConst(0);
        if(temp_index == -1)
        {
            this -> addConst(0, temp_count);
            zero_temp = VarPair(TEMP, temp_count++);
            VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, 0);
            (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, zero_temp));
        }
        else
            zero_temp = VarPair(TEMP, temp_index);
        if (codetype != 2)
            (this -> list).push_back(InterCode(var, zero_temp, JUMP_UNEQUAL, success));
        else
            (this -> list).push_back(InterCode(var, zero_temp, FJUMP_UNEQUAL, failure));
        if (codetype == 0)
            (this -> list).push_back(InterCode(GOTO, failure));
    }
    else if (condition -> msg == "Const Declaration")
    {
        VarPair const_temp;
        int const_value = atoi(condition -> name.c_str());
        int temp_index = this -> checkConst(const_value);
        if(temp_index == -1)
        {
            this -> addConst(const_value, temp_count);
            const_temp = VarPair(TEMP, temp_count++);
            VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
            (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, const_temp));
        }
        else
            const_temp = VarPair(TEMP, temp_index);
        VarPair zero_temp;
        temp_index = this -> checkConst(0);
        if(temp_index == -1)
        {
            this -> addConst(0, temp_count);
            zero_temp = VarPair(TEMP, temp_count++);
            VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, 0);
            (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, zero_temp));
        }
        else
            zero_temp = VarPair(TEMP, temp_index);
        if (codetype != 2)
            (this -> list).push_back(InterCode(const_temp, zero_temp, JUMP_UNEQUAL, success));
        else
            (this -> list).push_back(InterCode(const_temp, zero_temp, FJUMP_UNEQUAL, failure));
        if (codetype == 0)
            (this -> list).push_back(InterCode(GOTO, failure));
    }
    else
    {

    }
};

void InterCodeList::addConst(int value, int index)
{
    if(this -> constant_pool.count(value) != 0)
        printf("error: const value already existed.\n");
    else
        this->constant_pool[value] = index;
};

int InterCodeList::checkConst(int value)
{
    if(this -> constant_pool.count(value) != 0)
        return this -> constant_pool[value];
    else
        return -1;
};

void InterCodeList::read(ASTNode* root, Varlistnode* vlist, VarPair break_label, VarPair continue_label)
{
    if (root -> msg == "Translation Unit") {
        std::vector<ASTNode*>* temp = root -> getChildren();
        for (auto iter = (*temp).begin(); iter != (*temp).end(); iter ++)
        {
            this -> read(*iter, vlist, break_label, continue_label);
        }
    }
    else if (root -> msg == "Function Definition")
    {
        InterCode* temp = new InterCode();
        temp -> setOperator(FUNC_DEF);
        if ((*(root -> getChildren()))[1] -> msg == "Var Declaration")
        {
            temp -> setResult(VarPair(FUNC, (*(root -> getChildren()))[1] -> name));
            (this -> list).push_back(*temp);
            this -> read((*(root -> getChildren()))[2], vlist, break_label, continue_label);
            // not the final version
        }
        else if ((*(root -> getChildren()))[1] -> msg == "Function Declaration")
        {
            ASTNode* nodeptr = (*(root -> getChildren()))[1];
            temp -> setResult(VarPair(FUNC, (*(nodeptr -> getChildren()))[0] -> name));
            (this -> list).push_back(*temp);
            // this -> read((*(nodeptr -> getChildren()))[1], vlist);
            // to be completed
        }
    }
    else if (root -> msg == "Parameter Declaration List")
    {
        std::vector<ASTNode*>* temp = root -> getChildren();
        for (auto iter = (*temp).begin(); iter != (*temp).end(); iter ++)
        {
            // this -> read(*iter);
            // to be completed
        }
    }
    else if (root -> msg == "Parameter Declaration")
    {
        // to be completed
    }
    else if (root -> msg == "Compound Statement") 
    {
        Varlistnode* newlist = new Varlistnode(vlist);
        std::vector<ASTNode*>* temp = root -> getChildren();
        for (auto iter = (*temp).begin(); iter != (*temp).end(); iter ++)
        {
            this -> read(*iter, newlist, break_label, continue_label);
        }
    }
    else if (root -> msg == "Var Declaration") 
    {
        if ((*(root -> getChildren()))[0] -> name == "int")
        {
            std::vector<ASTNode*>* vars = (*(root -> getChildren()))[1] -> getChildren();
            for (auto iter = vars -> begin(); iter != vars -> end(); iter ++)
            {
                if ((*iter) -> msg == "Var Declaration")
                {
                    vlist -> addVar(VarPair(VAR, var_count++, (*iter) -> name));
                }
                else if ((*iter) -> msg == "Arr Declaration")
                {
                    VarPair arr = VarPair(ARR, arr_count++, (*iter) -> name);
                    vlist -> addVar(arr);
                    ASTNode* info = (*((*iter) -> getChildren()))[1];
                    VarPair size_temp;
                    int temp_index = this -> checkConst(INT_SIZE);
                    if (temp_index == -1)
                    {
                        VarPair size = VarPair(ARGTYPE::ARG_CONSTANT, INT_SIZE);
                        this -> addConst(INT_SIZE, temp_count);
                        size_temp = VarPair(TEMP, temp_count++);
                        (this -> list).push_back(InterCode(size, DOP_ASSIGNMENT, size_temp));
                    }
                    else
                        size_temp = VarPair(TEMP, temp_index);
                    int const_value = atoi((info -> name).c_str());
                    VarPair width_temp;
                    temp_index = this -> checkConst(const_value);
                    if (temp_index == -1)
                    {
                        VarPair width = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                        this -> addConst(const_value, temp_count);
                        width_temp = VarPair(TEMP, temp_count++);
                        (this -> list).push_back(InterCode(width, DOP_ASSIGNMENT, width_temp));
                    }
                    else
                        width_temp = VarPair(TEMP, temp_index);
                    VarPair space = VarPair(TEMP, temp_count++);
                    (this -> list).push_back(InterCode(width_temp, size_temp, DOP_MULTIPLY, space));
                    (this -> list).push_back(InterCode(space, ARRAY_DECLARATION, arr));
                }
                else if ((*iter) -> msg == "Initializer")
                {
                    ASTNode* var = (*((*iter) -> getChildren()))[0];
                    ASTNode* value = (*((*iter) -> getChildren()))[1];
                    if (var -> msg == "Var Declaration")
                    {
                        if (value -> msg == "Const Declaration")
                        {
                            int const_value = atoi(value -> name.c_str());
                            int temp_index = this -> checkConst(const_value);
                            VarPair temp;
                            if(temp_index == -1)
                            {
                                this -> addConst(const_value, temp_count);
                                temp = VarPair(TEMP, temp_count++);
                                VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                                (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, temp));
                            }
                            else
                                temp = VarPair(TEMP, temp_index);
                            VarPair variable = VarPair(VAR, var_count++, var -> name);
                            vlist -> addVar(variable);
                            (this -> list).push_back(InterCode(temp, DOP_ASSIGNMENT, variable));
                        }
                        else if (value -> msg == "ID Declaration")
                        {
                            VarPair id = vlist -> findVar(value -> name);
                            if (id.type == NULL_ARG)
                            {
                                printf("%s\n", (value -> name).c_str());
                                printf("error: var not defined.\n");
                                exit(-1);
                                // error: variable undefined
                            }
                            else
                            {
                                VarPair variable = VarPair(VAR, var_count++, (*iter) -> name);
                                vlist -> addVar(variable);
                                (this -> list).push_back(InterCode(id, DOP_ASSIGNMENT, variable));
                            }
                        }
                        else
                        {
                            VarPair temp_result = VarPair(TEMP, temp_count++);
                            this -> arithmetic(value, vlist, temp_result);
                            VarPair variable = VarPair(VAR, var_count++, var -> name);
                            vlist -> addVar(variable);
                            (this -> list).push_back(InterCode(temp_result, DOP_ASSIGNMENT, variable));
                            exit(-1);
                            // error: fatal assignment
                        }
                    }
                    else if(var -> msg == "Arr Declaration")
                    {

                        // to be completed
                    }
                }
            }
        }
        // else if( )           // to be completed
        // {

        // }
    }
    else if (root -> msg == "Assignment Expression")
    {
        ASTNode* left = (*(root -> getChildren()))[0];
        ASTNode* right = (*(root -> getChildren()))[1];
        if (left -> msg == "ID Declaration")
        {
            VarPair var = vlist -> findVar(left -> name);
            if (var.type == NULL_ARG)
            {
                printf("%s\n", left -> name.c_str());
                printf("error: variable undefined\n");
                exit(-1);
                // error: variable undefined
            }
            else if (var.type == ARR)
            {
                printf("\"%s\": Type \"ARR\"\n", left -> name.c_str());
                printf("error: can't be a left value\n");
                exit(-1);
                // error: can't be a left value
            }
            else if (right -> msg == "ID Declaration")
            {
                VarPair right_var = vlist -> findVar(right -> name);
                if (right_var.type == NULL_ARG)
                {
                    printf("%s\n", right -> name.c_str());
                    printf("error: variable undefined\n");
                    exit(-1);
                    // error: variable undefined
                }
                (this -> list).push_back(InterCode(right_var, DOP_ASSIGNMENT, var));
            }
            else if (right -> msg == "Const Declaration")
            {
                int const_value = atoi(right -> name.c_str());
                int temp_index = this -> checkConst(const_value);
                VarPair right_const;
                if(temp_index == -1)
                {
                    this -> addConst(const_value, temp_count);
                    right_const = VarPair(TEMP, temp_count++);
                    VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                    (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, right_const));
                }
                else
                    right_const = VarPair(TEMP, temp_index);
                (this -> list).push_back(InterCode(right_const, DOP_ASSIGNMENT, var));
            }
            else
            {
                VarPair right_value = VarPair(TEMP, temp_count++); 
                this -> arithmetic(right, vlist, right_value);
                (this -> list).push_back(InterCode(right_value, DOP_ASSIGNMENT, var));
            }
        }
        else if (left -> msg == "Expr")
        {
            // VarPair left_value = ;
            ASTNode* arrname = (*(left -> getChildren()))[0];
            ASTNode* targetidx = (*(left -> getChildren()))[1];
            VarPair arrpair;
            VarPair idxtemp;
            if (arrname -> msg == "ID Declaration")
            {
                arrpair = vlist -> findVar(arrname -> name);
                if (arrpair.type == NULL_ARG)
                {
                    printf("%s\n", arrname -> name.c_str());
                    printf("error: variable undefined\n");
                    exit(-1);
                    // error: variable undefined
                }
                else if (arrpair.type != ARR)
                {
                    printf("%s\n", arrname -> name.c_str());
                    printf("error: is not an array\n");
                }
                else
                {
                
                }
            }
            else
            {
                printf("not a correct type with \"[]\"\n");
                exit(-1);
                // error: not a correct type with "[]"
            }
            if (targetidx -> msg == "ID Declaration")
            {
                idxtemp = vlist -> findVar(targetidx -> name);
                if (idxtemp.type == NULL_ARG)
                {
                    printf("%s\n", targetidx -> name.c_str());
                    printf("error: variable undefined\n");
                    exit(-1);
                    // error: variable undefined
                }
                else
                {
                    
                }
            }
            else if (targetidx -> msg == "Const Declaration")
            {
                int const_value = atoi(targetidx -> name.c_str());
                int temp_index = this -> checkConst(const_value);
                if(temp_index == -1)
                {
                    this -> addConst(const_value, temp_count);
                    idxtemp = VarPair(TEMP, temp_count++);
                    VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                    (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, idxtemp));
                }
                else
                    idxtemp = VarPair(TEMP, temp_index);
            }
            else
            {
                idxtemp = VarPair(TEMP, temp_count++);
                this -> arithmetic(targetidx, vlist, idxtemp);
            }
            VarPair right_value;
            if (right -> msg == "ID Declaration")
            {
                right_value = vlist -> findVar(right -> name);
                if (right_value.type == NULL_ARG)
                {
                    printf("%s\n", right -> name.c_str());
                    printf("error: variable undefined\n");
                    exit(-1);
                    // error: variable undefined
                }
            }
            else if (right -> msg == "Const Declaration")
            {
                int const_value = atoi(right -> name.c_str());
                int temp_index = this -> checkConst(const_value);
                if(temp_index == -1)
                {
                    this -> addConst(const_value, temp_count);
                    right_value = VarPair(TEMP, temp_count++);
                    VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                    (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, right_value));
                }
                 else
                    right_value = VarPair(TEMP, temp_index);
            }
            else
            {
                right_value = VarPair(TEMP, temp_count++);
                this -> arithmetic(right, vlist, right_value);
            }
            int temp_index = this -> checkConst(INT_SIZE);
            VarPair width;
            if(temp_index == -1)
            {
                VarPair size = VarPair(ARGTYPE::ARG_CONSTANT, INT_SIZE);
                this -> addConst(INT_SIZE, temp_count);
                width = VarPair(TEMP, temp_count++);
                (this -> list).push_back(InterCode(size, DOP_ASSIGNMENT, width));
            }
            else
                width = VarPair(TEMP, temp_index);
            VarPair raddress = VarPair(TEMP, temp_count++);
            VarPair left_value = VarPair(TEMP, temp_count++);
            (this -> list).push_back(InterCode(idxtemp, width, DOP_MULTIPLY, raddress));
            (this -> list).push_back(InterCode(arrpair, raddress, DOP_GETVALUE, left_value));
            left_value.usage = CONTENT;
            if (right -> msg == "Expr")
                right_value.usage = CONTENT;
            (this -> list).push_back(InterCode(right_value, DOP_ASSIGNMENT, left_value));
        }
        else
        {
            printf("error:%s ", left -> name.c_str());
            printf("can't be a left value\n");
            exit(-1);
            // error: xxx can't be a left value
        }
        
    }
    else if (root -> msg == "Additive Expression" || root -> msg == "Multiplicative Expression" 
    || root -> msg == "Pow Expression" || root -> msg == "Logical OR Expression" 
    || root -> msg == "Logical AND Expression" || root -> msg == "Logical not expression" 
    || root -> msg == "Equality Expression" || root -> msg == "Relational Expression")
    {
        this -> fake_arithmetic(root, vlist);
    }
    else if (root -> msg == "Input Expression")
    {
        std::vector<ASTNode*>* children = root -> getChildren();
        // printf("1\n");
        for (auto iter = children -> begin(); iter != children -> end(); iter++)
        {
            if ((*iter) -> msg == "ID Declaration")
            {
                VarPair var = vlist -> findVar((*iter) -> name);
                if (var.type == NULL_ARG)
                {
                    printf("%s\n", (*iter) -> name.c_str());
                    printf("error: variable undefined\n");
                    exit(-1);
                    // error: variable undefined
                }
                else
                {
                    (this -> list).push_back(InterCode(OP_READ, var));
                }
            }
            else if ((*iter) -> msg == "Expr")
            {
                ASTNode* arrname = (*((*iter) -> getChildren()))[0];
                ASTNode* targetidx = (*((*iter) -> getChildren()))[1];
                VarPair arrpair;
                VarPair idxtemp;
                if (arrname -> msg == "ID Declaration")
                {
                    arrpair = vlist -> findVar(arrname -> name);
                    if (arrpair.type == NULL_ARG)
                    {
                        printf("%s\n", arrname -> name.c_str());
                        printf("error: variable undefined\n");
                        exit(-1);
                        // error: variable undefined
                    }
                    else if (arrpair.type != ARR)
                    {
                        printf("%s\n", arrname -> name.c_str());
                        printf("error: is not an array\n");
                        exit(-1);
                        // error: xxx is not an array
                    }
                    else
                    {
                    
                    }
                }
                else
                {
                    printf("not a correct type with \"[]\"\n");
                    exit(-1);
                    // error: not a correct type with "[]"
                }
                if (targetidx -> msg == "ID Declaration")
                {
                    idxtemp = vlist -> findVar(targetidx -> name);
                    if (idxtemp.type == NULL_ARG)
                    {
                        printf("%s\n", targetidx -> name.c_str());
                        printf("error: variable undefined\n");
                        exit(-1);
                        // error: variable undefined
                    }
                    else
                    {
                        
                    }
                }
                else if (targetidx -> msg == "Const Declaration")
                {
                    int const_value = atoi(targetidx -> name.c_str());
                    int temp_index = this -> checkConst(const_value);
                    if(temp_index == -1)
                    {
                        this -> addConst(const_value, temp_count);
                        idxtemp = VarPair(TEMP, temp_count++);
                        VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                        (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, idxtemp));
                    }
                    else
                        idxtemp = VarPair(TEMP, temp_index);
                }
                else
                {
                    idxtemp = VarPair(TEMP, temp_count++);
                    this -> arithmetic(targetidx, vlist, idxtemp);
                }
                int temp_index = this -> checkConst(INT_SIZE);
                VarPair width;
                if(temp_index == -1)
                {
                    VarPair size = VarPair(ARGTYPE::ARG_CONSTANT, INT_SIZE);
                    this -> addConst(INT_SIZE, temp_count);
                    width = VarPair(TEMP, temp_count++);
                    (this -> list).push_back(InterCode(size, DOP_ASSIGNMENT, width));
                }
                else
                    width = VarPair(TEMP, temp_index);
                VarPair raddress = VarPair(TEMP, temp_count++);
                VarPair left_value = VarPair(TEMP, temp_count++);
                (this -> list).push_back(InterCode(idxtemp, width, DOP_MULTIPLY, raddress));
                (this -> list).push_back(InterCode(arrpair, raddress, DOP_GETVALUE, left_value));
                left_value.usage = CONTENT;
                (this -> list).push_back(InterCode(OP_READ, left_value));
            }
            else
            {
                printf("error: not an expression that can be inputted.\n");
                exit(-1);
                // error: not an expression that can be inputted.
            }
        }
    }
    else if (root -> msg == "Output Expression")
    {
        std::vector<ASTNode*>* children = root -> getChildren();
        for (auto iter = children -> begin(); iter != children -> end(); iter++)
        {
            if ((*iter) -> msg == "ID Declaration")
            {
                VarPair var = vlist -> findVar((*iter) -> name);
                if (var.type == NULL_ARG)
                {
                    printf("%s\n", (*iter) -> name.c_str());
                    printf("error: variable undefined\n");
                    exit(-1);
                    // error: variable undefined
                }
                else
                {
                    (this -> list).push_back(InterCode(ARG, var));
                    (this -> list).push_back(InterCode(OP_PRINT));
                }
            }
            else if ((*iter) -> msg == "Const Declaration")
            {
                int const_value = atoi((*iter) -> name.c_str());
                int temp_index = this -> checkConst(const_value);
                VarPair const_output;
                if(temp_index == -1)
                {
                    this -> addConst(const_value, temp_count);
                    const_output = VarPair(TEMP, temp_count++);
                    VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                    (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, const_output));
                }
                else
                    const_output = VarPair(TEMP, temp_index);
                (this -> list).push_back(InterCode(ARG, const_output));
                (this -> list).push_back(InterCode(OP_PRINT));
            }
            else
            {
                VarPair outputer = VarPair(TEMP, temp_count++);
                this -> arithmetic(*iter, vlist, outputer); 
                if((*iter) -> msg == "Expr")
                    outputer.usage = CONTENT;
                (this -> list).push_back(InterCode(ARG, outputer));
                (this -> list).push_back(InterCode(OP_PRINT));
            }
        }
    }
    else if (root -> msg == "Jump Statement")
    {
        if(root -> name == "break")
        {
            if (break_label.type == LABEL)
                (this -> list).push_back(InterCode(GOTO, break_label));
            else
            {
                printf("error: 'break' cannot be used outside a loop\n");
                exit(-1);
                // error: 'break' cannot be used outside a loop
            }
        }
        else if (root -> name == "continue")
        {
            if (continue_label.type == LABEL)
                (this -> list).push_back(InterCode(GOTO, continue_label));
            else
            {
                printf("error: 'continue' cannot be used outside a loop\n");
                exit(-1);
                // error: 'continue' cannot be used outside a loop
            }
        }
        else if (root -> name == "return expr")
        {
            ASTNode* expression = (*(root -> getChildren()))[0];
            if (expression -> msg == "ID Declaration")
            {
                VarPair var = vlist -> findVar(expression -> name);
                if (var.type == NULL_ARG)
                {
                    printf("%s\n", expression -> name.c_str());
                    printf("error: variable undefined\n");
                    exit(-1);
                    // error: variable undefined
                }
                else
                {
                    (this -> list).push_back(InterCode(OP_RETURN, var));
                }
            }
            else if (expression -> msg == "Const Declaration")
            {
                int const_value = atoi(expression -> name.c_str());
                int temp_index = this -> checkConst(const_value);
                VarPair const_output;
                if(temp_index == -1)
                {
                    this -> addConst(const_value, temp_count);
                    const_output = VarPair(TEMP, temp_count++);
                    VarPair constant = VarPair(ARGTYPE::ARG_CONSTANT, const_value);
                    (this -> list).push_back(InterCode(constant, DOP_ASSIGNMENT, const_output));
                }
                else
                    const_output = VarPair(TEMP, temp_index);
                (this -> list).push_back(InterCode(OP_RETURN, const_output));
            }
            else
            {
                VarPair outputer = VarPair(TEMP, temp_count++);
                this -> arithmetic(expression, vlist, outputer); 
                if(expression -> msg == "Expr")
                    outputer.usage = CONTENT;
                (this -> list).push_back(InterCode(OP_RETURN, outputer));
            }
        }
        else
        {
            printf("Jump Statement: error: there shouldn't be other possibilities\n");
            exit(-1);
            // error: there shouldn't be other possibilities
        }
    }
    else if (root -> msg == "Repeat Statement")
    {
        if (root -> name == "while")
        {
            ASTNode* condition = (*(root -> getChildren()))[0];
            ASTNode* order = (*(root -> getChildren()))[1];
            VarPair loop_start = VarPair(LABEL, label_count++);
            VarPair loop_leave = VarPair(LABEL, label_count++);
            VarPair loop_continue = VarPair(LABEL, label_count++);
            (this -> list).push_back(InterCode(OP_LABEL, loop_start));
            this -> makeConditions(condition, loop_continue, loop_leave, 0, vlist);
            (this -> list).push_back(InterCode(OP_LABEL, loop_continue));
            this -> read(order, vlist, loop_leave, loop_start);
            (this -> list).push_back(InterCode(GOTO, loop_start));
            (this -> list).push_back(InterCode(OP_LABEL, loop_leave));
        }
        else if (root -> name == "for")
        {
            ASTNode* before_loop = (*(root -> getChildren()))[0];
            ASTNode* condition = (*(root -> getChildren()))[1];
            ASTNode* after_each_loop = (*(root -> getChildren()))[2];
            ASTNode* order = (*(root -> getChildren()))[3];
            this -> read(before_loop, vlist, break_label, continue_label);
            VarPair loop_start = VarPair(LABEL, label_count++);
            VarPair loop_leave = VarPair(LABEL, label_count++);
            VarPair loop_continue = VarPair(LABEL, label_count++);
            (this -> list).push_back(InterCode(OP_LABEL, loop_start));
            this -> makeConditions(condition, loop_continue, loop_leave, 0, vlist);
            (this -> list).push_back(InterCode(OP_LABEL, loop_continue));
            this -> read(order, vlist, loop_leave, loop_start);
            this -> read(after_each_loop, vlist, break_label, continue_label);
            (this -> list).push_back(InterCode(GOTO, loop_start));
            (this -> list).push_back(InterCode(OP_LABEL, loop_leave));
        }
        else
        {
            printf("Repeat Statement: there shouldn't be other possibilities.\n");
            exit(-1);
            // error: there shouldn't be other possibilities.
        }
    }
    else if (root -> msg == "Selection Statement")
    {
        std::vector<ASTNode*>* children = root -> getChildren();
        ASTNode* condition = (*children)[0];
        ASTNode* order = (*children)[1];
        if (children -> size() == 2)
        {
            VarPair success = VarPair(LABEL, label_count++);
            VarPair failure = VarPair(LABEL, label_count++);
            this -> makeConditions(condition, success, failure, 0, vlist);
            (this -> list).push_back(InterCode(OP_LABEL, success));
            this -> read(order, vlist, break_label, continue_label);
            (this -> list).push_back(InterCode(OP_LABEL, failure));
        }
        else if (children -> size() == 3)
        {
            ASTNode* order_if_failure = (*children)[2];
            VarPair success = VarPair(LABEL, label_count++);
            VarPair failure = VarPair(LABEL, label_count++);
            VarPair follow = VarPair(LABEL, label_count++);
            this -> makeConditions(condition, success, failure, 0, vlist);
            (this -> list).push_back(InterCode(OP_LABEL, success));
            this -> read(order, vlist, break_label, continue_label);
            (this -> list).push_back(InterCode(GOTO, follow));
            (this -> list).push_back(InterCode(OP_LABEL, failure));
            this -> read(order_if_failure, vlist, break_label, continue_label);
            (this -> list).push_back(InterCode(OP_LABEL, follow));
        }
        else
        {
            printf("Selection Statement: there shouldn't be other possibilities.\n");
            exit(-1);
            // error: there shouldn't be other possibilities.
        }
    }
    else if (root -> msg == "Empty Statement")
    {
        // do nothing
    }
    else if (root -> msg == "") {}
    // to be completed
};

void InterCodeList::label_recycle()
{
    bool* label_used = new bool[this -> label_count];
    for (int i = 0; i < this -> label_count; i++)
        label_used[i] = false;
    for (auto iter = (this -> list).begin(); iter != (this -> list).end(); iter++)
        if ((*iter).getResult().type == LABEL && (*iter).getOperator() != OP_LABEL)
        {
            int label_index = (*iter).getResult().index;
            label_used[label_index] = true;
        }
    for(int i = 0; i < this -> label_count; i++)
    {
        int recycle_count = 0;
        for (auto iter = (this -> list).begin(); iter != (this -> list).end();)
            if ((*iter).getOperator() == OP_LABEL && label_used[(*iter).getResult().index] == false)
            {
                iter = (this -> list).erase(iter);
                recycle_count++;
            }
            else if ((*iter).getOperator() == GOTO && iter != (this -> list).end() - 1 
            && (*(iter + 1)).getOperator() == OP_LABEL 
            && (*(iter + 1)).getResult().index == (*iter).getResult().index)
            {
                iter = (this -> list).erase(iter);
                recycle_count++;
            }
            else if ((*iter).getOperator() == GOTO && iter != (this -> list).begin() 
            && (*(iter - 1)).getOperator() == GOTO)
            {
                iter = (this -> list).erase(iter);
                recycle_count++;
            }
            else if ((*iter).getOperator() == OP_LABEL && iter != (this -> list).end() - 1 
            && (*(iter + 1)).getOperator() == OP_LABEL)
            {
                int index_this = (*iter).getResult().index;
                int index_next = (*(iter + 1)).getResult().index;
                for (auto iter1 = (this -> list).begin();  iter1 != (this -> list).end(); iter1++)
                    if ((*iter1).getOperator() == GOTO && (*iter1).getResult().index == index_this)
                        (*iter1).setResult(VarPair(LABEL, index_next));
                iter = (this -> list).erase(iter);
                recycle_count++;
            }
            else
                iter++;
        if (recycle_count == 0)
            break;
    }
};

// public
InterCodeList::InterCodeList()
{
    this -> root_list = new Varlistnode();
};

int InterCodeList::getListSize()
{
    return this -> list.size();
};

void InterCodeList::read(ASTNode* root)
{
    this -> read(root, this -> root_list, VarPair(), VarPair());
    this -> label_recycle();
};

void InterCodeList::printCodeList()
{
    printf("print intercode list:\n");
    for (auto iter = (this -> list).begin(); iter != (this -> list).end(); iter ++)
    {    
        printf("%s", (*iter).printCode().c_str());
    }
};
