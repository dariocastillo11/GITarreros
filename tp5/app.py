import os
import socket
from flask import Flask, render_template, jsonify, request

app = Flask(__name__)

SIM_MODE = os.environ.get('SIM_DEVICE') == '1'
active_channel = 1

def talk_to_simulator(cmd):
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.settimeout(1.0)
            s.connect(('127.0.0.1', 60000))
            s.sendall(f"{cmd}\n".encode())
            resp = s.recv(4096).decode().strip()
            return resp
    except Exception as e:
        return f"ERROR: {e}"

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/cambiar')
def cambiar():
    global active_channel
    canal = request.args.get('c', '1') # '1' or '2'
    try:
        if SIM_MODE:
            sim_canal = '0' if canal == '1' else '1'
            res = talk_to_simulator(f"WRITE:{sim_canal}")
            if res.startswith("ERROR"):
                return jsonify({"status": "error", "reason": res}), 500
            active_channel = int(canal)
        else:
            with open("/dev/mis_senales", "w") as f:
                f.write(canal)
        return jsonify({"status": "ok"})
    except Exception as e:
        return jsonify({"status": "error", "reason": str(e)}), 500

@app.route('/data')
def data():
    try:
        if SIM_MODE:
            raw_data = talk_to_simulator("READ")
            if raw_data and not raw_data.startswith("ERROR"):
                samples = [s for s in raw_data.replace("\n", "").split(";") if s]
                if samples:
                    last_sample = samples[-1]
                    str_tiempo, str_valor = last_sample.split(",")
                    tipo = "senoidal" if active_channel == 1 else "cuadrada"
                    return jsonify({
                        "status": "ok",
                        "canal": active_channel,
                        "tiempo": int(str_tiempo),
                        "valor": float(str_valor),
                        "raw": float(str_valor),
                        "tipo": tipo,
                        "unidad": "V"
                    })
            return jsonify({"status": "error", "reason": "No se obtuvieron datos del simulador"}), 500
        else:
            with open("/dev/mis_senales", "r") as f:
                raw_data = f.read().strip()
            
            parts = raw_data.split()
            if len(parts) == 3:
                sig = int(parts[0])      # 1 or 2
                tiempo = int(parts[1])   # timestamp
                raw_val = int(parts[2])  # 0..1000
                
                if sig == 2:
                    valor = raw_val * 3.3 / 1000.0
                    tipo = "cuadrada"
                else:
                    valor = raw_val * 5.0 / 1000.0
                    tipo = "senoidal"
                
                return jsonify({
                    "status": "ok",
                    "canal": sig,
                    "tiempo": tiempo,
                    "valor": valor,
                    "raw": raw_val,
                    "tipo": tipo,
                    "unidad": "V"
                })
            return jsonify({"status": "error", "reason": f"Formato inválido del driver: {raw_data}"}), 500
    except Exception as e:
        return jsonify({"status": "error", "reason": str(e)}), 500

if __name__ == '__main__':
    port = int(os.environ.get('PORT', 5000))
    app.run(host='0.0.0.0', port=port, debug=False)