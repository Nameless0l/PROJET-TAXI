#ifndef __HANDLER_H_INCLUDED__
#define __HANDLER_H_INCLUDED__

void init_handlers(void);
void handle_oc_scheduled(int signum, siginfo_t *info, void *context);

#endif //__HANDLER_H_INCLUDED__