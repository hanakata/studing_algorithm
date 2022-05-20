bool lock = false;

void some_func(){
    retry:
    if (!test_and_set(&lock)){
        
    }else{
        goto entry;
    }
    tas_release($lock)
}