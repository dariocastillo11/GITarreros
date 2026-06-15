import http.server
import socketserver
import os

PORT = 5000

class CustomHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        # Ruta para darle los datos del driver al HTML
        if self.path == '/data':
            self.send_response(200)
            self.send_header('Content-type', 'text/plain')
            self.end_headers()
            try:
                with open("/dev/mis_senales", "r") as f:
                    data = f.read()
                self.wfile.write(data.encode())
            except Exception as e:
                self.wfile.write(b"0,0;")
                
        # Ruta para cambiar el canal del driver
        elif self.path.startswith('/cambiar'):
            self.send_response(200)
            self.end_headers()
            try:
                canal = self.path.split('=')[1]
                with open("/dev/mis_senales", "w") as f:
                    f.write(canal)
            except:
                pass
        else:
            # Si pide cualquier otra cosa, le da el index.html
            return http.server.SimpleHTTPRequestHandler.do_GET(self)

with socketserver.TCPServer(("", PORT), CustomHandler) as httpd:
    print(f"Servidor Nativo corriendo en el puerto {PORT} (¡Sin Flask!)")
    httpd.serve_forever()