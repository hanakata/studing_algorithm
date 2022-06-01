#define NUM 10
void semaphore_aqcuire(volatile int *cnt){
    for(;;){
        while(*cnt >= NUM);
        __sync_fetch_and_add(cnt, 1);
        if(*cnt <= NUM){
            break;
        }
        __sync_fetch_and_sub(cnt, 1);
    }
}

void semaphore_release(int *cnt){
    __sync_fetch_and_sub(cnt, 1);
}