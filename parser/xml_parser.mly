%{

open Ast

%}
%token <float> NUMBER
%token <string> STRING
%token <string> IDENTIFIER
%token <string> PARAMETER
%token OPEN_TAG
%token CLOSE_TAG
%token GREATER_THAN
%token WHITESPACE
%token EOF

%start <Ast.expression option> expression_value
%%

let primitive :=
  | s = STRING; { Literal (String s) }
  | n = NUMBER; { Literal (Float n) }
  | i = IDENTIFIER; { Identifier i }

let expression :=
  | primitive
  | OPEN_TAG; name = IDENTIFIER; WHITESPACE?; GREATER_THAN;
    args = separated_list(WHITESPACE, expression);
    CLOSE_TAG; close_name = IDENTIFIER; WHITESPACE?; GREATER_THAN; {
      if name <> close_name then failwith "grr " else ();
      let (first_arg,remaining) =
        match args with
        | first_arg::remaining -> (first_arg, remaining)
        | [] -> (Void, []) in
      List.fold_left
        (fun node -> fun arg -> Apply (node, arg))
        (Apply (Identifier name, first_arg))
        remaining
    }

let expression_value :=
  | EOF; { None }
  | expr = expression; { Some expr }
