/** Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Inteligencia Artificial
 * Curso: 3º
 * Autores: Iván Texenery Díaz García & Muhammad Campos Preira
 * Correos: alu0101429762@ull.edu.es &
 * Archivo ASearch.cc: fichero main.
 *         Se encarga de crear un objeto de
 *         la clase InputOutput e interactuar
 *         con sus funciones miembro.
 **/
#include "InputOutput.h"

int main(int argc, char* argv[]) {
  InputOutput file(argc, argv);
  if (file.InitialCheck() == 0) {
    file.FileInputOutput();
  }
  return 0;
}