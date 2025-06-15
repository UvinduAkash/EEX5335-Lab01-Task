# EEX5335-Lab01-Task
# 🔁 Process Creation in C using fork() – Fibonacci Sequence (via WSL2)

This guide demonstrates how to set up a Linux development environment using WSL2 on Windows 11, write a C program that creates a child process using fork(), and generate a Fibonacci sequence from the child process. The parent process uses wait() to ensure synchronization.

---

## 🖥 System Setup

- *Operating System*: Windows 11 Pro (64-bit)
- *Linux Distribution*: Ubuntu 24.04 LTS (WSL2)
- *Terminal*: Ubuntu Bash (WSL2 maroon shell)
- *Compiler*: GCC (via build-essential)
- *Editor*: nano / Visual Studio Code (v1.101)

---

## ⚙ Step 1: Enable and Install WSL2 + Ubuntu

1. Open the Start Menu → search "Windows Features" → Open  
   ✅ Enable:
   - Windows Subsystem for Linux  
   - Virtual Machine Platform  
   Click OK and Restart the computer.

2. Open PowerShell as administrator and run:
   bash
   wsl --install
   

3. When Ubuntu opens:
   - Enter a username
   - Set a password

---

## 🔧 Step 2: Prepare the Ubuntu Environment

1. Update packages:
   bash
   sudo apt update && sudo apt upgrade
   

2. Install essential developer tools:
   bash
   sudo apt install build-essential
   

---

## 🧾 Step 3: Write the C Program using fork()

1. Create and open the C file:
   bash
   nano fibonacci_fork.c
   

2. Paste this C code:
   c
   #include <stdio.h>
   #include <stdlib.h>
   #include <unistd.h>
   #include <sys/wait.h>

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
       if (argc != 2) {
           fprintf(stderr, "Usage: %s <non-negative number>\n", argv[0]);
           return 1;
       }

       int n = atoi(argv[1]);
       if (n < 0) {
           fprintf(stderr, "Error: Please enter a non-negative number.\n");
           return 1;
       }

       pid_t pid = fork();

       if (pid < 0) {
           perror("fork failed");
           return 1;
       }
       else if (pid == 0) {
           printf("Child Process (PID: %d) generating Fibonacci:\n", getpid());
           generateFibonacci(n);
           exit(0);
       }
       else {
           wait(NULL);
           printf("Parent Process (PID: %d) waited for child to complete.\n", getpid());
       }

       return 0;
   }
   

3. Save and exit:
   - Press Ctrl+O → Enter → Ctrl+X

---

## 🛠 Step 4: Compile the Program

In the terminal:
bash
gcc fibonacci_fork.c -o fibonacci_fork


If there are no errors, an executable named fibonacci_fork will be created.

---

## ▶ Step 5: Run the Program

Run the program by passing a number of terms:
bash
./fibonacci_fork 7


Output:
bash
Child Process (PID: 2356) generating Fibonacci:
0 1 1 2 3 5 8 
Parent Process (PID: 2355) waited for child to complete.


---

## ❌ Common Mistakes

| Problem                       | Cause                              | Solution                                  |
|------------------------------|-------------------------------------|-------------------------------------------|
| gcc: command not found       | GCC not installed                   | Run sudo apt install build-essential    |
| -0: invalid option           | You typed -0 instead of -o      | Use -o fibonacci_fork                   |
| ./fibonacci_fork: not found  | File not compiled or wrong name     | Ensure gcc compiled successfully          |
| command not found: ./gcc     | Mistakenly typed ./gcc            | Just use gcc, not ./gcc               |

---

## 📂 Directory Structure


.
├── fibonacci_fork.c       # Source code
└── README.md              # Instructions and environment setup


---

## 📁 Accessing Files from Windows

If you create files using WSL2, you can access them from Windows via:

\wsl.localhost\Ubuntu\home\<your-username>\


Or use Visual Studio Code with the WSL extension to open your Ubuntu home directory directly.

---

## ✅ Summary

This project helped demonstrate:

- Using fork() to create child processes in C.
- Synchronizing execution using wait().
- Building and running C programs inside Ubuntu on Windows using WSL2.
- Common compilation and execution errors in Linux development environments.

---

## 👨‍💻 Author

P.L. Uvindu Perera  
Operating Systems Laboratory – The Open University of Sri Lanka  
GitHub Repository: https://github.com/your-username/fibonacci-fork-lab

> Replace your-username with your actual GitHub username.
