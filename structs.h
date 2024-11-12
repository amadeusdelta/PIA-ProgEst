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
    // Maximo 100 empleados registrados
    int empleados_registrados;
    // La fecha del registro del proyecto no se usa nunca, no esta implentado
    // en ninguna parte del codigo de forma funcional, pues no es necesario
    int fecha_i;
    int fecha_f;
} PROYECTO;

typedef struct
{
    char calle[30];
    char colonia[30];
    int numero;
    int CP;
    char municipio[30];
} DIRECCION;

// Estructura para el registro de empleados
typedef struct
{
    char clave_proy[10];
    int num_emp;
    char nombre[30];
    char curp[18];
    int fecha_nac;
    char correo[20];
    char telefono[10];
    int perfil;
    float tarifa_h;
    float tarifa_mensual;
    DIRECCION direccion;
} EMPLEADO;

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
    char nom[30];
    int perfil;
    float tarifa_h;
    int horas_trabajadas;
    float sueldo_mensual;
} HORAS_EMPLEADO;

typedef struct
{
    char clave_proy[10];
    int mes_creacion;
    int ano_creacion;
    HORAS_EMPLEADO empleados[MAX_EMPLEADOS];
} NOMINA;

// Instancias nulas o por defecto para cada estructura
extern const PROYECTO null_proyecto;
extern const EMPLEADO null_empleado;
extern const USUARIO null_usuario;
extern const HORAS_EMPLEADO null_horas_empleado;
extern const NOMINA null_nomina;

#endif // Cierre para MAX_EMPLEADOS
#endif // Cierre para PROJECT_H
