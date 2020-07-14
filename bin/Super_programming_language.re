let initial_env = Env.initial_env;

open Ast;

let example =
  Apply(
    Identifier("log"),
    Apply(
      Apply(Identifier("+"), Literal(Integer(5))),
      Literal(Integer(2)),
    ),
  );

switch (Eval.eval(initial_env, example)) {
| Ok(_) => ()
| Error(error) => failwith(error)
};
