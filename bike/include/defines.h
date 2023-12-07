#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <time.h>

#define STARTED_COURSE 0x3
#define SEGMENT_READY 0xa
#define TASK_TIME_MIN 5
#define TASK_TIME_MAX 10
#define SEG_SIZE 1024
#define BIKE_CREATED 0x5
#define NB_QUARTER 110
#define RADIUS 5
#define ENDED_COURSE 0x4
#define WAIT_TIME 1 

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
}Quarter;

typedef struct Bike
{
   pid_t pid;
   Quarter start;
   Quarter itinerary[5];
}Bike;

extern Bike *bike;
extern pid_t oc_pid;
extern int shm_id;	// id of area
extern void *shm_zone;	//attach area
extern key_t shm_key;	// clief of area
extern char *quartier[111];


#endif // __DEFINES_H__