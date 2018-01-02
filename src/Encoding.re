type char_encoding =
  | Ascii
  | Base64
  | Binary
  | Hex
  | Latin1
  | Ucs2
  | Utf16le
  | Utf8;

let string_of_encoding = (e: char_encoding) => {
  switch e {
    | Ascii => "ascii"
    | Base64 => "base64"
    | Binary => "binary"
    | Hex => "hex"
    | Latin1 => "latin1"
    | Ucs2 => "ucs2"
    | Utf16le => "utf16le"
    | Utf8 => "utf8"
  };
}
