√_This is a **21 School/Ecole 42** Project_

# Philosophers

Multithreading in C. Dining philosophers task.

# Rules
    • One or more philosophers sit at a round table.
        There is a large bowl of spaghetti in the middle of the table.
    • The philosophers alternatively eat, think, or sleep.
        While they are eating, they are not thinking nor sleeping;
        while thinking, they are not eating nor sleeping;
        and, of course, while sleeping, they are not eating nor thinking.
    • There are also forks on the table. There are as many forks as philosophers.
    • Because serving and eating spaghetti with only one fork is very inconvenient, a
        philosopher takes their right and their left forks to eat, one in each hand.
    • When a philosopher has finished eating, they put their forks back on the table and
        start sleeping. Once awake, they start thinking again. The simulation stops when
        a philosopher dies of starvation.
    • Every philosopher needs to eat and should never starve.
    • Philosophers don’t speak with each other.
    • Philosophers don’t know if another philosopher is about to die.
    • No need to say that philosophers should avoid dying
    • In mandatory part each philosopher is a thread.
    • In bonus part each philosopher is a process.

## Project goals

1. Deadlock avoiding.
2. Data race avoiding.

## How to run
Go to philo or philo_bonus directory and type:
1. philo:

        make && ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep 
        [number_of_times_each_philosopher_must_eat]
 
2. philo_bonus:

        make bonus && ./philo_bonus number_of_philosophers time_to_die time_to_eat
        time_to_sleep [number_of_times_each_philosopher_must_eat]
*in [] listed optional parameter
