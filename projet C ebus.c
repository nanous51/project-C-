#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 struct Passager* pass=NULL;
 struct Reservation* res=NULL;
 struct the_bus* b=NULL;

typedef struct {
    int j,m,a;
}date;
typedef struct {
    int h,m,s;
}heure;
typedef struct the_bus {
    int idbus,nb_place_dispo;
    int place_dispo[150];
    char dest[100];
    date datedep;
    heure heuredep;
    int nbserv;
    char services[20][101];
    struct the_bus *suiv;
}the_bus  ;
 typedef struct  Reservation {
    int idreservation,idbus,num_place;
    char nompass[100],mdp[40];
    struct Reservation *suiv;
}Reservation;
 typedef struct Passager {
    int idpass, num_tel;
    char nompass[50],email[50],mdpp[40];
    struct Passager *suiv;
} Passager;
int buscpm = 0;
int rescpm = 0;
int passcpm = 0;

/////////////////////////////////////////////////////////////////fonction

/////ajout passager dans fichier

struct Passager* CreateOpenpassager() {
    FILE* file = fopen("passfich.bin", "ab+");
    struct Passager * head = NULL;

    struct Passager p;
    while (fread(&p, sizeof(struct Passager), 1, file) == 1) {
        struct Passager * newNode = (struct Passager *)malloc(sizeof(struct Passager));
        memcpy(newNode, &p, sizeof(struct Passager));
        newNode->suiv = head;
        head = newNode;
    }
    fclose(file);

    return head;
}

/////ajout bus dans fichier
struct the_bus* CreateOpenbus() {
    FILE* file = fopen("busfich.bin", "ab+");
    struct the_bus * head = NULL;

    struct the_bus* b ;
    while (fread(&b, sizeof(struct the_bus), 1, file) == 1) {
        struct the_bus * newNode = (struct the_bus *)malloc(sizeof(struct the_bus));
        memcpy(newNode, &b, sizeof(struct the_bus));
        newNode->suiv = head;
        head = newNode;
    }
    fclose(file);

    return head;
}

//////ajout reservation dans fichier

struct Reservation* CreateOpenreservation() {
    FILE* file = fopen("resfich.bin", "ab+");
    struct Reservation* head = NULL;

    struct Reservation res;
    while (fread(&res, sizeof(struct Reservation), 1, file) == 1) {
        struct Reservation * newNode = (struct Reservation *)malloc(sizeof(struct Reservation));
        memcpy(newNode, &res, sizeof(struct Reservation));
        newNode->suiv = head;
        head = newNode;
    }
    fclose(file);

    return head;
}
/////////sauvegarde les listesdans les fichiers

void ReadWritepassager(struct Passager * tete) {
    FILE* file = fopen("passbin.bin", "wb");

    struct Passager * current = tete;

    while (current != NULL) {
        fwrite(current, sizeof(struct Passager), 1, file);
        current = current->suiv;
    }

    fclose(file);
}

void ReadWritebus(struct the_bus* tete) {
    FILE* file = fopen("busfich.bin", "wb");

    struct the_bus* current = tete;

    while (current != NULL) {
        fwrite(current, sizeof(struct the_bus), 1, file);
        current = current->suiv;
    }

    fclose(file);
}

void ReadWritereservation(struct Reservation* tete) {
    FILE* file = fopen("resfich.bin", "wb");

    struct Reservation* current = tete;

    while (current != NULL) {
        fwrite(current, sizeof(struct Reservation), 1, file);
        current = current->suiv;
    }

    fclose(file);
}


/////creation nouveau compte

void nouveau_compte() {

    Passager *p = (Passager *)malloc(sizeof(Passager));
    printf("veuillez entrer votre nom s'il vous plait : \n");
    scanf("%s",&p->nompass);
    printf("veuillez entrer votre e-mail : \n");
    scanf("%s", &p->email);
    printf("veuillez entrer votre numero de telephone :\n ");
    scanf("%d",  &p->num_tel);
    printf("et maintenant choississez un mot de passe convenable :\n ");
    scanf("%s",  &p->mdpp);
     printf("patientez un peu \n ");
    p->idpass =passcpm+1;
    p->suiv = NULL;
     printf("compte est crée avec succées.\n votre identifiant est le suivant :\n%d\n",p->idpass);


}
/////creaction d'un compte bus

void creerbus() {
    the_bus *p = (the_bus *)malloc(sizeof(the_bus));
    printf("veuillez entrer l'identifiant du bus :\n ");
    scanf("%d",  &p->idbus);
    printf("combien de place est-t-il disponible  :\n ");
    scanf("%d",  &p->nb_place_dispo);
   printf("veuillez entrer la destination du bus :\n ");
   for (int i = 0; i < p->nb_place_dispo; i++)p->place_dispo[i]=0;
    scanf("%s",  &p->dest);
     printf("Quelle est la date de depart (sous  la format jj/mm/aaaa svp ):\n ");
    scanf("%d/%d/%d",  &p->datedep.j,&p->datedep.m,&p->datedep.a);
    printf("Quel est l'heure de depart (sous  la format hh:mm:ss svp):\n ");
    scanf("%d:%d:%d",  &p->heuredep.h,&p->heuredep.m,&p->heuredep.s);
    printf("veuillez entrer le nombre de service dans ce bus :\n ");
    scanf("%d",  &p->nbserv);

    printf("veuillez entrer les services existants dans le bus :\n ");
    for (int i = 0; i < p->nbserv; i++)
    scanf("%s",  &p->services[i]);

}
/////ajout details du bus

void details_bus(const char *busfich) {
    FILE *f= fopen("busfich", "rb");
    the_bus *q;
    while (fread(q, sizeof(the_bus), 1, f) == 1) {
         printf("Identifiant : %d\n Destination : %s\n nombre de places disponibles : %d\n les numeros des places disponibles dans le bus:",
               q->idbus, q->dest,q->nb_place_dispo);
        for (int i = 0; i < q->nb_place_dispo; i++)
         if(q->place_dispo[i]==0)
          printf("%d,",i+1);
          printf("\n");
         printf("date de depart: %d/%d/%d à  %d:%d:%d\n  servises valables: \n", q->datedep.j, q->datedep.m,q->datedep.a,q->heuredep.h,q->heuredep.m,q->heuredep.s);
         for (int i = 0; i < q->nbserv; i++)
          printf("-%s,",q->services[i]);
           printf("\n");


    } free(q); fclose(f); }

//////faire la reservation

void faire_reservation() {

   Reservation *p = (Reservation *)malloc(sizeof(Reservation));
    printf("Entrez le nom du voyageur: ");
    scanf("%s", &p->nompass);
    printf("les bus disponibles sont :\n");

    int nbr=0;the_bus *l=b;
    while(nbr==0){
    nbr=0;l=b;
    printf("Entrez l'identifiant du bus choisi : ");
    scanf("%d\n", &p->idbus);

     while (nbr==0 & l!=NULL){
        if(l->place_dispo[p->num_place]==0&& l->idbus==p->idbus)
        nbr++;
         l=l->suiv;
    }
        if(nbr==0)printf("Oups bus complet!");
    }
    int nb=1;the_bus *h=b;
    while(nb==1){
     h=b;
    nb=0;
    printf("Entrez le numero de la place choisi : ");
    scanf("%d\n", &p->num_place);
    while (nb==0 & h!=NULL){
        if(h->place_dispo[p->num_place]==1&& h->idbus==p->idbus)
        nb++;
        h=h->suiv;
    }
    if(nb==1)
    printf("place deja reservee.\n");}
    printf("reservation faite avec succee\n");

}



/////recherche de reservation existante

Reservation* recherche_reservation(int id , char mtdp[50] ){

    Reservation* re=res;
    int nb=0;
    while(re->suiv!=NULL){

        if(re->idreservation==id&&re->mdp==mtdp)return re;
        re=re->suiv;
    }


        if(re->mdp==mtdp ){
            if( re->idreservation==id)
            return re;}
        else {

            return NULL;
        }

}

/////modificartion de la reservation

void modifier_la_reservation() {
    int id;
    char modp[50];
     printf("veuillez entrer votre identifiant:\n");
     scanf("%d",&id);
     printf("veuillez entrer votre mot de passe:\n");
     scanf("%s",&modp);
    Reservation *p = recherche_reservation(id,modp);

    if (p!= NULL) {
        int x=0;
        while(x!=1&&x!=2){
         printf("si vous voulez changer le bus tapez 1 sinon si vous voulez changer votre emplacement (numero d eplace) taper 2 \n");
         scanf("%d",&x);}
        if(x==1){
            int nbr=0,i=0;the_bus *l=b;int idt;
    while(nbr==0){
    nbr=0;l=b;
    printf("veuillez entrer l'identifiant du nouveau bus \n: ");

    scanf("%d",idt);

     while (nbr==0 && l!=NULL){
         i=0;

         while(nbr==0 & l!=NULL&&i<l->nb_place_dispo&& l->idbus==idt){
        if(l->place_dispo[i]==0)
        nbr++;

        i++;}
         l=l->suiv;

    }
        if(nbr==0)printf("non, ce bus est plein choisissez un autre \n");
    else{


    int nb=1;the_bus *h=b;int num_plc;
    while(nb==1){

     h=b;
    nb=0;
    printf("veuillez entrer le numero de la place choisi dans le nouveau bus  : ");
    scanf("%d", &num_plc);
    while (nb==0 & h!=NULL){
        if(h->place_dispo[num_plc]==1&& h->idbus==idt)
        nb++;
        h=h->suiv;
    }
    if(nb==1)
    printf("cette place est auparavant reservée choississez une autre.\n");}
     p->idbus=idt;
      p->num_place = num_plc;
    printf("successful modification!\n");}

        }}
    else if(x==2){
        int num_plc;
int nb=1;the_bus *h=b;
    while(nb==1){

     h=b;
    nb=0;
    printf("veuiller entrer votre nouveau choix de l'emplacement :\n ");
    scanf("%d", &num_plc);
    while (nb==0 & h!=NULL){
        if(h->place_dispo[num_plc]==1&& h->idbus==p->idbus)
        nb++;
        h=h->suiv;
    }
    if(nb==1)
    printf("desolé cette place est deja reservée .\n");}

      p->num_place = num_plc;
    printf("successful modification\n");}

        }





else {

        printf("veuillez faire votre reservation d'abord .\n");
    }

}

////code principale

int test,mod, carry;
int main() {
    pass=CreateOpenpassager();
    res=CreateOpenreservation();
    b=CreateOpenbus();

    printf("si vous etes un employée veuillez entrer 1 sinon si vous etes un voyageur veuillez choisir 2\n");
    scanf("%d",&test);
    if(test==1){
    creerbus();}

    else if (test==2 ){
    nouveau_compte();
    faire_reservation();
    printf("veuillez modifier quelque chose ? si oui taper 1 sinon taper 0");
    scanf("%d",&mod);
    if(mod==1)
    modifier_la_reservation();
    else if (mod==0)
        {
            printf("reservation terminée ! A trés bientot!");
        }
    } ;
    ReadWritepassager(pass);
    ReadWritebus(b);
    ReadWritereservation(res);
    return 0;
    }

