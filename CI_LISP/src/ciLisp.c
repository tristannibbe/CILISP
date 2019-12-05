#include "ciLisp.h"
#include "math.h"

void yyerror(char *s) {
    fprintf(stderr, "\nERROR: %s\n", s);
    // note stderr that normally defaults to stdout, but can be redirected: ./src 2> src.log
    // CLion will display stderr in a different color from stdin and stdout
}

char *numNames[] = {
        "Integer",
        "Double"
};


char *types[] = {
    "int",
    "double"
};
// Array of string values for operations.
// Must be in sync with funcs in the OPER_TYPE enum in order for resolveFunc to work.
char *funcNames[] = {
        "neg",
        "abs",
        "exp",
        "sqrt",
        "add",
        "sub",
        "mult",
        "div",
        "remainder",
        "log",
        "pow",
        "max",
        "min",
        "exp2",
        "cbrt",
        "hypot",
        "read",
        "rand",
        "print",
        "equal",
        "less",
        "greater",
        ""
};

OPER_TYPE resolveFunc(char *funcName)
{
    int i = 0;
    while (funcNames[i][0] != '\0')
    {
        if (strcmp(funcNames[i], funcName) == 0)
            return i;
        i++;
    }
    return CUSTOM_OPER;
}

NUM_TYPE resolveType(char *type){
    int i = 0;
    while (types[i][0] != '\0')
    {
        if (strcmp(types[i], type) == 0)
            return i;
        i++;
    }
    return UNDEFINED_TYPE;
}

// Called when an INT or DOUBLE token is encountered (see ciLisp.l and ciLisp.y).
// Creates an AST_NODE for the number.
// Sets the AST_NODE's type to number.
// Populates the value of the contained NUMBER_AST_NODE with the argument value.
// SEE: AST_NODE, NUM_AST_NODE, AST_NODE_TYPE.
AST_NODE *createNumberNode(double value, NUM_TYPE type)
{
    AST_NODE *node;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE);
    if ((node = calloc(nodeSize, 1)) == NULL)
        yyerror("Memory allocation failed!");

    node->type = NUM_NODE_TYPE;
    node->data.number.value = value;
    if(  round(value) == value){
        node->data.number.type = INT_TYPE;
    } else {
        node->data.number.type = DOUBLE_TYPE;
    }
    // TODO done set the AST_NODE's type, assign values to contained NUM_AST_NODE

    return node;
}

// Called when an f_expr is created (see ciLisp.y).
// Creates an AST_NODE for a function call.
// Sets the created AST_NODE's type to function.
// Populates the contained FUNC_AST_NODE with:
//      - An OPER_TYPE (the enum identifying the specific function being called)
//      - 2 AST_NODEs, the operands
// SEE: AST_NODE, FUNC_AST_NODE, AST_NODE_TYPE.
AST_NODE *createFunctionNode(char *funcName, AST_NODE *op1, AST_NODE *op2)
{
    AST_NODE *node;
    size_t nodeSize;

    // allocate space (or error)
    nodeSize = sizeof(AST_NODE);
    if ((node = calloc(nodeSize, 1)) == NULL)
        yyerror("Memory allocation failed!");

    node->type = FUNC_NODE_TYPE;
    node->data.function.op1 = op1;
    node->data.function.op2 = op2;
    if(op1 != NULL){
        op1->parent = node;
    }if(op2 != NULL){
        op2->parent = node;
    }
    node->data.function.oper = resolveFunc(funcName);
    if(node->data.function.oper == CUSTOM_OPER){
        node->data.function.ident  = funcName;
    } else{
        free(funcName);
    }


    // TODO done set the AST_NODE's type, populate contained FUNC_AST_NODE
    // NOTE: you do not need to populate the "ident" field unless the function is type CUSTOM_OPER.
    // When you do have a CUSTOM_OPER, you do NOT need to allocate and strcpy here.
    // The funcName will be a string identifier for which space should be allocated in the tokenizer.
    // For CUSTOM_OPER functions, you should simply assign the "ident" pointer to the passed in funcName.
    // For functions other than CUSTOM_OPER, you should free the funcName after you're assigned the OPER_TYPE.

    return node;
}

// Called after execution is done on the base of the tree.
// (see the program production in ciLisp.y)
// Recursively frees the whole abstract syntax tree.
// You'll need to update and expand freeNode as the project develops.
void freeNode(AST_NODE *node)
{
    if (!node)
        return;

    if (node->type == FUNC_NODE_TYPE)
    {
        // Recursive calls to free child nodes
        freeNode(node->data.function.op1);
        freeNode(node->data.function.op2);

        // Free up identifier string if necessary
        if (node->data.function.oper == CUSTOM_OPER)
        {
            free(node->data.function.ident);
        }
    }

    free(node);
}

// Evaluates an AST_NODE.
// returns a RET_VAL storing the the resulting value and type.
// You'll need to update and expand eval (and the more specific eval functions below)
// as the project develops.
RET_VAL eval(AST_NODE *node)
{
    if (!node)
        return (RET_VAL){INT_TYPE, NAN};

    RET_VAL result = {INT_TYPE, NAN}; // see NUM_AST_NODE, because RET_VAL is just an alternative name for it.

    // TODO complete the switch.
    // Make calls to other eval functions based on node type.
    // Use the results of those calls to populate result.
    switch (node->type)
    {
        case FUNC_NODE_TYPE:
            result = evalFuncNode(node);
            break;
        case NUM_NODE_TYPE:
            result = evalNumNode(node);
            break;
        case SYM_NODE_TYPE:
            result = evalSymbolNode(node,node->data.symbol.ident);
            break;
        default:
            yyerror("Invalid AST_NODE_TYPE, probably invalid writes somewhere!");
    }

    return result;
}  

// returns a pointer to the NUM_AST_NODE (aka RET_VAL) referenced by node.
// DOES NOT allocate space for a new RET_VAL.
RET_VAL evalNumNode(AST_NODE *node)
{
    if (!node)
        return (RET_VAL){INT_TYPE, NAN};

    RET_VAL result = {INT_TYPE, NAN};

    result.type = node->data.number.type;
    result.value = node->data.number.value;

    // TODO done populate result with the values stored in the node.
    // SEE: AST_NODE, AST_NODE_TYPE, NUM_AST_NODE


    return result;
}

void setNumType(RET_VAL num){
    if(ceil(num.value) == num.value)
        num.type = INT_TYPE;
    else
        num.type = DOUBLE_TYPE;
}

RET_VAL roundToINT(RET_VAL node){
    node.value = round(node.value);
    node.type = INT_TYPE;
    return  node;
}

RET_VAL evalSymbolNode(AST_NODE *node, char* ident){


    if(node->symbolTable != NULL) {
        SYMBOL_TABLE_NODE *current = node->symbolTable;
        if (strcmp(node->symbolTable->ident, ident) == 0) {
            if(eval(current->val).type == DOUBLE_TYPE && current->val_type == INT_TYPE){
                printf("WARNING: precision loss in the assignment for variable %s\n",ident);
                return roundToINT( eval(current->val) );
            }
            return eval(current->val);
        }

        while (current->next != NULL) {
            current = current->next;
            if (strcmp(current->ident, ident) == 0) {
                return eval(current->val);
            }
        }
    }
    if(node->parent != NULL){
        return evalSymbolNode(node->parent,ident);
    }else if (node->symbolTable == NULL){
        error("ERROR: NO SYMBOL TABLE DETECTED");
        return (RET_VAL){INT_TYPE, NAN};
    }else {
        error("ERROR: ENTRY NOT FOUND IN SYMBOL TABLE");
        return (RET_VAL) {INT_TYPE, NAN};
    }

}


RET_VAL evalFuncNode(AST_NODE *node)
{
    if (!node)
        return (RET_VAL){INT_TYPE, NAN};

    RET_VAL result = {INT_TYPE, NAN};
    RET_VAL temp1 = {INT_TYPE, NAN};
    RET_VAL temp2 = {INT_TYPE, NAN};


    switch(node->data.function.oper){
        case NEG_OPER:
            result.value = -eval(node->data.function.op1).value;
            setNumType(result);
            break;
        case ABS_OPER:
            result.value = fabs(eval(node->data.function.op1).value);
            setNumType(result);
            break;
        case SQRT_OPER:
            result.value = sqrt(eval(node->data.function.op1).value);
            result.type = DOUBLE_TYPE;
            break;
        case EXP_OPER:
            result.value = exp(eval(node->data.function.op1).value);
            result.type = DOUBLE_TYPE;
            break;
        case ADD_OPER:
            temp1 = eval(node->data.function.op1);
            temp2 = eval(node->data.function.op2);

            if(temp1.type == DOUBLE_TYPE || temp2.type == DOUBLE_TYPE){
                result.type = DOUBLE_TYPE;
            }
            result.value = temp1.value + temp2.value;
            break;
        case SUB_OPER:
            temp1 = eval(node->data.function.op1);
            temp2 = eval(node->data.function.op2);

            if(temp1.type == DOUBLE_TYPE || temp2.type == DOUBLE_TYPE){
                result.type = DOUBLE_TYPE;
            }
            result.value = temp1.value - temp2.value;
            break;
        case MAX_OPER:
            result.value = fmax(eval(node->data.function.op1).value,eval(node->data.function.op2).value);
            setNumType(result);
            break;
        case MIN_OPER:
            result.value = fmin(eval(node->data.function.op1).value,eval(node->data.function.op2).value);
            setNumType(result);
            break;
        case MULT_OPER:
            temp1 = eval(node->data.function.op1);
            temp2 = eval(node->data.function.op2);

            if(temp1.type == DOUBLE_TYPE || temp2.type == DOUBLE_TYPE){
                result.type = DOUBLE_TYPE;
            }
            result.value = temp1.value * temp2.value;
            break;
        case REMAINDER_OPER:
            result.value = fmod(eval(node->data.function.op1).value,eval(node->data.function.op2).value);
            result.type = DOUBLE_TYPE;
            break;
        case DIV_OPER:
            temp1 = eval(node->data.function.op1);
            temp2 = eval(node->data.function.op2);

            if(temp1.type == DOUBLE_TYPE || temp2.type == DOUBLE_TYPE){
                result.type = DOUBLE_TYPE;
            }
            result.value = temp1.value / temp2.value;
            break;
        case LOG_OPER:
            result.value = log(eval(node->data.function.op1).value);
            result.type = DOUBLE_TYPE;
            break;
        case POW_OPER:
            result.value = pow(eval(node->data.function.op1).value,eval(node->data.function.op2).value);
            setNumType(result);
            break;
        case EXP2_OPER:
            result.value = exp2(eval(node->data.function.op1).value);
            setNumType(result);
            break;
        case CBRT_OPER:
            result.value = cbrt(eval(node->data.function.op1).value);
            result.type = DOUBLE_TYPE;
            break;
        case HYPOT_OPER:
            result.value = hypot(eval(node->data.function.op1).value,eval(node->data.function.op2).value);
            setNumType(result);
            break;
        case READ_OPER:
            break;
        case RAND_OPER:
            break;
        case PRINT_OPER:
            result = eval(node->data.function.op1);
            break;
        case EQUAL_OPER:
            break;
        case LESS_OPER:
            break;
        case GREATER_OPER:
            break;
        case CUSTOM_OPER:
            break;

    }
    // TODO populate result with the result of running the function on its operands.
    // SEE: AST_NODE, AST_NODE_TYPE, FUNC_AST_NODE

    return result;
}

SYMBOL_TABLE_NODE* addToSymbolTable(SYMBOL_TABLE_NODE *table, SYMBOL_TABLE_NODE *toAdd){
	
  if (table != NULL)
  {
    if(table->next != NULL)
    {
      while(table->next != NULL)
      {
        table = table->next;
      }
      table->next = toAdd;
    }
    else
    {
      table->next = toAdd;
    }
  }  
  else
    error();
  return table;

}

void error(char* msg)
{
  printf("\n%s",msg);
  exit(0);
}

AST_NODE* createSymbolNode(char* ident){
    AST_NODE *node;
    size_t nodeSize;
    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE);
    if ((node = calloc(nodeSize, 1)) == NULL)
        yyerror("Memory allocation failed!");

    node->type = SYM_NODE_TYPE;
    node->data.symbol.ident = ident;
    return node;
}

SYMBOL_TABLE_NODE* createSymbolTableNode(char *ident,AST_NODE *value, char* type){
    SYMBOL_TABLE_NODE *node;
    size_t  nodeSize;
    nodeSize = sizeof(SYMBOL_TABLE_NODE);
    if ((node = calloc(nodeSize, 1)) == NULL)
        yyerror("Memory allocation failed!");

    node->ident = ident;
    node->val = value;
    node->val_type = resolveType(type);
    return node;
}

AST_NODE* setSymbolTable(SYMBOL_TABLE_NODE *table, AST_NODE *node){
    node->symbolTable = table;
    return node;
}

// prints the type and value of a RET_VAL
void printRetVal(RET_VAL val)
{
    if(val.type == DOUBLE_TYPE)
        printf("Type: %s Value: %.2f", numNames[val.type], val.value);
    else
        printf("Type: %s Value: %d", numNames[val.type], (int) val.value);
    // TODO done print the type and value of the value passed in.
}
