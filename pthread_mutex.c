/*
Jon
5.3.6
*/

#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define MIN_PID 300
#define MAX_PID 5000

/* Declare an integer array with 4701 slots for pids */
int pid_array [4701];
int last;
int threadNumber = 0;
pthread_mutex_t mutex;

/* The function below creates and initializes an array data structure for representing pids */
int allocate_map(void) {
  int i;
  for (i = 0; i <=(MAX_PID - MIN_PID); i++) {
    pid_array[i] = 0;
  }
  last = 0;
  if (pid_array[4700] == 0) {
    return 1;           // return 1 if successful
  } else {
    return -1;          // return —1 if unsuccessful
  }
}

/* The function below allocates and returns a pid */
int allocate_pid(void) {
  int i = 0;        // Loop counter
  int next;         // Pointer to next pid
  if (last == MAX_PID) {
    next = MIN_PID;
  } else {
    next = last + 1;
  }
  while ((i <= (MAX_PID - MIN_PID)) && (pid_array[next] == 1)) {
    ++i;
    ++next;
    if (next > MAX_PID) {
      next = MIN_PID;
    }
  }
  if (i == (MAX_PID - MIN_PID) + 1) {
      return -1;      // return — 1 if unable to allocate a pid (all pids are in use)
  }
  pid_array[next] = 1;
  last = next;
  return last + 300;
}

/* The function below releases a pid */
void release_pid(int pid) {
  pid_array[pid - 300] = 0;
}

// We need this function to avoid the array from over filling up
int PID_slot_number(int pid){
  return pid_array[pid - 300];
}

/////////////////////////////////////////////////////////

void * process(void* param) {
  int pid = allocate_pid();
  while (threadNumber < 100) {
    pthread_mutex_lock(&mutex);
    if (threadNumber >= 100) {
      pthread_mutex_unlock(&mutex);
      break;
    }
    threadNumber++;
    printf("Ran thread for process %d\n", threadNumber);
    pthread_mutex_unlock(&mutex);
  }
  release_pid(pid);
}

int main() {
  pthread_t thread[100];
  int i = 0;
  for(i = 0; i < 100; i++) {
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&thread[i], NULL, process, NULL);
    process(NULL);
  }
  for(i = 0; i < 100; i++) {
    pthread_join(thread[i], NULL);
    pthread_mutex_destroy(&mutex);
  }
  return 0;
}
