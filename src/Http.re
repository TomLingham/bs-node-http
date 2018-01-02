module Response = {
  open NodeHttp;
  type t = ServerResponse.t;
  let close = ServerResponse.end_;
  let write = (chunk: string, ~encoding=Encoding.Utf8, response: t) : t => {
    ServerResponse.write(
      response,
      chunk,
      Encoding.string_of_encoding(encoding)
    );
    response;
  };
  let setHeader = (header: string, value: string, response: t) : t => {
    ServerResponse.setHeader(response, header, value);
    response;
  };
  let setStatusCode = (code: int, response: t) : t => {
    ServerResponse.setStatusCode(response, code);
    response;
  };
};

module Server = {
  open NodeHttp;
  let listen = Server.listen;
  [@bs.send.pipe : Server.t] external on : ([@bs.string] [
    | `request(
        (~request: ClientRequest.t, ~response: ServerResponse.t) => unit
      )
    | `close(unit => unit)
  ]) => Server.t = "";
};

let create_server = NodeHttp.create_server;