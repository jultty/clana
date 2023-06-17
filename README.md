# clana

An application for data cleaning, gap detection and acquiring averages and linear regression calculations, specifically based on the data structures found in the National Water Agency's public systems.

Aplicação para limpeza de dados, detecção de lacunas, obtenção de médias e regressões lineares. Baseada especificamente para as estruturas de dados encontradas nos sistemas públicos da Agência Nacional das Águas.

## Compiling from source

[CMake](https://cmake.org/) version 3.0 or higher is needed in order to compile. It's available for several different operating systems.

Once CMake is set up, you can proceed with the following steps:

1. Download or clone this repository to your machine. The final path where you clone or extract the contents, where the file `CMakeLists.txt` as well as this `README.md` file are, will be referred to as the **source directory**.
2. Create a destination directory for the compiled files. This is your **build directory** and can be anywhere in your system.
3. In a terminal, execute the following command from the build directory:

```
cmake path/to/source/directory
```

Replace `path/to/source/directory` with the full path to the source directory.

This should produce several files in the build directory.

4. Run your preferred build tool to build the program. On Windows you can use CMake itself:

```
cmake --build .
```
Notice there is a `.` dot character after `--build`.

On Linux you can use either CMake or just `make`.

The final output should be something like "[100%] Built target clana". Once you see that, you are done and should have an executable file named `clana` in the build directory you just created.

----
Prototype developed for the Data Structures course, part of the Systems Analysis and Development program offered at the Federal Institute of São Paulo, Jacareí campus.

Protótipo desenvolvido para a disciplina de Estrutura de Dados, curso de Análise e Desenvolvimento de Sistemas do Instituto Federal de São Paulo, câmpus Jacareí.
