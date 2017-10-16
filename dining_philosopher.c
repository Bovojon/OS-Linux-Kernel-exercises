/*
Jon
Project2
*/

#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PHILOSOPERS_NUM 5
// Philosophers are THINKING, then become HUNGRY so they start EATING
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT_PHILOSOPHER (philosopher_number+4)%PHILOSOPERS_NUM
#define RIGHT_PHILOSOPHER (philosopher_number+1)%PHILOSOPERS_NUM

pthread_mutex_t mutex;
pthread_cond_t cond_var[PHILOSOPERS_NUM];
pthread_t threadID[PHILOSOPERS_NUM];

// Declare the functions
void * philospher(void *num);
void pickup_forks(int);
void return_forks(int);
void philosopher_can_eat(int);
int state[PHILOSOPERS_NUM];
int philosophers[PHILOSOPERS_NUM]={0,1,2,3,4};

void *philospher(void *num) {
  while(1) {
    int x = rand() % 3;
    int *i = num;
    sleep(x+1);
    printf("%d seconds waited...\n", x+1);
    pickup_forks(*i);
    return_forks(*i);
  }
}

void pickup_forks(int philosopher_number) {
  // Lock first
  pthread_mutex_lock (&mutex);
  // Make philosopher hungry
  state[philosopher_number] = HUNGRY;
  printf("Philosopher %d is Hungry now \n", philosopher_number+1);
  // Get what the philosopher is doing
  philosopher_can_eat(philosopher_number);
  // Wait if she is eating
  if (state[philosopher_number] != EATING){
    pthread_cond_wait(&cond_var[philosopher_number], &mutex);
  }
  // Else, unlock and sleep for 5 seconds
  pthread_mutex_unlock (&mutex);
}

void return_forks(int philosopher_number) {
  // Lock first
  pthread_mutex_lock (&mutex);
  // Make philosopher thinking
  state[philosopher_number] = THINKING;
  printf("Philosopher %d is putting forks %d and %d down. She is thinking now. \n", philosopher_number+1, LEFT_PHILOSOPHER+1, philosopher_number+1);
  philosopher_can_eat(LEFT_PHILOSOPHER);
  philosopher_can_eat(RIGHT_PHILOSOPHER);
  pthread_mutex_unlock (&mutex);
}

void philosopher_can_eat(int philosopher_number) {
  // Check the state of the philosophers
  // If a philosopher is hungry, then if her LEFT_PHILOSOPHER and RIGHT_PHILOSOPHER are not eating then she can eat
  if (state[philosopher_number] == HUNGRY && state[LEFT_PHILOSOPHER] != EATING && state[RIGHT_PHILOSOPHER] != EATING) {
    state[philosopher_number] = EATING;
    printf("Philosopher %d is picking up fork %d and %d. She is eating now \n", philosopher_number+1, LEFT_PHILOSOPHER+1, philosopher_number+1);
    pthread_cond_signal(&cond_var[philosopher_number]);
  }
}

int main() {
    int i;
    time_t t;
    srand((unsigned) time(&t));
    pthread_t threadID[PHILOSOPERS_NUM];
    // Set them all to thinking initially
    for(i=0; i < PHILOSOPERS_NUM; i++) {
      state[i] = THINKING;
      pthread_cond_init(&cond_var[i], NULL);
    }
    pthread_mutex_init (&mutex, NULL);
    for(i=0; i < PHILOSOPERS_NUM; i++) {
      // Create a pthread
      pthread_create(&threadID[i], NULL, philospher, &philosophers[i]);
      printf("Philosopher %d is thinking now \n", i+1);
    }
    for(i=0; i<PHILOSOPERS_NUM; i++) {
      pthread_join(threadID[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
}
