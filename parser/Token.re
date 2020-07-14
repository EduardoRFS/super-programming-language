[@deriving show]
type t =
  | NUMBER(float)
  | STRING(string)
  | IDENTIFIER(string)
  | PARAMETER(string)
  | OPEN_TAG
  | CLOSE_TAG
  | GREATER_THAN
  | WHITESPACE
  | EOF;

type token = t;
