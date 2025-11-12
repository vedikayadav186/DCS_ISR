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