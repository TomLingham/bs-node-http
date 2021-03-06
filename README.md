# bs-node-http

[![npm](https://img.shields.io/npm/v/bs-node-http.svg)](https://www.npmjs.com/package/bs-node-http)
[![npm](https://img.shields.io/npm/dw/bs-node-http.svg)](https://www.npmjs.com/package/bs-node-http)

Node [`http`](https://nodejs.org/api/http.html) bindings for
[Bucklescript](https://github.com/BuckleScript/bucklescript) in
[Reason](https://github.com/facebook/reason)

## Status
Obligatory "this is just a WIP" section. Feel free to pull down and extend
the API and/or make it better ... I don't pretend to be a ReasonML wizard.

I will be accepting PR's. Node HTTP is one of my most used modules and I'm
surprised this wasn't done yet. A good alternative, though, is the
[bs-express](https://github.com/reasonml-community/bs-express) project if
you are after routing as well.

## Installation

Install `bs-node-http` from npm. `npm i -S bs-node-http`.

Then, add `bs-node-http` to yor `bs-dependencies` in your `bsconfig.json`.

```json
{
  "bs-dependencies": ["bs-node-http"]
}
```

## Usage

The api is modified to favour piping the response so doesn't map 1 to 1 with
the Node API. It's very minimal at the moment - if what you want isn't added
feel free to submit an issue or a PR. 

```reason
open Http;

let server =
  createServer((~request, ~response) => {
    switch (ClientRequest.getMethod(request)) {
    | `GET => print_string("GET money, GET paid")
    | `POST => print_string("POSTman Pat")
    | `PUT => print_string("PUTting the tee-pee in HTTP")
    | _ => print_string("We don't accept other methods...")
    };

    ServerResponse.(
      response
      |> setStatusCode(418)
      |> setHeader("x-reason", "reason-ml")
      |> write("Hello, world! I am a teapot!")
      |> write("UmVhc29uTUwgaXMgcHJldHR5IGdyZWF0IQ==", ~encoding=`base64)
      |> end_
    )
  });

Server.(
  server
  |> listen(~port=3000)
);
```
