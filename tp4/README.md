Kernel Modules

Para este proyecto es necesario contar con los headers de linux instalados, para lo cual se utiliza el siguiente comando

sudo apt-get install build-essential checkinstall linux-source linux-headers-$(uname -r)

donde el uso de $(uname -r) nos asegura que se instalen los headers correspondientes al kernel de linux instalado en nuestro sistema.

A la hora de generar modulos de kernel es necesario que realicemos una escritura adecuada de las syscalls para que el compilador pueda comunicar de manera adecuada los atributos insertados, esto lo podemos verificar mediante el uso de los headers. Lo Headers tienen informacion sobre las funciones existentes en el kernel, los parametros que reciben y los tipos de datos que devuelven. De esta forma evitamos tener que descargar la totalidad de funciones y en su lugar le damos una estructura con la que puede comunicarse nuestro modulo con el kernel de linux que tengamos instalado. 