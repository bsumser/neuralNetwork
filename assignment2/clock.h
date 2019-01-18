#ifndef CLOCK_H_
#define CLOCK_H_

typedef struct {
  // TODO: Define your ASCII clock data structure here. 
} ClockType;

// Initialize the clock data structure 
void initClock( ClockType *clock );

// Print an ASCII clock showing cur_time as the time 
void printClock( const time_t cur_time, const ClockType *clock );

// Free up any dynamically allocated memory in the clock
void cleanClock( ClockType *clock);

#endif /* CLOCK_H_ */