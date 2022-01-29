# Philosophers
The aim of this project is to write a solution of the dining philosopher's problem - the classical problem of synchronization. The implementation bases on threads, mutexes and semaphores.
This is the project for School21 (Ecole 42).

## The programs take the following arguments:

- **number_of_philosophers**: The number of philosophers and also the number of forks.
- **time_to_die (in milliseconds)**: If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- **time_to_eat (in milliseconds)**: The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
- **time_to_sleep (in milliseconds)**: The time a philosopher will spend sleeping.
- **number_of_times_each_philosopher_must_eat (optional argument)**: If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
