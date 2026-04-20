import ctypes
import os
import requests

# 1. Configurar la Librería C (Igual que antes)
lib_path = os.path.abspath("./libcalculo.so")
lib = ctypes.CDLL(lib_path)
lib.procesar_indice.argtypes = (ctypes.c_double,)
lib.procesar_indice.restype = ctypes.c_long

def obtener_gini_argentina():
    # URL oficial del Banco Mundial para Argentina (GINI 2011-2020)
    url = "https://api.worldbank.org/v2/en/country/AR/indicator/SI.POV.GINI?format=json&date=2011:2020"
    
    print(f"[Python] Consultando API del Banco Mundial...")
    response = requests.get(url)
    
    if response.status_code == 200:
        data = response.json()
        # El JSON del Banco Mundial tiene los datos en la posición [1]
        # Buscamos el primer valor que no sea None (el más reciente)
        for registro in data[1]:
            if registro['value'] is not None:
                valor_gini = registro['value']
                anio = registro['date']
                print(f"[Python] Dato encontrado: GINI Argentina ({anio}) = {valor_gini}")
                return valor_gini
    else:
        print("[Python] Error al consultar la API")
        return None

# --- EJECUCIÓN ---
valor_real = obtener_gini_argentina()

if valor_real:

    print(f"[Python] Enviando float {valor_real} a la capa C...")
    resultado = lib.procesar_indice(valor_real)
    print(f"[Python] Resultado final (GINI convertido a int + 1): {resultado}")