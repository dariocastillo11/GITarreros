import http.server
import socketserver
import os

PORT = 5000
DEVICE = "/dev/mis_senales"

HTML = """<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <title>Monitor de Señales</title>
  <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
  <style>
    body { font-family: Arial, sans-serif; background: #f4f4f9;
           display: flex; flex-direction: column; align-items: center; padding: 30px; }
    h2   { color: #333; }
    button { padding: 10px 24px; margin: 6px; font-size: 15px; cursor: pointer;
             border: none; border-radius: 6px; background: #007bff; color: #fff; }
    button.active { background: #28a745; }
    canvas { max-width: 800px; width: 100%; margin-top: 20px; }
  </style>
</head>
<body>
  <h2>Monitor de Señales — Kernel Driver</h2>
  <div>
    <button id="b0" class="active" onclick="cambiar(0)">Señal 1 — Cuadrada</button>
    <button id="b1"               onclick="cambiar(1)">Señal 2 — Diente de sierra</button>
  </div>
  <canvas id="chart"></canvas>

  <script>
    const ctx   = document.getElementById('chart').getContext('2d');
    const chart = new Chart(ctx, {
      type: 'line',
      data: {
        labels: [],
        datasets: [{
          label: 'Valor',
          data: [],
          borderColor: '#007bff',
          backgroundColor: 'rgba(0,123,255,0.08)',
          tension: 0.3,
          fill: true,
          pointRadius: 4
        }]
      },
      options: {
        animation: false,
        scales: {
          x: { title: { display: true, text: 'Tiempo (s)' } },
          y: { min: -1, max: 11, title: { display: true, text: 'Valor' } }
        }
      }
    });

    // Mantiene un historial de los últimos 30 puntos
    const MAX = 30;
    const tiempos = [];
    const valores = [];

    function cambiar(canal) {
      fetch('/cambiar?canal=' + canal);
      document.getElementById('b0').className = canal === 0 ? 'active' : '';
      document.getElementById('b1').className = canal === 1 ? 'active' : '';
      chart.data.datasets[0].borderColor = canal === 0 ? '#007bff' : '#28a745';
    }

    async function actualizar() {
      try {
        const res  = await fetch('/data');
        const text = await res.text();
        text.split(';').filter(p => p.includes(',')).forEach(p => {
          const [t, v] = p.split(',');
          tiempos.push(t);
          valores.push(parseInt(v));
          if (tiempos.length > MAX) { tiempos.shift(); valores.shift(); }
        });
        chart.data.labels          = tiempos;
        chart.data.datasets[0].data = valores;
        chart.update();
      } catch (e) { console.error(e); }
    }

    setInterval(actualizar, 1000);
  </script>
</body>
</html>"""

class Handler(http.server.SimpleHTTPRequestHandler):
    def log_message(self, *args): pass   # silencia el log por defecto

    def do_GET(self):
        if self.path == '/':
            self._reply(200, 'text/html; charset=utf-8', HTML.encode())

        elif self.path == '/data':
            try:
                with open(DEVICE, 'r') as f:
                    data = f.read()
            except Exception:
                data = "0,0;"
            self._reply(200, 'text/plain', data.encode())

        elif self.path.startswith('/cambiar'):
            try:
                canal = self.path.split('=')[1]
                with open(DEVICE, 'w') as f:
                    f.write(canal)
            except Exception:
                pass
            self._reply(200, 'text/plain', b'ok')

        else:
            self.send_response(404)
            self.end_headers()

    def _reply(self, code, ctype, body):
        self.send_response(code)
        self.send_header('Content-Type', ctype)
        self.send_header('Content-Length', str(len(body)))
        self.end_headers()
        self.wfile.write(body)

with socketserver.TCPServer(('', PORT), Handler) as httpd:
    print(f'Servidor corriendo en el puerto {PORT}')
    httpd.serve_forever()