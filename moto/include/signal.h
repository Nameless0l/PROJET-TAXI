#ifndef __SIGNAL_H__
#define __SIGNAL_H__

int random_integer(int a, int b);
int starting_course(pid_t client_pid);
void ended_course(pid_t client_pid);
void bike_handler(int signum);
void send_signal(pid_t oc_pid, int sig);
void set_handler();

#endif //__SIGNAL_H__