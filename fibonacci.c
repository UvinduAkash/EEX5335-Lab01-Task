#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to generate and print Fibonacci sequence up to n terms
void generateFibonacci(int n) {
    int first = 0, second = 1, next;

    if (n >= 1) printf("%d ", first);
    if (n >= 2) printf("%d ", second);

    for (int i = 3; i <= n; i++) {
        next = first + second;
        printf("%d ", next);
        first = second;
        second = next;
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    // Check if user entered the number of terms as a command line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative number>\n", argv[0]);
        return 1;
    }

    // Convert input to integer
    int n = atoi(argv[1]);

    // Check if the input is a non-negative number
    if (n < 0) {
        fprintf(stderr, "Error: Please enter a non-negative number.\n");
        return 1;
    }

    // Create a child process using fork()
    pid_t pid = fork();

    // Error occurred during fork
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    // Child process
    else if (pid == 0) {
        printf("Child Process (PID: %d) is generating Fibonacci sequence:\n", getpid());
        generateFibonacci(n);
        exit(0); // Always good to exit explicitly in child
    }

    // Parent process
    else {
        // Parent waits for the child to complete using wait()
        wait(NULL);
        printf("Parent Process (PID: %d) waited for child to finish.\n", getpid());
    }

    return 0;
}
