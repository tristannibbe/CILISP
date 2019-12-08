
%{
    #include "ciLisp.h"
%}

%union {
    double dval;
    char *sval;
    struct ast_node *astNode;
    struct symbol_table_node *symTableNode;
};

%token <sval> FUNC SYMBOL TYPE
%token <dval> INT DOUBLE
%token LPAREN RPAREN EOL QUIT LET

%type <astNode> s_expr f_expr number s_expr_list
%type <symTableNode> let_elem let_list let_section

%%

program:
    s_expr EOL {
        fprintf(stderr, "yacc: program ::= s_expr EOL\n");
        if ($1) {
            printRetVal(eval($1));
            freeNode($1);
        }
    };

s_expr:
    number {
        fprintf(stderr, "yacc: s_expr ::= number\n");
        $$ = $1;
    }
    | SYMBOL{
         fprintf(stderr, "yacc: s_expr ::= symbol\n");
         $$ = createSymbolNode($1);
         }
    | f_expr {
        $$ = $1;
    }
    | QUIT {
        fprintf(stderr, "yacc: s_expr ::= QUIT\n");
        exit(EXIT_SUCCESS);
    }
    | LPAREN let_section s_expr RPAREN{
    	fprintf(stderr, "yacc: s_expr ::= let section\n");
    	$$ = setSymbolTable($2,$3);
    }
    | error {
        fprintf(stderr, "yacc: s_expr ::= error\n");
        yyerror("unexpected token");
        $$ = NULL;
    };

let_section:
	LPAREN LET let_list RPAREN{
	$$ = $3;
	}

let_list:
	let_elem
	| let_list let_elem{
		$$ = addToSymbolTable($1,$2);
	}

let_elem: LPAREN TYPE SYMBOL s_expr RPAREN{
		$$ = createSymbolTableNode($3,$4,$2);
	}
	|LPAREN SYMBOL s_expr RPAREN{
		$$ =  createSymbolTableNode($2,$3, "");
}

number:
    INT {
        fprintf(stderr, "yacc: number ::= INT\n");
        $$ = createNumberNode($1, INT_TYPE);
    }
    | DOUBLE {
        fprintf(stderr, "yacc: number ::= DOUBLE\n");
        $$ = createNumberNode($1, DOUBLE_TYPE);
    };

f_expr:
    LPAREN FUNC s_expr RPAREN {
        fprintf(stderr, "yacc: s_expr ::= LPAREN FUNC expr RPAREN\n");
       $$ = createFunctionNode($2,$3);
    }|LPAREN FUNC s_expr_list RPAREN {
              fprintf(stderr, "yacc: s_expr ::= LPAREN FUNC expr RPAREN\n");
              $$ = createFunctionNode($2,$3);
          }
s_expr_list:
	s_expr{
		$$ = $1;
	}
	|s_expr s_expr_list{
		$$ = setNextValue($1,$2);
		$$ = $1;
	}
%%

