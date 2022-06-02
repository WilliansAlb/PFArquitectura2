CREATE DATABASE Hospital;
USE Hospital;
DROP TABLE area;
CREATE TABLE IF NOT EXISTS area(
    nombre VARCHAR(45) NOT NULL,
    aforo_maximo INT NOT NULL DEFAULT 10,
    turno_actual INT NOT NULL DEFAULT 0,
    turno_total INT NOT NULL DEFAULT 0,
    aforo_actual INT NOT NULL DEFAULT 0,
    PRIMARY KEY(nombre)
);