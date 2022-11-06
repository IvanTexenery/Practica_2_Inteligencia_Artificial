/** Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Inteligencia Artificial
 * Curso: 3º
 * Autores: Iván Texenery Díaz García & Muhammad Campos Preira
 * Correos: alu0101429762@ull.edu.es &
 * Archivo Grid.cc: fichero de la clase Grid.
 *         Contiene la definición de la clase Grid,
 *         encargada de realizar las operaciones correspondientes
 *         sobre el grafo leído con la clase InputOutput.
 **/
#include "Grid.h"
// Constructor
Grid::Grid(const int rows, const int columns, const std::pair<int, int> init,
           const std::pair<int, int> end) {
  rows_ = rows;
  columns_ = columns;
  init_ = init;
  end_ = end;

  for (int i{0}; i < rows; ++i) {
    for (int j{0}; j < columns; ++j) {
      nodes_.emplace_back(std::pair<int, int>(i, j));
    }
  }
  for (int i{0}; i < rows; ++i) {
    for (int j{0}; j < columns; ++j) {
      if (init.first == i && init.second == j) {
        path_.emplace_back("I");
      } else if (end.first == i && end.second == j) {
        path_.emplace_back("D");
      } else {
        path_.emplace_back("∙");
      }
    }
  }
}

//-----------------------------------------------------------------------------------------------
// Distancia Euclídea
//-----------------------------------------------------------------------------------------------
int EuclideanDistance(std::pair<int, int> current,
                          std::pair<int, int> end) {
  return (sqrt(pow(abs(current.first - end.first), 2) + pow(abs(current.second - end.second), 2)));
}
//-----------------------------------------------------------------------------------------------
// Distancia Manhattan
//-----------------------------------------------------------------------------------------------
int ManhattanDistance(std::pair<int, int> current, std::pair<int, int> end) {
  return (abs(current.first - end.first) + abs(current.second - end.second));
}
//-----------------------------------------------------------------------------------------------
// Búsqueda Primero El Mejor
//-----------------------------------------------------------------------------------------------
void Grid::BFS(std::pair<int, int> inicio, std::pair<int, int> fin,
               std::string evaluation_function) {
  // Vectores auxiliares o lista abierta
  std::vector<std::pair<int, int>> open_list;
  std::vector<std::pair<int, int>> open_list_antecesors;
  std::vector<double> open_list_distances;
  std::vector<std::string> open_list_directions;
  // Inicialización de la lista abierta
  open_list.emplace_back(inicio);
  open_list_antecesors.emplace_back(inicio);
  open_list_distances.emplace_back(0);
  open_list_directions.emplace_back("I");
  // Vectores para construir el camino o lista cerrada
  std::vector<std::pair<int, int>> closed_list;
  std::vector<std::pair<int, int>> closed_list_antecesors;
  std::vector<std::string> closed_list_directions;
  // Vector de nodos generados
  std::vector<std::pair<int, int>> generated_nodes;
  generated_nodes.emplace_back(inicio);
  // Vector de nodos visitados o inspeccionados
  std::vector<std::pair<int, int>> inspected_nodes;
  inspected_nodes.emplace_back(inicio);
  // Flag
  bool end = false;
  while (!open_list.empty() && !end) {
    int position{0};
    double previous{0}, next{0};
    std::pair<int, int> best_node{0, 0}, auxiliar{0, 0};
    // Recorremos la cola de nodos por visitar, eligiendo el nodo de menor
    // distancia al nodo final
    for (int j{0}; j < (int)open_list.size(); ++j) {
      next = open_list_distances[j];
      if (previous > next) {
        previous = next;
        position = j;
      } else if (previous <= next && previous == 0) {
        previous = next;
        position = j;
      }
    }

    // Añadimos el nodo de menor coste a cada vector
    closed_list.emplace_back(open_list[0 + position]);
    closed_list_antecesors.emplace_back(open_list_antecesors[0 + position]);
    closed_list_directions.emplace_back(open_list_directions[0 + position]);
    best_node = open_list[position];

    if (!Finder(inspected_nodes, best_node)) {
      inspected_nodes.emplace_back(best_node);
    }
    // Si el nodo a inspeccionar es el final, finaliza la búsqueda
    if (best_node == fin) {
      end = true;
      break;
    }
    // Introducimos en la cola los respectivos vecinos del nodo
    // Casilla de abajo
    auxiliar.first = best_node.first + 1;
    auxiliar.second = best_node.second;
    if (auxiliar.first < rows_ && auxiliar.first >= 0 &&
        auxiliar.second < columns_ && auxiliar.second >= 0 &&
        !Finder(inspected_nodes, auxiliar) && !Finder(open_list, auxiliar)) {
      open_list_antecesors.emplace_back(best_node);
      if (evaluation_function == "Manhattan") {
        open_list_distances.emplace_back(ManhattanDistance(auxiliar, fin));
      } else {
        open_list_distances.emplace_back(EuclideanDistance(auxiliar, fin));
      }

      generated_nodes.emplace_back(auxiliar);
      open_list.emplace_back(auxiliar);
      open_list_directions.emplace_back("↓");
    }

    // Casilla de encima
    auxiliar.first = best_node.first - 1;
    auxiliar.second = best_node.second;
    if (auxiliar.first < rows_ && auxiliar.first >= 0 &&
        auxiliar.second < columns_ && auxiliar.second >= 0 &&
        !Finder(inspected_nodes, auxiliar) && !Finder(open_list, auxiliar)) {
      open_list_antecesors.emplace_back(best_node);
      if (evaluation_function == "Manhattan") {
        open_list_distances.emplace_back(ManhattanDistance(auxiliar, fin));
      } else {
        open_list_distances.emplace_back(EuclideanDistance(auxiliar, fin));
      }
      generated_nodes.emplace_back(auxiliar);
      open_list.emplace_back(auxiliar);
      open_list_directions.emplace_back("↑");
    }

    // Casilla de la derecha
    auxiliar.first = best_node.first;
    auxiliar.second = best_node.second + 1;
    if (auxiliar.first < rows_ && auxiliar.first >= 0 &&
        auxiliar.second < columns_ && auxiliar.second >= 0 &&
        !Finder(inspected_nodes, auxiliar) && !Finder(open_list, auxiliar)) {
      open_list_antecesors.emplace_back(best_node);
      if (evaluation_function == "Manhattan") {
        open_list_distances.emplace_back(ManhattanDistance(auxiliar, fin));
      } else {
        open_list_distances.emplace_back(EuclideanDistance(auxiliar, fin));
      }
      generated_nodes.emplace_back(auxiliar);
      open_list.emplace_back(auxiliar);
      open_list_directions.emplace_back("→");
    }

    // Casilla de la izquierda
    auxiliar.first = best_node.first;
    auxiliar.second = best_node.second - 1;
    if (auxiliar.first < rows_ && auxiliar.first >= 0 &&
        auxiliar.second < columns_ && auxiliar.second >= 0 &&
        !Finder(inspected_nodes, auxiliar) && !Finder(open_list, auxiliar)) {
      open_list_antecesors.emplace_back(best_node);
      if (evaluation_function == "Manhattan") {
        open_list_distances.emplace_back(ManhattanDistance(auxiliar, fin));
      } else {
        open_list_distances.emplace_back(EuclideanDistance(auxiliar, fin));
      }
      generated_nodes.emplace_back(auxiliar);
      open_list.emplace_back(auxiliar);
      open_list_directions.emplace_back("←");
    }
    // Borramos el nodo examinado dado que ya no lo utilizamos
    open_list.erase(open_list.begin() + position);
    open_list_antecesors.erase(open_list_antecesors.begin() + position);
    open_list_distances.erase(open_list_distances.begin() + position);
    open_list_directions.erase(open_list_directions.begin() + position);
  }
  // Obtenemos los nodos generados y visitados
  // generated_vertex_ = generated_vertex.size();
  // inspected_vertex_ = inspected_vertex.size();
  // Obtenemos el camino mínimo a través de la lista cerrada
  std::pair<int, int> node{fin};
  for (size_t i{closed_list.size() - 1}; i > 0; --i) {
    if (node == closed_list[i]) {
      path_[node.first * columns_ + node.second] = closed_list_directions[i];
      node = closed_list_antecesors[i];
    }
  }
  path_[fin.first * columns_ + fin.second] = "D";
}

//-----------------------------------------------------------------------------------------------
// Operador de inserción
//-----------------------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &output, const Grid &grid) {
  output << "Grid de " << grid.rows_ << " filas y " << grid.columns_
         << " columnas" << std::endl;
  for (int i{0}; i < grid.rows_; ++i) {
    for (int j{0}; j < grid.columns_; ++j) {
      output << grid.path_[i * grid.columns_ + j];
    }
    output << std::endl;
  }
  return output;
}