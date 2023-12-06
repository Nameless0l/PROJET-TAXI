#ifndef __CLIENT__H__
#define __CLIENT__H__


// Set handlers for signals
void set_handlers();
void client_wait(int n);
void client_handler(int sig);
Client *generate_client();
int random_integer(int a, int b);
void create_memory(pid_t client_pid);
void write_client_infos(Client *client);
void free_shm(pid_t client_pid);
void print_client(Client *client);
void print_client_segment();

#endif //__CLIENT__H__