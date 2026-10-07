#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define N 10

union semun {
    int val;
};

int main() {

    key_t key_sem = ftok("semfile", 65);
    key_t key_shm = ftok("shmfile", 75);

    int semid = semget(key_sem, 2, IPC_CREAT | 0666);
    int shmid = shmget(key_shm, N * sizeof(int), IPC_CREAT | 0666);

    int *shared = (int*) shmat(shmid, NULL, 0);

    union semun arg;
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg); // roditelj može da piše

    arg.val = 0;
    semctl(semid, 1, SETVAL, arg); // dete čeka

    struct sembuf P0 = {0, -1, 0};
    struct sembuf V0 = {0, 1, 0};

    struct sembuf P1 = {1, -1, 0};
    struct sembuf V1 = {1, 1, 0};

    if (fork() == 0) {
        // ===== DETE =====
        while (1) {
            semop(semid, &P1, 1);

            int sum = 0;
            for (int i = 0; i < N; i++)
                sum += shared[i];

            if (shared[0] == -1)
                break;

            printf("Zbir: %d\n", sum);

            semop(semid, &V0, 1);
        }

        shmdt(shared);
        exit(0);
    }
    else {
        // ===== RODITELJ =====
        FILE *f = fopen("brojevi.txt", "r");
        if (!f) {
            perror("Greska pri otvaranju fajla");
            exit(1);
        }

        while (1) {
            semop(semid, &P0, 1);

            int i;
            for (i = 0; i < N; i++) {
                if (fscanf(f, "%d", &shared[i]) != 1)
                    break;
            }

            if (i == 0) {
                shared[0] = -1; // signal za kraj
                semop(semid, &V1, 1);
                break;
            }

            while (i < N) {
                shared[i++] = 0;
            }

            semop(semid, &V1, 1);
        }

        wait(NULL);

        fclose(f);
        shmdt(shared);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);
    }

    return 0;
}
