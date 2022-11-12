/** Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Inteligencia Artificial
 * Curso: 3º
 * Autores: Iván Texenery Díaz García & Muhammad Campos Preira
 * Correos: alu0101429762@ull.edu.es & alu0101434025@ull.edu.es
 * Archivo Grid.h: fichero de la clase Grid.
 *         Contiene la declaración de la clase Grid,
 *         encargada de realizar las operaciones correspondientes
 *         sobre el grafo leído con la clase InputOutput y 
 *         contiene una función sencilla para encontrar elementos 
 *         en un vector.
 **/
#pragma once
#include <cmath>
#include "InputOutput.h"
#include <stdlib.h>
static int counter{0};

class Grid {
 public:
  Grid(const int rows, const int columns, const std::pair<int, int> init, const std::pair<int, int> end);
  ~Grid(){};
  friend std::ostream &operator<<(std::ostream &output, const Grid &grid);
  void BFS(std::pair<int, int> inicio, std::pair<int, int> fin, std::string evaluation_function);

 private:
  int rows_{0}, columns_{0}; 
  std::pair<int, int> init_, end_;
  std::vector<std::pair<int, int>> nodes_; 
  std::vector<std::string> path_;

};

//-----------------------------------------------------------------------------------------------
// Finder
//-----------------------------------------------------------------------------------------------

template<class T>
bool Finder(std::vector<T> vector, T element) {
  bool found{false};
  for (auto i : vector) {
    if (i == element) {
      found = true;
    }
  }
  return found;
}