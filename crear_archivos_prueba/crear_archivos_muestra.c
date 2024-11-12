#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "funciones_utils.h"

EMPLEADO empleados[20] = {
    {"PRJ001", 1, "Juan Perez", "HEGJ900101MVZRRL01", 19900101, "juan@correo.com", "5512345678", 1, 50.0, 50.0 * 180, {"Calle Uno", "Colonia A", 101, 12345, "Ciudad Z"}},
    {"PRJ001", 2, "Ana Gomez", "HEGA910320MVZRRL02", 19910320, "ana@correo.com", "5512345679", 2, 45.0, 45.0 * 180, {"Calle Dos", "Colonia B", 102, 12346, "Ciudad Y"}},
    {"PRJ001", 3, "Luis Rios", "HEGR920515MVZRRL03", 19920515, "luis@correo.com", "5512345680", 3, 40.0, 40.0 * 180, {"Calle Tres", "Colonia C", 103, 12347, "Ciudad X"}},
    {"PRJ001", 4, "Maria Lopez", "HEGM930722MVZRRL04", 19930722, "maria@correo.com", "5512345681", 4, 38.0, 38.0 * 180, {"Calle Cuatro", "Colonia D", 104, 12348, "Ciudad W"}},

    {"PRJ002", 5, "Carlos Silva", "HEGC880925MVZRRL05", 19880925, "carlos@correo.com", "5512345682", 5, 55.0, 55.0 * 180, {"Calle Cinco", "Colonia E", 105, 12349, "Ciudad V"}},
    {"PRJ002", 6, "Laura Jimenez", "HEGL890813MVZRRL06", 19890813, "laura@correo.com", "5512345683", 2, 48.0, 48.0 * 180, {"Calle Seis", "Colonia F", 106, 12350, "Ciudad U"}},
    {"PRJ002", 7, "Pedro Castillo", "HEGP940129MVZRRL07", 19940129, "pedro@correo.com", "5512345684", 3, 42.0, 42.0 * 180, {"Calle Siete", "Colonia G", 107, 12351, "Ciudad T"}},
    {"PRJ002", 8, "Sofia Ramirez", "HEGS950316MVZRRL08", 19950316, "sofia@correo.com", "5512345685", 4, 39.0, 39.0 * 180, {"Calle Ocho", "Colonia H", 108, 12352, "Ciudad S"}},

    {"PRJ003", 9, "Miguel Torres", "HEGM850601MVZRRL09", 19850601, "miguel@correo.com", "5512345686", 1, 60.0, 60.0 * 180, {"Calle Nueve", "Colonia I", 109, 12353, "Ciudad R"}},
    {"PRJ003", 10, "Elena Martinez", "HEGE880930MVZRRL10", 19880930, "elena@correo.com", "5512345687", 2, 47.0, 47.0 * 180, {"Calle Diez", "Colonia J", 110, 12354, "Ciudad Q"}},
    {"PRJ003", 11, "Roberto Ramirez", "HEGR950712MVZRRL11", 19950712, "roberto@correo.com", "5512345688", 3, 41.0, 41.0 * 180, {"Calle Once", "Colonia K", 111, 12355, "Ciudad P"}},
    {"PRJ003", 12, "Patricia Lopez", "HEGP921101MVZRRL12", 19921101, "patricia@correo.com", "5512345689", 4, 36.0, 36.0 * 180, {"Calle Doce", "Colonia L", 112, 12356, "Ciudad O"}},

    {"PRJ004", 13, "Ricardo Fuentes", "HEGR830428MVZRRL13", 19830428, "ricardo@correo.com", "5512345690", 1, 52.0, 52.0 * 180, {"Calle Trece", "Colonia M", 113, 12357, "Ciudad N"}},
    {"PRJ004", 14, "Carmen Ortiz", "HEGO920519MVZRRL14", 19920519, "carmen@correo.com", "5512345691", 2, 44.0, 44.0 * 180, {"Calle Catorce", "Colonia N", 114, 12358, "Ciudad M"}},
    {"PRJ004", 15, "Esteban Cruz", "HEGE880625MVZRRL15", 19880625, "esteban@correo.com", "5512345692", 3, 43.0, 43.0 * 180, {"Calle Quince", "Colonia O", 115, 12359, "Ciudad L"}},
    {"PRJ004", 16, "Lucia Rivera", "HEGL931003MVZRRL16", 19931003, "lucia@correo.com", "5512345693", 4, 37.0, 37.0 * 180, {"Calle Dieciseis", "Colonia P", 116, 12360, "Ciudad K"}},

    {"PRJ005", 17, "Julio Salinas", "HEGJ820729MVZRRL17", 19820729, "julio@correo.com", "5512345694", 1, 53.0, 53.0 * 180, {"Calle Diecisiete", "Colonia Q", 117, 12361, "Ciudad J"}},
    {"PRJ005", 18, "Veronica Soto", "HEGV860214MVZRRL18", 19860214, "veronica@correo.com", "5512345695", 2, 46.0, 46.0 * 180, {"Calle Dieciocho", "Colonia R", 118, 12362, "Ciudad I"}},
    {"PRJ005", 19, "Oscar Vargas", "HEGO930101MVZRRL19", 19930101, "oscar@correo.com", "5512345696", 3, 39.0, 39.0 * 180, {"Calle Diecinueve", "Colonia S", 119, 12363, "Ciudad H"}},
    {"PRJ005", 20, "Isabel Guerra", "HEGI940227MVZRRL20", 19940227, "isabel@correo.com", "5512345697", 4, 42.0, 42.0 * 180, {"Calle Veinte", "Colonia T", 120, 12364, "Ciudad G"}}};

NOMINA nominas[5] = {
    {"PRJ001", 11, 2024, {{1, "Juan Perez", 1, 50.0, 180, 50.0 * 180}, {2, "Ana Gomez", 2, 45.0, 172, 45.0 * 172}, {3, "Luis Rios", 3, 40.0, 185, 40.0 * 185}, {4, "Maria Lopez", 4, 38.0, 178, 38.0 * 178}}},
    {"PRJ002", 11, 2024, {{5, "Carlos Silva", 5, 55.0, 190, 55.0 * 190}, {6, "Laura Jimenez", 2, 48.0, 175, 48.0 * 175}, {7, "Pedro Castillo", 3, 42.0, 182, 42.0 * 182}, {8, "Sofia Ramirez", 4, 39.0, 170, 39.0 * 170}}},
    {"PRJ003", 11, 2024, {{9, "Miguel Torres", 1, 60.0, 188, 60.0 * 188}, {10, "Elena Martinez", 2, 47.0, 176, 47.0 * 176}, {11, "Roberto Ramirez", 3, 41.0, 179, 41.0 * 179}, {12, "Patricia Lopez", 4, 36.0, 184, 36.0 * 184}}},
    {"PRJ004", 11, 2024, {{13, "Ricardo Fuentes", 1, 52.0, 173, 52.0 * 173}, {14, "Carmen Ortiz", 2, 44.0, 187, 44.0 * 187}, {15, "Esteban Cruz", 3, 43.0, 171, 43.0 * 171}, {16, "Lucia Rivera", 4, 37.0, 180, 37.0 * 180}}},
    {"PRJ005", 11, 2024, {{17, "Julio Salinas", 1, 53.0, 186, 53.0 * 186}, {18, "Veronica Soto", 2, 46.0, 174, 46.0 * 174}, {19, "Oscar Vargas", 3, 39.0, 181, 39.0 * 181}, {20, "Isabel Guerra", 4, 42.0, 177, 42.0 * 177}}}};

PROYECTO proyectos[5] = {
    {"PRJ001", "Proyecto Alpha", 100000.0, 4, 16112024, 16112025},
    {"PRJ002", "Proyecto Beta", 150000.0, 4, 17112024, 17112025},
    {"PRJ003", "Proyecto Gamma", 200000.0, 4, 18112024, 18112025},
    {"PRJ004", "Proyecto Delta", 250000.0, 4, 19112024, 19112025},
    {"PRJ005", "Proyecto Epsilon", 300000.0, 4, 20112024, 20112025}};

void crear_proyectos(PROYECTO *proyectos)
{
    FILE *archivo = fopen("registro_proyectos.dat", "wb");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo de proyectos");
        return;
    }

    fwrite(proyectos, sizeof(PROYECTO), 5, archivo);
    fclose(archivo);
}

void crear_empleados(EMPLEADO *empleados)
{
    FILE *archivo = fopen("registro_empleados.dat", "wb");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo de empleados");
        return;
    }

    fwrite(empleados, sizeof(EMPLEADO), 20, archivo);
    fclose(archivo);
}

void guardar_nominas(NOMINA nominas[])
{
    FILE *file = fopen("registro_nominas.dat", "wb");
    if (file == NULL)
    {
        perror("Error al abrir el archivo de nominas");
        return;
    }

    for (int i = 0; i < 5; i++)
    {
        fwrite(&nominas[i], sizeof(NOMINA), 1, file);
    }

    fclose(file);
    printf("Nominas guardadas en registro_nominas.dat exitosamente.\n");
}

int main(int argc, char const *argv[])
{
    crear_proyectos(proyectos);
    crear_empleados(empleados);
    guardar_nominas(nominas);
    return 0;
}
