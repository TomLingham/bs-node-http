type http;

module ClientRequest: {
  type t;

  /**
   * Get the header value from the request. Equivalent to accessing properties
   * on `request.headers`.
   * 
   * https://nodejs.org/api/http.html#http_message_headers
   */
  [@bs.get_index] [@bs.scope ("headers")] external getHeader : (t, string) => string = "";

  /**
   * Get the method type of the request (e.g. POST, GET, PUT). Equivalent to
   * acceessing the `request.method` property.
   * 
   * https://nodejs.org/api/http.html#http_message_method
   */
  [@bs.get] external getMethod : (t) => string = "method";
};

module Server: {
  type t;

  /**
   * Start the server on the specified port and begin listening for incoming
   * HTTP requests.
   * 
   * https://nodejs.org/api/http.html#http_server_listen
   */
  [@bs.send.pipe : t] external listen : (~port: int) => t = "";
};

module ServerResponse: {
  type t;

  /**
   * End the response.
   * 
   * https://nodejs.org/api/http.html#http_response_end_data_encoding_callback
   */
  [@bs.send] external end_ : t => unit = "end";

  /**
   * Remove the header from the response.
   * 
   * https://nodejs.org/api/http.html#http_response_removeheader_name
   */
  let removeHeader: (string, t) => t;

  /**
   * Set the header to the specified value.
   * 
   * https://nodejs.org/api/http.html#http_response_setheader_name_value
   */
  let setHeader: (string, string, t) => t;

  /**
   * The equivalent of setting the `statusCode` property on the response
   * object.
   * 
   * https://nodejs.org/api/http.html#http_response_statuscode
   */
  let setStatusCode: (int, t) => t;

  /**
   * The equivalent of setting the `statusMessage` property on the response
   * object.
   * 
   * https://nodejs.org/api/http.html#http_response_statusmessage
   */
  let setStatusMessage: (string, t) => t;

  /**
   * Write a chunk to the response body. This method DOES NOT take a callback.
   * 
   * https://nodejs.org/api/http.html#http_response_write_chunk_encoding_callback
   */
  let write: (string, ~encoding: CharEncoding.t=?, t) => t;

  /**
   * Write a chunk to the response body. This method DOES take a callback.
   * 
   * https://nodejs.org/api/http.html#http_response_write_chunk_encoding_callback
   */
  let writeCallback:
    (string, ~encoding: CharEncoding.t=?, string => unit, t) => t;

  [@bs.send.pipe : Server.t] external on : ([@bs.string] [
    | `request((~request: ClientRequest.t, ~response: t) => unit)
    | `close(unit => unit)
  ]) => Server.t = "";
};

/**
 * Create a HTTP server and pass the handler for the request.
 * 
 * https://nodejs.org/api/http.html#http_http_createserver_requestlistener
 */
[@bs.module "http"]
external createServer :
  ((~request: ClientRequest.t, ~response: ServerResponse.t) => 'a) => Server.t =
  "createServer";