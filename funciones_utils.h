#ifndef FUNCIONES_UTILS_H
#define FUNCIONES_UTILS_H
#include "structs.h"
void imprimir_empleado(EMPLEADO empleado);
int obtener_num(int opc);
const char *num_a_mes(int num);
void crear_directorio(const char *path);
EMPLEADO *leer_empleados_proyecto(char clave_proyecto[10]);
PROYECTO buscar_proyecto(char clave_proyecto[10]);

#endif // FUNCIONES_UTILS_H
