open Ast;
open Eval;

include Env;

let plus =
  fun
  | Literal(Integer(a)) =>
    Native(
      (
        fun
        | Literal(Integer(b)) => Ok(Literal(Integer(a + b)))
        | _ => failwith("something is not something")
      ),
    )
    |> Result.ok
  | _ => Error("something is not something");
let log = value => {
  Console.log(Eval.show_value(value));
  Ok(Void);
};
let initial_env = [("+", Native(plus)), ("log", Native(log))];
let initial_env = initial_env |> List.to_seq |> Env.of_seq;
