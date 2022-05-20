bool lock = false;

void some_func(){
    retry:
        if (!lock){
            lock = true;
        }else{
            goto retry;
        }
        lock = falses
}