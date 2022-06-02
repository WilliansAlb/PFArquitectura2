# Proyecto Final Arquitectura de Computadores 2
## _Descripción_
En los hospitales públicos de Guatemala se cuenta con diversos servicios los cuales están disponibles para los pacientes/usuarios que llegan a necesitarlos, estos servicios se encuentran en distintas áreas dentro del hospital, por ejemplo se tiene el área de maternidad, de rayos X, de oftalmología, de pulmones, entre otros. La manera de funcionar de los hospitales es que el ingreso es el mismo para todos (entrada) en el cual dependiendo al servicio que vayan a utilizar se les asigna un turno conforme van llegando (FIFO) y se dirigen a las salas de espera para ser atendidos según el orden asignado.

Debido a la pandemia de COVID-19 como políticas de prevención se recomienda el distanciamiento social y evitar las aglomeraciones, por lo que como ingenieros se les solicita una solución para llevar a cabo de mejor manera el manejo de la asignación de turnos a los pacientes y que estos eviten aglomeraciones en las salas de los servicios, así como en el resto de las instalaciones del hospital. Se sabe que los servicios tienen un número limitado de pacientes para ser atendidos por día, así como la cantidad total de personas (pacientes y personal del hospital) en un momento en las instalaciones no debería de excederse para reducir riesgos y tener instalaciones seguras.

## Características
- Implementa conceptos y tecnologías de IoT (Internet de las cosas), usando microcontroladores, sensores, actuadores y perifericos para el manejo de turnos del hospital.
- Se utiliza tecnología RFID para el control de la entrada de las personas, así como el manejo de los turnos de las diferentes áreas.
- Hace uso de displays inteligentes para mostrar información relevante (turno siguiente), área que consulta, personas que se encuentran en el área entre otras.
- Implementa un sistema SCADA para controlar, supervisar y adquirir datos (SCADA) con la finalidad de manejar los turnos, la información del estado del hospital (cantidad de visitantes y personal), así como activar alertas de emergencia.
- Considera la activación automática de ventiladores para hacer circular el aire según la cantidad de personas en las instalaciones, así también cuenta con la posibilidad de modificar los valores a los que se activará

## Tecnologías

Se usaron las siguientes herramientas para la creación del proyecto:

- [ESP8266](https://www.espressif.com/) - Chip Wi-Fi de bajo coste con pila TCP/IP
- [Arduino](www.arduino.cc) - Editor de código de Arduino
- [Visual Studio Code](https://code.visualstudio.com/) - Editor de código
- [node.js] - Entorno de servidor de código abierto
- [Express] - Framework web más popular de Node
- [MySQL](https://www.mysql.com/) - Sistema de gestión de bases de datos

## Installation
## _Servidor Node_
Este proyecto requiere de [Node.js](https://nodejs.org/) v10+ para funcionar.

Instala las dependencias y empieza el servidor

```sh
npm i
npm run start
```
## _Base de datos_
Este proyecto requiere de tener alguna base de datos relacional, de preferencia MySQL.
Ejecuta los scripts sql DDL y DML para empezar a utilizar la base de datos
## _ESP8266_
Utiliza el editor de Arduino, asegurate de que reconozca el puerto de conexión del ESP8266 y que tengas todas las librerías instaladas.

## License

MIT

   [dill]: <https://github.com/joemccann/dillinger>
   [git-repo-url]: <https://github.com/joemccann/dillinger.git>
   [john gruber]: <http://daringfireball.net>
   [df1]: <http://daringfireball.net/projects/markdown/>
   [markdown-it]: <https://github.com/markdown-it/markdown-it>
   [Ace Editor]: <http://ace.ajax.org>
   [node.js]: <http://nodejs.org>
   [Twitter Bootstrap]: <http://twitter.github.com/bootstrap/>
   [jQuery]: <http://jquery.com>
   [@tjholowaychuk]: <http://twitter.com/tjholowaychuk>
   [express]: <http://expressjs.com>
   [AngularJS]: <http://angularjs.org>
   [Gulp]: <http://gulpjs.com>