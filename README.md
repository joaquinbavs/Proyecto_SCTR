IMPORTATNE: EL PROYECTO DEFINITIVO SE ENCUENTRA EN LA RAMA ramaFSM. En este proyecto, tenemos la existencia de 3 ramas. Una de ellas, la rama main, es la cual no sigue un modelo FSM (TABLE-DRIVEN), si no que lo hace mediante condiciones. 
Por otro lado tenemos otra rama que es la que sigue un modelo FSM (TABLE-DRIVEN), el cual se llama ramaFSM. 
Por último tenemos una rama, la cual fue la base a partir de la cual se crearon estas otras dos. Dentro de cada rama, tenemos 2 carpetas (include y src) donde se encuentran los headers y archivos de codigo fuente C. 
Además tenemos otros dos archivos. Pico_sdk_import_cmake que es un script que te ayuda a incluir y configurar el SDK de la Raspberry Pi Pico; 
y por otro lado CMakeLists.txt que es el archivo de configuración que define cómo se debe construir el proyecto, incluyendo el uso de bibliotecas, fuentes y configuraciones específicas. 
Por último se adjunta un esquema del circuito de nuestra placa:


<img width="485" height="344" alt="image" src="https://github.com/user-attachments/assets/b0562ab4-7ef6-4eba-9fa8-0f90cc4e3f52" />

(Se ha obviado el buzzer en la imagen, el cual iría conectado al pin 14 de la Raspberry Pi Pico)
