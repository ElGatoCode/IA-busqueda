
# Inteligencia Artificial - Búsquedas

##### Miguel Martín

##### alu0101209777@ull.edu.es

Implementación de algoritmos de búsquedas informadas.

#### Algoritmos

* A*

  

#### Heurísticas
*  ``` manhattan | Manhattan ``` Manhattan distance (default)

*  ```Euclidean | euclidean | Pythagorean | pythagorean ``` Euclidean distance

  
  

## Guía de uso

  

1.  **Descargue el código**

2.  **Compile el programa con**  ```make bin/search ```

  

### Ejecución

Hay tres formas de ejecutar y pasar los parámetros al programa:

##### Modo interactivo

Ejecute el programa sin pasar ningún argumento: ```bin/search``` y este solicitará todos los parámetros necesarios: dimensiones del tablero, coordenadas del punto inicial y final, número de obstáculos, posición de los mismos, etc...

##### Línea de comandos

Ejecute el programa con las opciones ```bin/search [opciones]```

**Opciones**

  

```-r o --rows num_filas``` Especifica el número de filas, por defecto es 75

  

```-c o --cols num_columnas``` Especifica el número de columnas, por defecto es 75

  

```-o o --obstacles num_obstaculos``` Especifica el número de obstáculos (posiciones aleatorias), por defecto es 0. <br>

**Nota**: si se especifica un num_obstaculos mayor o igual que el área se colocarán area - 2 obstáculos como máximo.

  

```-f o --file nombre_fichero``` Especifica un fichero con el tablero a cargar (vea [Formatos](#formatos) para más información)

  

```-fp o --fillp porcentaje``` Especifica el porcentaje de obstáculos del tablero (posiciones aleatorias), por defecto es 0.0. (0 <= porcentaje <= 1) <br>

**Nota**: si se especifica un porcentaje mayor o igual que 1 se colocarán area - 2 obstáculos como máximo.

  

```-h o --heuristic heuristica``` Especifica la heurística a utilizar (vea [Heurísticas](#heuristicas) para más información)

```--coord.a row col``` Especifica las coordenadas del punto inicial (row, col), por defecto son (0, 0)

```--coord.b row col``` Especifica las coordenadas del punto final (row, col), por defecto son (rows -1, cols -1)

```--no-print``` No imprime el tablero. Por defecto se imprime el tablero sin solución y posteriormente el tablero con la solución (si la hay).

### Formatos

  

##### Fichero con tablero

Ejemplo:

```

3 5

A . . . .

. # # # .

. . . . B

```

**Primera línea:** dos números enteros separados por un espacio en blanco donde el primero (X) representa el número de filas y el segundo (Y) el número de columnas <br>

**Siguientes líneas:** cada línea (debe haber al menos X líneas) contendrá al menos Y caracteres separados por espacios en blanco donde:

+  ```A``` La letra A representa el punto inicial (solo puede haber uno)

+  ```B``` La letra B repreenta el punto final (solo puede haber uno)

+  ```.``` El caracter punto representa un espacio libre

+  ```#``` El caracter 'almohadilla' representa un obstáculo