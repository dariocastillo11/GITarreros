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

## 📊 Datos de OpenBenchmark.org
Al analizar las comparaciones públicas de usuarios, encontramos una muestra de **378 benchmarks en común**. El dominio de Intel en esta generación es notable:

* **Tasa de Victoria (Intel):** 79% de los tests ganados.
* **Casos Específicos:**
    * 📂 **Compilación de Código:** Mayor rendimiento en la familia Intel.
    * 🔐 **OpenSSL:** Superioridad para el **Ryzen 9**, demostrando que AMD sigue siendo fuerte en tareas criptográficas específicas.

---

## 🎨 Caso 2: Renderizado 3D (Cinebench)
El renderizado es la prueba de fuego para la potencia mononúcleo y multinúcleo. Basado en los registros de [NanoReview](https://nanoreview.net/en/cpu-list/cinebench-scores):

| Test Cinebench | Líder en Performance |
| :--- | :--- |
| **Single-Core** | **Intel Core i5-13600K** |
| **Multi-Core** | **Intel Core i5-13600K** |

---

##   Rendimiento en Gaming (3DMark)
Aunque 3DMark es famoso por medir la tarjeta gráfica (GPU), su prueba de CPU mide la capacidad del procesador para calcular físicas complejas en videojuegos (partículas, destrucción, multitudes).

* **Intel Core i5-13600K (CPU Score):** 17,500 puntos.
* **AMD Ryzen 9 5900X (CPU Score):** 14,000 puntos.

 **Conclusión:** Si el objetivo principal del equipo es el **Gaming**, el i5-13600K es una opción superior, garantizando que el procesador no haga "cuello de botella" con tarjetas gráficas de gama alta.

---

##   Tareas Cotidianas y Productividad 
Geekbench nos permite ver cómo se comportan estos procesadores en escenarios del día a día (navegación pesada, compresión de archivos, procesamiento de fotos). 

| Tipo de Carga | Intel Core i5-13600K | AMD Ryzen 9 5900X |
| :--- | :--- | :--- |
| **Single-Core** | 2,700 pts | 2,100 pts |
| **Multi-Core** | 16,500 pts | 13,000 pts |

 **Conclusión:** La arquitectura híbrida de Intel permite que los "E-cores" (núcleos de eficiencia) manejen las tareas de fondo, dejando los "P-cores" (núcleos de rendimiento) libres para las tareas principales, logrando una fluidez notable.


---

## Consumo Energético y Temperaturas (OCCT + HWiNFO64)
El costo energético y térmico cuando estresamos los equipos al 100% usando herramientas como OCCT.

| Especificación | Intel Core i5-13600K | AMD Ryzen 9 5900X |
| :--- | :--- | :--- |
| **TDP Base** | 125 W | 105 W |
| **Consumo Máximo (Carga 100%)** | **181 W** | **142 W** |
| **Temperatura Promedio bajo estrés** | Más alta (Requiere buen AIO/Cooler) | Más moderada |

 **Conclusión:** Aquí es donde AMD saca ventaja. El **Ryzen 9 5900X es considerablemente más eficiente energéticamente**. El procesador de Intel, para lograr esos picos de rendimiento, necesita consumir mucha más electricidad y genera más calor, obligando al usuario a invertir más en un buen sistema de refrigeración.

---


# 📊 Rendimiento, Speedup y Eficiencia

Para este estudio, tomamos como **línea de base (Baseline)** al procesador **AMD Ryzen 9 5900X**. Los datos analizados corresponden a la prueba de compilación del Kernel de Linux (`build-linux-kernel-1.15.x`), obtenida a través de *Phoronix Test Suite*.

## 1. Rendimiento ($R$)
El rendimiento se define como la relación inversamente proporcional al tiempo de ejecución ($T$). Se calcula mediante la fórmula:

$$R = \frac{1}{T}$$

| Procesador | Cores | Tiempo (s) | Rendimiento |
| :--- | :---: | :---: | :--- |
| AMD Ryzen 9 5900X | 12 | 76 | 0.0131 |
| **Intel Core i5-13600K** | 14 | 72 | 0.0138 |
| **AMD Ryzen 9 7950X** | 16 | 50 | **0.0200** |

---

## 2. Speedup ($S$)
El **Speedup** es la métrica que indica cuánto más rápido es un sistema en comparación con nuestra base (Ryzen 9 5900X).

$$S = \frac{T_{referencia}}{T_{nuevo}}$$

| Procesador | Speedup | Estado |
| :--- | :---: | :--- |
| AMD Ryzen 9 5900X | 1.00x | *Baseline* |
| Intel Core i5-13600K | 1.06x | +6% más rápido |
| **AMD Ryzen 9 7950X** | **1.52x** | **+52% más rápido** |

---

## 3. Análisis de Eficiencia
La eficiencia nos permite entender si el rendimiento obtenido justifica el uso de recursos (núcleos) o la inversión económica.

### A. Eficiencia por Núcleo ($E_n$)
Calculada como el rendimiento obtenido por cada núcleo físico del procesador:
$$E_n = \frac{R}{\text{Núcleos}}$$

| Procesador | Eficiencia/Núcleo | Observación |
| :--- | :---: | :--- |
| **AMD Ryzen 9 7950X** | **0.001250** | **Más eficiente por núcleo** |
| AMD Ryzen 9 5900X | 0.001091 | Equilibrio medio |
| Intel Core i5-13600K | 0.000985 | Menor eficiencia por núcleo |

> **Nota técnica:** Aunque el Intel i5-13600K es más rápido que el 5900X, su eficiencia por núcleo es menor. Esto demuestra que el rendimiento no depende solo de la cantidad de núcleos, sino de factores como la **arquitectura**, las **frecuencias de reloj** y la **jerarquía de memoria caché**.

### B. Eficiencia por Costo ($E_c$)
Basado en precios de referencia de *Newegg.com*. Refleja cuánto rendimiento obtenemos por cada dólar invertido.
$$E_c = \frac{R}{\text{Precio}}$$

| Procesador | Precio (USD) | Eficiencia/Precio |
| :--- | :---: | :--- |
| **Intel Core i5-136

## ⚖️ El factor "Cuello de Botella" y GPU
Es importante notar que el rendimiento no depende únicamente de la CPU. En tareas como **Gaming** o **Edición de Video**, entra en juego la combinación de hardware:

1. **Sinergia CPU + GPU:** El rendimiento final es el resultado de qué tan bien trabajan juntos ambos componentes.
2. **Cuello de Botella (Bottleneck):** Una CPU débil puede limitar a una GPU potente, desperdiciando dinero y potencia.
3. **Relación Calidad/Precio:** El objetivo final del benchmarking es determinar qué combinación ofrece la mayor cantidad de "rendimiento por dólar" invertido.