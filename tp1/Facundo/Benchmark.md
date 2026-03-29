# 🚀 Benchmarking y Rendimiento de Sistemas

El **benchmarking** es el proceso mediante el cual determinamos el rendimiento real de un equipo informático. Estas pruebas se realizan sobre diversos aspectos del hardware (RAM, CPU, GPU) con el fin de medir su capacidad bajo distintas tareas de carga.

### 💡 ¿Para qué sirve en la práctica?
* **Optimización de Presupuesto:** Permite configurar una computadora basada en las tareas que realizamos habitualmente, centrando la inversión en los componentes que más impacto tienen (por ejemplo, más GPU para gaming o más RAM para edición de video).
* **Fuentes de Información:** Los usuarios pueden consultar listados de resultados globales para conocer los valores de rendimiento de ciertos componentes sin necesidad de realizar las pruebas por sí mismos.

---

## 🛠️ Herramientas de Benchmark Populares

A continuación, se describen los programas más utilizados para evaluar el hardware:

| Programa | Tipo de Test | Descripción |
| :--- | :--- | :--- |
| **Timed Linux Kernel Compilation** | **CPU / Stress** | Mide el tiempo que tarda el equipo en compilar el núcleo de Linux. Es una prueba excelente para medir potencia bruta y multitarea. |
| **Cinebench (Maxon)** | **CPU (Render)** | Evalúa la capacidad del procesador mediante el renderizado de una imagen 3D compleja. Es el estándar para diseño y arquitectura. |
| **3D Mark** | **GPU (Gaming)** | Simula entornos de videojuegos de alta exigencia técnica para medir los FPS y la potencia de la tarjeta gráfica. |
| **AMD Adrenalin** | **Monitor / Driver** | Software oficial de AMD que, además de gestionar drivers, incluye herramientas para medir el rendimiento y FPS en tiempo real. |
| **Geekbench** | **CPU / Multiplataforma** | Realiza pruebas que simulan tareas cotidianas (comprimir archivos, procesar fotos) para dar un puntaje de rendimiento single-core y multi-core. |
| **CrystalDiskMark** | **Almacenamiento** | Mide la velocidad de lectura y escritura (MB/s) de discos rígidos y unidades SSD/NVMe. |
| **OCCT** | **Estabilidad / Calor** | Estresa los componentes al 100% para verificar que el equipo no falle por altas temperaturas o falta de energía. |
| **HWiNFO64** | **Diagnóstico** | Proporciona información detallada sobre todos los sensores del equipo (temperatura, voltajes y frecuencias) en tiempo real. |

---



# ⚔️ Comparativa de Rendimiento: Intel vs. AMD

Para poner en perspectiva los conceptos de benchmarking, analizamos el enfrentamiento entre dos referentes del mercado: el **Intel Core i5-13600K** y el **AMD Ryzen 9 5900X**.

### 💻 Especificaciones Base (Intel Core i5-13600K)
* **Núcleos/Hilos:** 14 núcleos (6P + 8E) / 20 hilos.
* **Frecuencia Máxima:** 5.1 GHz.
* **Arquitectura:** Híbrida de 13ª Generación.

---

## ⏱️ Caso 1: Compilación de Kernel de Linux
La compilación es una tarea que estresa todos los núcleos del procesador. Según los datos de rendimiento, el procesador de Intel logra una ligera ventaja en eficiencia temporal:

| Procesador | Tiempo de Compilación (Promedio) | Resultado |
| :--- | :--- | :--- |
| **Intel Core i5-13600K** | **72 ± 5 segundos** | 🏆 **Ganador** |
| AMD Ryzen 9 5900X | 76 ± 8 segundos | - |

> **Conclusión:** En tareas de procesamiento bruto de código, la arquitectura de Intel demuestra una ejecución más ágil.

---

## 📊 Caso 2: Datos de OpenBenchmark.org
Al analizar las comparaciones públicas de usuarios, encontramos una muestra de **378 benchmarks en común**. El dominio de Intel en esta generación es notable:

* **Tasa de Victoria (Intel):** 79% de los tests ganados.
* **Casos Específicos:**
    * 📂 **Compilación de Código:** Mayor rendimiento en la familia Intel.
    * 🔐 **OpenSSL:** Superioridad para el **Ryzen 9**, demostrando que AMD sigue siendo fuerte en tareas criptográficas específicas.

---

## 🎨 Caso 3: Renderizado 3D (Cinebench)
El renderizado es la prueba de fuego para la potencia mononúcleo y multinúcleo. Basado en los registros de [NanoReview](https://nanoreview.net/en/cpu-list/cinebench-scores):

| Test Cinebench | Líder en Performance |
| :--- | :--- |
| **Single-Core** | **Intel Core i5-13600K** |
| **Multi-Core** | **Intel Core i5-13600K** |

---

## ⚖️ El factor "Cuello de Botella" y GPU
Es importante notar que el rendimiento no depende únicamente de la CPU. En tareas como **Gaming** o **Edición de Video**, entra en juego la combinación de hardware:

1. **Sinergia CPU + GPU:** El rendimiento final es el resultado de qué tan bien trabajan juntos ambos componentes.
2. **Cuello de Botella (Bottleneck):** Una CPU débil puede limitar a una GPU potente, desperdiciando dinero y potencia.
3. **Relación Calidad/Precio:** El objetivo final del benchmarking es determinar qué combinación ofrece la mayor cantidad de "rendimiento por dólar" invertido.