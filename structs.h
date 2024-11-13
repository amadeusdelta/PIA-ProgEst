#ifndef PROJECT_H
#define PROJECT_H
#ifndef MAX_EMPLEADOS
#define MAX_EMPLEADOS 100

typedef struct
{
    char clave_proy[10];
    char nom[30];
    float monto;
    int empleados_registrados;
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

typedef struct
{
    char clave_proy[10];
    int num_emp;
    char nombre[30];
    char curp[19];
    int fecha_nac;
    char correo[20];
    char telefono[10];
    int perfil;
    float tarifa_h;
    float tarifa_mensual;
    DIRECCION direccion;
} EMPLEADO;

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

extern const PROYECTO null_proyecto;
extern const EMPLEADO null_empleado;
extern const HORAS_EMPLEADO null_horas_empleado;
extern const NOMINA null_nomina;

#endif
#endif
