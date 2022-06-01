void spinlock_aqcuire(bool *lock){
    //共有変数へのポインタを受け取りTASを用いてロックを獲得できるまでループ
    while (test_and_set(lock));
}

void apinlock_release(bool *lock){
    tas_release(lock);
}