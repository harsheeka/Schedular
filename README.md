# OS Project: Process Scheduling with Round-Robin and Priority-Based Algorithms

## Project Description

This project is an implementation of **process scheduling** for an operating systems class. It simulates two popular scheduling algorithms: **Round-Robin** and **Priority-Based Scheduling**. The user can create multiple processes, provide their burst times and priorities, and then select which scheduling algorithm to run. The program will simulate the execution of the processes and calculate key performance metrics such as **average waiting time**.

## Features

- **Process Creation**: Dynamically creates a pool of processes, each with a unique Process ID (PID), burst time, and priority.
- **Round-Robin Scheduling**: Implements a time-sharing algorithm where processes are scheduled in a circular order with a predefined time quantum.
- **Priority-Based Scheduling**: Schedules processes based on their assigned priority, with higher-priority processes being executed first.
- **Interactive User Interface**: Allows users to:
  - Input process burst times and priorities.
  - Choose between Round-Robin or Priority Scheduling.
  - Provide additional parameters like time quantum for Round-Robin.
- **Performance Metrics**: Calculates and displays the average waiting time for both scheduling algorithms.
  
## File Structure

```
.
├── README.md                # Project description and instructions
├── process_scheduler.c       # Source code for process scheduling implementation
└── Makefile                 # Makefile for building the project
```

## How to Run

1. Clone this repository:

    ```bash
    git clone https://github.com/username/os-process-scheduler.git
    cd os-process-scheduler
    ```

2. Compile the code using the provided Makefile:

    ```bash
    make
    ```

3. Run the program:

    ```bash
    ./process_scheduler
    ```

4. Follow the on-screen prompts to:
   - Enter the number of processes and their burst times.
   - Enter priorities for the processes (only when using Priority Scheduling).
   - Select either Round-Robin or Priority Scheduling.
   - For Round-Robin, input the time quantum.
   
5. The program will output the execution order, remaining burst times, and the **average waiting time** for the chosen scheduling algorithm.

## Example Usage

```
Enter number of processes: 3
Process 1 burst time: 10
Process 2 burst time: 5
Process 3 burst time: 8

Choose scheduling algorithm:
1. Round-Robin
2. Priority-Based
Choice: 1

Enter time quantum for Round-Robin: 3

Output:
Process execution order: [1, 2, 3, 1, 3]
Average waiting time: 6.2
```

## Requirements

- **C compiler** (e.g., GCC)
- **Make** for building the project

## Future Enhancements

- Add support for more scheduling algorithms (e.g., Shortest Job First, First-Come First-Serve).
- Implement priority inversion handling.
- Add graphical visualization of process scheduling.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

Feel free to contribute to this project by forking the repository and submitting a pull request!

---

### Contact

For any questions or suggestions, please feel free to contact me at [your-email@example.com].
