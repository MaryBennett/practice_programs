from datetime import datetime
import argparse
import cgi
from http.server import HTTPServer, BaseHTTPRequestHandler


class S(BaseHTTPRequestHandler):
    def _set_headers(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()

    def _html(self, message):
        """This just generates an HTML document that includes `message`
        in the body. Override, or re-write this do do more interesting stuff.
        """
        content = f"<html><body><h1>{message}</h1></body></html>"
        return content.encode("utf8")  # NOTE: must return a bytes object!

    def do_GET(self):
        self._set_headers()
        self.wfile.write(self._html("hi!"))

    def do_HEAD(self):
        self._set_headers()

    def do_POST(self):
        # Doesn't do anything with posted data
        form = cgi.FieldStorage(
            fp=self.rfile,
            headers=self.headers,
            environ={'REQUEST_METHOD':'POST',
                     'CONTENT_TYPE':self.headers['Content-Type'],
                     })

        # Begin the response
        self._set_headers()
        self.wfile.write(self._html("POST!"))

        # Echo back information about what was posted in the form
        temp = None
        humid = None
        for field in form.keys():
            if field.lower() == "temperature":
                temp = form[field].value
            elif field.lower() == "humidity":
                humid = form[field].value
        if temp is None:
            print("Temperature was not defined")
            temp = 0.0
        if humid is None:
            print("Humidity was not defined")
            humid = 0.0
        with open("dummy.csv", "a") as handle:
            handle.write("{0}, {1}, {2}\n".format(datetime.now(),
                                                  temp,
                                                  humid))


def run(server_class=HTTPServer, handler_class=S, addr="localhost", port=8000):
    server_address = (addr, port)
    httpd = server_class(server_address, handler_class)

    print(f"Starting httpd server on {addr}:{port}")
    httpd.serve_forever()


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description="Run a simple HTTP server")
    parser.add_argument(
        "-l",
        "--listen",
        default="localhost",
        help="Specify the IP address on which the server listens",
    )
    parser.add_argument(
        "-p",
        "--port",
        type=int,
        default=8000,
        help="Specify the port on which the server listens",
    )
    with open("dummy.csv", "w") as handle:
        handle.write("Time, Temperature, Humidity\n")
    args = parser.parse_args()
    run(addr=args.listen, port=args.port)
