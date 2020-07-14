[@deriving show]
type identifier = string;

[@deriving show]
type literal =
  | String(string)
  | Float(float);

[@deriving show]
type expression =
  | Literal(literal)
  | Identifier(identifier)
  | Apply(expression, expression)
  | Function(identifier, expression)
  | Binding((identifier, expression), expression);
