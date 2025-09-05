<div align="center">
	<picture>
		<img src="https://github.com/ayogun/42-project-badges/blob/main/badges/pipexm.png" alt="42 The Pipex school project with a bonus badge.">
	</picture>  

<p><a href="https://www.hive.fi/en/curriculum">Hive (42 School Network)</a> core curriculum project</p>  
<h1>Pipex</h1>  

</div>

Pipex is a C programming project that recreates the behavior of Unix shell pipelines.  
The goal is to implement a program that mimics the following shell command:

```bash
< infile cmd1 | cmd2 > outfile
```

<div align="center">
	<picture>
		<img src="https://raw.githubusercontent.com/github/explore/main/topics/c/c.png" alt="C programming" height="80">
	</picture> 
</div>

---

#### Core topics:
1. **Unix system calls.**  
   * Using `pipe()`, `fork()`, `dup2()`, `execve()`, and `waitpid()`.  
   * Understanding file descriptors and process creation.  

2. **Input/Output redirection.**  
   * Reading from an input file.  
   * Redirecting output into a file.  

3. **PATH resolution.**  
   * Searching for executables inside the environment variable `PATH`.  

4. **Error handling.**  
   * Gracefully handling cases like missing files or invalid commands.  
   * Clear exit codes and error messages.  

---

### Project structure:
```css
pipex/
│
├── include/
│   └── pipex.h           # Header file
│
├── src/
│   ├── pipex.c           # Main program
│   ├── process.c         # Child process handling
│   ├── utils.c           # Helper functions
│   └── path_utils.c      # PATH resolution
│
├── Makefile              # Build system
├── README.md             # Documentation
└── .gitignore
```

---

### Where to start
1. Clone the repository:
```bash
git clone https://github.com/<your-username>/pipex.git
cd pipex
```

2. Build the program:
```bash
make
```

3. Run with arguments:
```bash
./pipex infile "cmd1" "cmd2" outfile
```

Example:
```bash
./pipex infile "ls -l" "wc -l" outfile
```
Equivalent to:
```bash
< infile ls -l | wc -l > outfile
```

---

### Mind map
```mermaid
mindmap
  root((Pipex))
    Goal
      Simulate shell pipelines
      Use low-level syscalls
    Syscalls
      fork
      pipe
      dup2
      execve
      waitpid
    Features
      Input redirection
      Output redirection
      Error handling
    Usage
      Compile: make
      Run: ./pipex infile "cmd1" "cmd2" outfile
    Example
      "ls -l" | "wc -l"
    Structure
      pipex.c
      process.c
      utils.c
      pipex.h
```

---

### Developed by
**Your Name**  
[LinkedIn](https://www.linkedin.com) • [GitHub](https://github.com/<your-username>)  
