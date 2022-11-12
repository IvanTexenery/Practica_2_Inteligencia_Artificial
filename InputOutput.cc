/** Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Inteligencia Artificial
 * Curso: 3º
 * Autores: Iván Texenery Díaz García & Muhammad Campos Preira
 * Correos: alu0101429762@ull.edu.es & alu0101434025@ull.edu.es
 * Archivo InputOutput.cc: fichero de la clase InputOutput.
 *         Contiene la definición de la clase InputOutput,
 *         encargada de supervisar toda la operación de
 *         entrada/salida.
 **/
#include "InputOutput.h"

#include "Grid.h"

int InputOutput::InitialCheck() {
  // Menú de control de parámetros y ayuda al usuario
  int argc{GetArgc()};
  char** argv{GetArgv()};
  if (argc != 2) {
    std::cout << "Modo de empleo: " << argv[0] << " [FICHERO DE SALIDA]"
              << std::endl
              << "Pruebe " << argv[0] << " --help para más información"
              << std::endl;
    return 1;
  } else {
    std::string help{argv[1]};
    if ("--help" == help) {
      std::cout << "Introduzca el nombre del programa y el fichero de datos de "
                << "salida: " << std::endl
                << argv[0] << " [FICHERO DE SALIDA]" << std::endl;
      return 1;
    }
  }
  return 0;
}

void InputOutput::FileInputOutput() {
  char** argv{GetArgv()};
  // Asignamos el archivo de Salida
  std::ofstream my_output_file;
  my_output_file.open(argv[1]);

  bool finished{false};
  while (!finished) {
    int rows, columns;
    std::pair<int, int> init, end;

    // Solicitamos los vértices de inicio y destino
    std::cout << "Introduzca el número de filas: ";
    std::cin >> rows;
    std::cout << "Introduzca el número de columnas: ";
    std::cin >> columns;
    std::cout << "Introduzca coordenada x del nodo de inicio: ";
    std::cin >> init.first;
    std::cout << "Introduzca coordenada y del nodo de inicio: ";
    std::cin >> init.second;
    std::cout << "Introduzca coordenada x del nodo de destino: ";
    std::cin >> end.first;
    std::cout << "Introduzca coordenada y del nodo de destino: ";
    std::cin >> end.second;
    if (init.first > rows - 1 || init.second > columns - 1 ||
        end.first > rows - 1 || end.second > columns - 1 || init.first < 0 ||
        init.second < 0 || end.first < 0 || end.second < 0) {
      std::cout << "Se ha introducido un nodo inalcanzable." << std::endl;
      finished = true;
      break;
    } else {
      // Solicitamos que tipo de función de evaluación se desea usar
      std::string evaluation_function{""};
      bool finished_2{false};
      while (!finished_2) {
        std::cout << "Introduzca que tipo de función de evaluación se desea "
                     "utilizar[Manhattan|Euclidean]:";
        std::cin >> evaluation_function;
        if (evaluation_function != "Manhattan" &&
            evaluation_function != "Euclidean") {
          std::cout << "Introduzca una función válida." << std::endl;
        } else {
          finished_2 = true;
        }
      }
      // Creamos el grafo correspondiente y realizamos las operaciones de la
      // búesqueda en anchura
      Grid grid(rows, columns, init, end);
      grid.BFS(init, end, evaluation_function);
      my_output_file << grid;
      finished = true;
    }
  }
  // Cuando hayamos terminado con la ejecución del programa, cerramos el archivo
  // de salida
  my_output_file.close();
}