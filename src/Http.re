module Response = {
  open NodeHttp;
  type t = ServerResponse.t;
  let close = ServerResponse.end_;
  let write = (str: string, res: t) : t => {
    ServerResponse.write(res, str);
    res;
  };
  let setHeader = (header: string, value: string, res: t) : t => {
    ServerResponse.setHeader(res, header, value);
    res;
  };
  let setStatusCode = (code: int, res: t) : t => {
    ServerResponse.setStatusCode(res, code);
    res;
  };
};

module Server = {
  open NodeHttp;
  let listen = Server.listen;
};

let create_server = NodeHttp.create_server;