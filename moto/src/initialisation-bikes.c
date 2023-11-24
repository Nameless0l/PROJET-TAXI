#include "../include/defines.h"
#include "../include/signal.h"
#include "../include/initialisation_bikes.h"

char *quartier[111] = {
    "Centre_commercial",
    "Elig_Essono",
    "Etoa_MekiI",
    "Nlongkak",
    "Elig_Edzoa",
    "Bastos",
    "Manguier",
    "Tongolo",
    "MballaI",
    "MballaII",
    "Nkolondom",
    "Etoudi",
    "Messassi",
    "Okolo",
    "Olembe",
    "Nyom",
    "Etoa_MekiII",
    "MballaIII",
    "Emana",
    "Nkoleton",
    "CiteVerte",
    "Madagascar",
    "Mokolo",
    "GrandMessa",
    "Ekoudou",
    "Tsinga",
    "Nkom_Kana",
    "Oliga",
    "MessaCarrière",
    "EcoledePolice",
    "Febe",
    "Ntoungou",
    "Obili",
    "Ngoa_EkeleI",
    "NlongMvolye",
    "AhalaI",
    "Efoulan",
    "Obobogo",
    "Nsam",
    "MelenII_CentreAdministratif",
    "Etoa",
    "NkolmessengI",
    "AfanoyaI",
    "AfanoyaII",
    "AfanoyaIII",
    "AfanoyaIV",
    "Nkolfon",
    "MekoumbouII",
    "Ntouessong",
    "MekoumbouI",
    "AhalaII",
    "NsimeyongI",
    "NsimeyongII",
    "NsimeyongIII",
    "Olezoa",
    "Dakar",
    "Ngoa_EkeleII",
    "Mvan_Nord,"
    "Ndamvout",
    "Messame_Ndongo",
    "Odza",
    "Ekoumdoum",
    "Awae",
    "Nkomo",
    "Ekounou",
    "Biteng",
    "KondenguiI",
    "Mimboman_I",
    "Etam_Bafia",
    "Mvog_Mbi",
    "Nkol_NdongoII",
    "Mebandan",
    "Mvan_Sud",
    "Ekie",
    "Emombo",
    "KondenguiII",
    "KondenguiIII",
    "Nkol_NdongoI",
    "MimbomanIII",
    "Ntui_Essong",
    "Nkolo",
    "Abom",
    "Mvog_Ada",
    "Essos"
    "Nkol_Messing",
    "Nkol_Ebogo",
    "QuartierFouda",
    "NgoussoI",
    "Eleveur",
    "MfandenaI",
    "MfandenaII",
    "NgoussoIII",
    "Ngousso_Ntem",
    "Ngoulmekong",
    "MelenVIIIBetC",
    "Etoug_EbeII",
    "Mvog_betsi",
    "Biyem_Assi",
    "MendongII",
    "MelenVIII",
    "Simbock",
    "Etoug_EbeI",
    "Melen",
    "Elig_Effa",
    "Nkolbikok",
    "SimbockEcoledeguerre",
    "Etetak",
    "Oyom_Abang",
    "Nkolbisson",
    "Minkoameyos",
    "Nkolso"
    };

/**

**/
// Return a bike filled with his parameters
Bike *create_bike()
{
    Bike *bike = (Bike*)malloc(sizeof(Bike));

    // if alloc fails
    if(!bike) 
        return NULL;

    // Generating a itinerary filled with a random of 5 consecutives quarters
    int start = random_integer(0, NB_QUARTER - RADIUS);
    
    // Filling consecutives quarters
    for (int i = 0; i < RADIUS; i++)
        bike->itinerary[i] = start++;

    // Filling the new bike structure
    bike->pid = getpid(); // Getting pid process

    return bike;
}


void write_infos_bike(Bike *bike)
{
    memcpy(shm_zone, bike, sizeof(Bike));
}

void create_segment(pid_t pid)
{
    shm_id = shmget((key_t)pid, SEG_SIZE, IPC_CREAT | 0666);
    shm_zone = shmat(shm_id, NULL, 0);
}

    /*for (int i = 0; i < RADIUS; i++)
    {
        printf("%d\n", itinerary[i]);
        printf("%s\n", quartier[itinerary[i]]);
        
    }*/
    
    //struct_data* point = &data;
    //printf("%x\n",&data);
    //printf("%x\n",&point);
    //printf("%d\n",sd.pid); 
    //memcpy(point,shm_mem,sizeof(struct_data));
    //printf("%d\n",pid);
    //printf("%d\n", data.pid);
    //printf("%d\n", point->pid);


//This fonction will be use to create the signal to tell th OC that we finished 
    //the creation of the bike . . . 
    //The handler of this will be create by the C.O
    //kill(getppid(),SIGUSR1);
    //After we are going to use signal(SIGUSR1,handle)