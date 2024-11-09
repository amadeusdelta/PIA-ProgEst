#ifndef PROJECT_H
#define PROJECT_H
#ifndef MAX_EMPLEADOS
#define MAX_EMPLEADOS 100

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
    DIRECCION direccion;
} EMPLEADO;

typedef struct
{
} DIRECCION;

// Estructura para el registro de usuarios
typedef struct
{
    char usuario[50];
    char contraseña[50];
} USUARIO;

// Estructura usada en nominas para guardar datos de cada empleado
typedef struct
{
    int num_emp;
    char clave_proy[10];
    int horas_trabajadas;
    float sueldo_mensual;
} HORAS_EMPLEADO;

typedef struct
{
    int num_emp;
    char clave_proy[10];
    int total_horas_trabajadas;
    int mes_creacion;
    int ano_creacion;
    HORAS_EMPLEADO empleado[MAX_EMPLEADOS];
} NOMINA;

// Instancias nulas o por defecto para cada estructura
const PROYECTO null_proyecto = {"", "", 0.0, 0, 0};
const EMPLEADO null_empleado = {"", 0, "", "", 0, "", 0};
const USUARIO null_usuario = {"", ""};
const HORAS_EMPLEADO null_horas_empleado = {0, "", 0};
const NOMINA null_nomina = {0, "", 0, 0, {0, "", 0}};

#endif // Cierre para MAX_EMPLEADOS
#endif // Cierre para PROJECT_H
