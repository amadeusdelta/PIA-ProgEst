#ifndef PROJECT_H
#define PROJECT_H

#include <string.h>

// Estructura para el registro de proyectos

typedef struct
{
    char clave_proy[10];
    char nom[30];
    float monto;
    int fecha_i;
    int fecha_f;
} PROYECTO;

// Estructura para el registro de empleados
typedef struct
{
    char clave_proy[10];
    int num_emp;
    char nombre[30];
    char curp[18];
    int fecha_nac;
    char correo[20];
    int telefono;
    float tarifa_h;

} EMPLEADO;

// Estructura para el registro de usuarios
typedef struct
{
    char usuario[50];
    char contraseña[50];
} USUARIO;

// Instancias nulas o por defecto para cada estructura
const PROYECTO null_proyecto = {"", "", 0.0, 0, 0};
const EMPLEADO null_empleado = {"", 0, "", "", 0, "", 0};
const USUARIO null_usuario = {"", ""};

#endif
