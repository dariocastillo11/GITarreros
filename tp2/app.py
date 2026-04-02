import ctypes
import os

# 1. Cargar la librería que acabamos de crear
lib_path = os.path.abspath("./libcalculo.so")
lib = ctypes.CDLL(lib_path)

# 2. Configurar los tipos de datos (importante para que no explote)
# Le decimos que procesar_indice recibe un 'long' y devuelve un 'long'
lib.procesar_indice.argtypes = (ctypes.c_long,)
lib.procesar_indice.restype = ctypes.c_long

# 3. Probar la conexión
numero_entrada = 42
print(f"[Python] Enviando {numero_entrada} a la capa C...")

resultado = lib.procesar_indice(numero_entrada)

print(f"[Python] El resultado final es: {resultado}")