#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

struct poruka {
    long tip;
    int broj;
};

int zbirovi(int n) {
    int zbir = 0;
    if (n < 0) n = -n;
    while (n > 0) {
        zbir += n % 10;
        n /= 10;
    }
    return zbir;
}

int main() {
    key_t key = ftok("red", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if(msgid == -1) { perror("msgget"); exit(1); }

    if(fork() == 0) {
        // DETE
        FILE *f = fopen("rezultat.txt", "w");
        if(!f){ perror("fopen"); exit(1); }

        struct poruka p;
        int brojac=0;
        while(1) {
    msgrcv(msgid, &p, sizeof(int), 1, 0); // prima tip 1
    if(p.broj == 0) break;
    if(brojac<10)
    {
    fprintf(f, "Broj: %d -> zbir cifara: %d\n", p.broj, zbirovi(p.broj));
    brojac++;}
}

        fclose(f);
        exit(0);
    } else {
        // RODITELJ
        struct poruka p;
        p.tip = 1;

        for(int i = 0; i < 10; i++) {
            printf("Unesi broj: ");
            scanf("%d", &p.broj);
            msgsnd(msgid, &p, sizeof(int), 0); // šalje svaki broj posebno
        }

        // šalje završnu poruku
        p.broj = 0;
        msgsnd(msgid, &p, sizeof(int), 0);

        // uklanja queue
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}
