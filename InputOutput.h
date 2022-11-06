/** Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Inteligencia Artificial
 * Curso: 3º
 * Autores: Iván Texenery Díaz García & Muhammad Campos Preira
 * Correos: alu0101429762@ull.edu.es &
 * Archivo InputOutput.h: fichero de la clase InputOutput.
 *         Contiene la declaración de la clase InputOutput,
 *         encargada de supervisar toda la operación de 
 *         entrada/salida.
 **/
#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class InputOutput {
 public:
  InputOutput(int argc, char* argv[]) {
    argc_ = argc;
    argv_ = argv;
  };
  int GetArgc(){return argc_;};
  char** GetArgv(){return argv_;};
  int InitialCheck();
  void FileInputOutput();

 private:
  int argc_;
  char** argv_;
};