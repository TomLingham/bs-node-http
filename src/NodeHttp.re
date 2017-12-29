type http;

type request;

module ServerResponse = {
  type t;
  [@bs.send] external end_ : t => unit = "end";
  [@bs.send] external setHeader : (t, string, string) => unit = "setHeader";
  [@bs.send] external write : (t, string) => unit = "write";
  [@bs.set] external setStatusCode : (t, int) => unit = "statusCode";
};

module Server = {
  type t;
  [@bs.send.pipe : t] external listen : (~port: int) => t = "";
};

[@bs.module "http"]
external create_server :
  ((~request: request, ~response: ServerResponse.t) => 'a) => Server.t =
  "createServer";