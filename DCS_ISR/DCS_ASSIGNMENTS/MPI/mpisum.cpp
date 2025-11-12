#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    int rank, size;
    const int N = 16;  // Total number of elements
    std::vector<int> data;
    int elements_per_proc;

    MPI_Init(&argc, &argv);               // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get current process ID
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get total number of processes

    elements_per_proc = N / size;

    std::vector<int> sub_data(elements_per_proc);

    if (rank == 0) {
        data.resize(N);
        for (int i = 0; i < N; ++i) {
            data[i] = i + 1;
        }

        std::cout << "Full array: ";
        for (int i = 0; i < N; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    // Scatter the data to all processes
    MPI_Scatter(data.data(), elements_per_proc, MPI_INT,
                sub_data.data(), elements_per_proc, MPI_INT,
                0, MPI_COMM_WORLD);

    // Each process computes its partial sum
    int partial_sum = 0;
    for (int i = 0; i < elements_per_proc; ++i) {
        partial_sum += sub_data[i];
    }

    std::cout << "Process " << rank << " calculated partial sum: " << partial_sum << std::endl;

    // Reduce all partial sums to get the final sum at root
    int total_sum = 0;
    MPI_Reduce(&partial_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Root process displays the final result
    if (rank == 0) {
        std::cout << "Total sum calculated using MPI: " << total_sum << std::endl;
    }

    MPI_Finalize(); // Finalize the MPI environment
    return 0;
}

// without vector
// #include <mpi.h>
// #include <iostream>

// int main(int argc, char* argv[]) {
//     int rank, size;
//     const int N = 16;  // Total number of elements
//     int data[N];       // Full array (used by root process)
//     int elements_per_proc;
//     int sub_data[100]; // Sub-array for each process (max size placeholder)

//     MPI_Init(&argc, &argv);               // Initialize MPI
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get current process ID
//     MPI_Comm_size(MPI_COMM_WORLD, &size); // Get total number of processes

//     elements_per_proc = N / size;

//     // Initialize data only at root process
//     if (rank == 0) {
//         for (int i = 0; i < N; i++) {
//             data[i] = i + 1;
//         }

//         std::cout << "Full array: ";
//         for (int i = 0; i < N; i++) {
//             std::cout << data[i] << " ";
//         }
//         std::cout << std::endl;
//     }

//     // Scatter data among all processes
//     MPI_Scatter(data, elements_per_proc, MPI_INT,
//                 sub_data, elements_per_proc, MPI_INT,
//                 0, MPI_COMM_WORLD);

//     // Each process calculates its partial sum
//     int partial_sum = 0;
//     for (int i = 0; i < elements_per_proc; i++) {
//         partial_sum += sub_data[i];
//     }

//     std::cout << "Process " << rank << " calculated partial sum: " << partial_sum << std::endl;

//     // Reduce all partial sums to get the final sum at root
//     int total_sum = 0;
//     MPI_Reduce(&partial_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

//     // Root process prints total
//     if (rank == 0) {
//         std::cout << "Total sum calculated using MPI: " << total_sum << std::endl;
//     }

//     MPI_Finalize(); // Finalize MPI environment
//     return 0;
// }



/* 
Microsoft MPI v10.1.3
https://www.microsoft.com/en-us/download/details.aspx?id=105289
in system variable -> path -> C:\Program Files\Microsoft MPI\Bin -> add new
in CMD 
mpiexec -help
search for x64 native (\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools>)
if not then
https://visualstudio.microsoft.com/downloads/
scroll down -> Build Tools for Visual Studio 2022 download this 
Desktop development with C++
✅ Make sure all these are checked on the right side:

✅ MSVC v143 - VS 2022 C++ x64/x86 build tools

✅ Windows 10 or 11 SDK (10.0.22000 or newer)

✅ C++ CMake tools for Windows

✅ C++ ATL and MFC (optional)

✅ MSBuild and C++ profiling tools

setup done
Press Start → search x64 Native Tools Command Prompt for VS 2022

cd C:\DCS

cl /EHsc mpisum.cpp /I "C:\Program Files (x86)\Microsoft SDKs\MPI\Include" /link /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" msmpi.lib /out:mpisum.exe

mpiexec -n 4 sum_mpi.exe
*/

