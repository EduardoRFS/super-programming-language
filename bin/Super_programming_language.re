let initial_env = Env.initial_env;

// let example =
//   Apply(
//     Identifier("log"),
//     Apply(
//       Apply(Identifier("+"), Literal(Float(5.2))),
//       Literal(Float(2.3)),
//     ),
//   );

// switch (Eval.eval(initial_env, example)) {
// | Ok(_) => ()
// | Error(error) => failwith(error)
// };

open Parser.Tokenizer;

let read_all = code => {
  let buf = Sedlexing.Utf8.from_string(code);
  let rec read = acc =>
    switch (tokenize(buf)) {
    | Ok(EOF) => acc |> List.rev
    | Error(error) => failwith("error " ++ error)
    | Ok(token) => read([token, ...acc])
    };
  let tokens = read([]);
  tokens |> List.map(Parser.Token.show) |> List.iter(print_endline);
};

read_all({|<log>"abc"</log>|});
