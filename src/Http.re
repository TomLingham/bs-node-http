type http;

module ClientRequest = {
  type t;

  [@bs.get_index] [@bs.scope ("headers")] external getHeader : (t, string) => string = "";
  [@bs.get] external getMethod : (t) => string = "method";
};

module Server = {
  type t;
  [@bs.send.pipe : t] external listen : (~port: int) => t = "";
};

module ServerResponse = {
  type t;

  /**
   * Bind the external node API calls here so that we have the bindings
   * available. Mapping to the interface we want happens below.
   */
  [@bs.send] external removeHeader : (t, string) => unit = "";
  [@bs.send] external setHeader : (t, string, string) => unit = "";
  [@bs.send] external write : (t, string, CharEncoding.abs_t) => unit = "";
  [@bs.send] external writeCallback : (t, string, CharEncoding.abs_t, string => unit) => unit = "write";
  [@bs.set] external setStatusCode : (t, int) => unit = "statusCode";
  [@bs.set] external setStatusMessage : (t, string) => unit = "statusMessage";

  /**
   * Actual interface implementation will happen below here.
   */
  [@bs.send] external end_ : t => unit = "end";

  let removeHeader = (header: string, response: t) => {
    removeHeader(response, header);
    response;
  };

  let setHeader = (header: string, value: string, response: t) => {
    setHeader(response, header, value);
    response;
  };

  let write = (chunk: string, ~encoding: option(CharEncoding.t)=?, response: t) => {
    let en = switch encoding {
    | Some(e) => e
    | None => `utf8
    };

    write(
      response,
      chunk,
      CharEncoding.tToJs(en)
    );
    response;
  };

  let writeCallback = (chunk: string, ~encoding: option(CharEncoding.t)=?, callback, response: t) => {
    let en = switch encoding {
    | Some(e) => e
    | None => `utf8
    };

    writeCallback(
      response,
      chunk,
      CharEncoding.tToJs(en),
      callback
    );
    response;
  };

  let setStatusCode = (statusCode: int, response: t) => {
    setStatusCode(response, statusCode);
    response;
  };

  let setStatusMessage = (statusMessage: string, response: t) => {
    setStatusMessage(response, statusMessage);
    response;
  };

  [@bs.send.pipe : Server.t] external on : ([@bs.string] [
    | `request((~request: ClientRequest.t, ~response: t) => unit)
    | `close(unit => unit)
  ]) => Server.t = "";
};

[@bs.module "http"]
external createServer :
  ((~request: ClientRequest.t, ~response: ServerResponse.t) => 'a) => Server.t =
  "createServer";