open Parser;
open Ast;

module Env = Map.Make(String);

[@deriving show]
type value =
  | Void
  | String(string)
  | Float(float)
  | Boolean(bool)
  | Function(identifier, expression)
  | Native(value => result(value, string));

let (let.ok) = Result.bind;

let rec eval = (env: Env.t(value), expr) =>
  switch (expr) {
  | Ast.Literal(String(string)) => Ok(String(string))
  | Literal(Float(float)) => Ok(Float(float))
  | Identifier(identifier) =>
    Env.find_opt(identifier, env)
    |> Option.to_result(~none="identifier not found")
  | Apply(fn, argument) =>
    let.ok fn_value = eval(env, fn);
    let.ok argument = eval(env, argument);
    switch (fn_value) {
    | Native(fn) => fn(argument)
    | Function(parameter, body) =>
      let env = Env.add(parameter, argument, env);
      eval(env, body);
    | value => Error(show_value(value) ++ " is not a function")
    };
  | Function(parameters, body) => Ok(Function(parameters, body))
  | Binding((identifier, value), return_value) =>
    // TODO: recursive values
    let.ok value = eval(env, value);
    let env = Env.add(identifier, value, env);
    eval(env, return_value);
  };
