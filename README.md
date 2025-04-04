🧠 Philosophers

🗒️ Overview
The Philosophers project explores the classic Dining Philosophers Problem, a synchronization problem involving 
shared resources (forks) and concurrent threads (philosophers). The goal is to simulate a realistic solution 
while avoiding common pitfalls like deadlocks, race conditions, and starvation.

👨‍🏫 The Rules
Five philosophers sit at a round table. Each has a plate and a fork to their left and right. 
They must alternate between:

Thinking 🧠
Eating 🍝 (requires two forks: left and right)
Sleeping 😴

Constraints:
A philosopher must pick up both forks to eat.
Philosophers must not die of starvation.
Use threads and mutexes only.
Avoid deadlocks and data races.

🔧 How to Compile & Run
🧱 Build the program
  - make
  - ./philo [num_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: num_of_times_each_philo_must_eat]
📘 Example
  ./philo 5 800 200 200
  This runs a simulation with 5 philosophers:
    800ms before dying
    200ms to eat
    200ms to sleep

🧵 Threads & Synchronization
Each philosopher is a thread.
Mutexes represent forks (to prevent simultaneous access).
One monitor thread checks for death conditions.
