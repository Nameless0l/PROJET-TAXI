#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <signal.h>
#include <sys/shm.h>
#include <math.h>

#define CREATED_CLIENT 0x1
#define CLIENT_GONE 0x2
#define MAX_WAIT_TIME 10
#define MIN_WAIT_TIME 3
#define MAX_PRICE 10000
#define BIKE_ASSIGNED 0xC
#define STARTED_COURSE 0x3
#define ENDED_COURSE 0x4
#define TO_MYSELF 0x10
#define NB_QUARTER 113
#define SEG_SIZE 1024
#define TASK_TIME 1
#define CLIENT_WAIT_TIME 30

typedef enum QUARTER_YAOUNDE
{
    OMNISPORT,
    POLYTECH,
    TRAVAUX,
    FMSB,
    CENTRE_COMMERCIAL_ELIG_ESSONO,
    ETOA_MEKI,
    NLONGKAK,
    ELIG_EDZOA,
    BASTOS,
    MANGUIER,
    TONGOLO,
    MBALLA,
    NKOLONDOM,
    ETOUDI,
    MESSASSI,
    OKOLO,
    OLEMBO,
    NYOM,
    EMANA,
    NKOLETON,
    CITE_VERTE,
    MADAGASCAR,
    MOKOLO,
    GRAND_MESSA,
    EKOUDOU,
    TSINGA,
    NKOM_KANA,
    OLIGA,
    MESSA_CARRIERE,
    ECOLE_DE_POLICE,
    FOUDA,
    NGOSSO,
    ELEVEUR,
    MFANDENA,
    NKOL_MESSING,
    NKOL_EBOGO,
    MELEN,
    NKOL_BIKOK,
    ELIG_EFFA,
    OYOM_ABANG,
    ETETAK,
    OBILI,
    NGOA_EKELE_1,
    NLONG_MVOLYE,
    AHALA_1,
    EFOULAN,
    OBOBOGO,
    NSAM,
    MELAN_2_CENTRE_ADMINISTRATIF,
    ETOA_NKOLMESSENG_1,
    AFANOYA_1,
    AFANOYA_2,
    AFANOYA_3,
    AFANOYA_4,
    NKOLFON_MEKOUMBOU_2,
    NTOUESSONG_MEKOUMBOU_1,
    AHALA_2,
    NSIMEYONG_1,
    NSIMEYONG_2,
    NSIMEYONG_3,
    OLEZOA,
    DAKAR,
    NGOA_EKELE_2,
    MVAN_NORD,
    NDAMVOUT,
    MESSAME_NDONGO,
    ODZA,
    EKOUMDOUM,
    AWE,
    NKOMO,
    EKOUNOU,
    BITENG,
    KONDENGUI_1,
    MIMBOMAN_1,
    ETAM_BAFIA,
    MVOG_MBI,
    NKOL_NDONGO_2,
    MEBANDAN,
    MVAN_SUD,
    EKIE,
    EMOMBO,
    KONDENGUI_2,
    KONDENGUI_3,
    NKOL_NDONGO_1,
    MIMBOMAN_3,
    NTUI_ESSONG,
    NKOLO,
    MVOG_ADA,
    NGOUSSO,
    NGOSSO_NTEM,
    NGOULMEKONG,
    MELEN_8B_ET_C,
    ETOUG_EBE_2,
    MVOG_BETSI,
    BIYEM_ASSI,
    MENDONG_2,
    MELAN_8,
    SIMBOCK,
    ETOUG_EBE_1,
    MELAN_ELIG_EFFA,
    NKOL_BIKOK_SIMBOCK,
    ECOLE_DE_GUERRE,
    ETETAK_2,
    OYOM_ABANG_2,
    NKOL_BISSON,
    MINKOAMEYOS,
    NKOLSO,
    NKOLM_MISSING,
    ESSOS,
    NGOUSSO_1,
    QUARTIER_GENERAL,
    ECOLE_NORMALE,
    NKOA_BANG
} quarter;

typedef struct client
{
    /*
        Definition of a client type, which will references our process: one client is a process

        pid is the process id of the client (as we said, it's a process)

        start and dest are quarters, element of an enumeration of all quarters of our town

        price in an integer which represents the price that client will pay if there is a bic that drive him to his dest
    */
    pid_t pid;
    quarter start;
    quarter dest;
    unsigned int price;
    time_t wait_time;
} Client;

extern pid_t oc_pid;
extern void *shared_mem;

#endif // __DEFINES_H__