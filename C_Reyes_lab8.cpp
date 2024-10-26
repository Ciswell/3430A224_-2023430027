#include <iostream>
#include <cstdlib> 
#include <ctime>  
#include <chrono>  

// funcion de ordenamiento por Seleccion
void seleccion(int* arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}

// funcion de ordenamiento Quicksort
void quicksort(int* arr, int left, int right) {
    if (left < right) {
        int pivot = arr[right];
        int i = left - 1;
        for (int j = left; j < right; ++j) {
            if (arr[j] <= pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[right]);
        quicksort(arr, left, i);
        quicksort(arr, i + 2, right);
    }
}

void llenarArreglo(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 10000000 + 1;
    }
}

void mostrarArreglo(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "uso: " << argv[0] << " <n> <s/n>\n";
        return 1;
    }

    int n = std::atoi(argv[1]);
    bool mostrar = (argv[2][0] == 's');
    
    if (n <= 0) {
        std::cerr << "el numero de elementos debe ser positivo.\n";
        return 1;
    }

    int* arr1 = new int[n];
    int* arr2 = new int[n];

    srand(static_cast<unsigned int>(time(0)));
    llenarArreglo(arr1, n);
    std::copy(arr1, arr1 + n, arr2);  // copiar el arreglo para que ambos metodos trabajen con los mismos datos

    if (mostrar) {
        std::cout << "arreglo original:\n";
        mostrarArreglo(arr1, n);
    }

    // medicion del tiempo del metodo de seleccion
    auto start = std::chrono::high_resolution_clock::now();
    seleccion(arr1, n);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracion_seleccion = end - start;

    // medicion del tiempo del quicksort
    start = std::chrono::high_resolution_clock::now();
    quicksort(arr2, 0, n - 1);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracion_quicksort = end - start;

    if (mostrar) {
        std::cout << "\narreglo ordenado (seleccion):\n";
        mostrarArreglo(arr1, n);
        std::cout << "\narreglo ordenado (quicksort):\n";
        mostrarArreglo(arr2, n);
    }

    // mostrar los tiempos en milisegundos
    std::cout << "\n-----------------------------------------\n";
    std::cout << "metodo       | tiempo\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "seleccion    | " << duracion_seleccion.count() << " milisegundos\n";
    std::cout << "quicksort    | " << duracion_quicksort.count() << " milisegundos\n";
    std::cout << "-----------------------------------------\n";

    delete[] arr1;
    delete[] arr2;

    return 0;
}
