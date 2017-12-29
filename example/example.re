open Http;

let handler = (~request as _, ~response) =>
  response
  |> Response.setStatusCode(200)
  |> Response.setHeader("X-some-fancy-header", "hederz 4 dayz")
  |> Response.write("Foo")
  |> Response.write("Bar")
  |> Response.close;

let server = create_server(handler) |> Server.listen(~port=3000);