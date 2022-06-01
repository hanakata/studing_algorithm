void spinlock_aqcuire(volatile bool *lock){
    for(;;){
        while (lock);
        if (!test_and_set(lock)){
            break;
        }
        
    }
}

void apinlock_release(bool *lock){
    tas_release(lock);
}