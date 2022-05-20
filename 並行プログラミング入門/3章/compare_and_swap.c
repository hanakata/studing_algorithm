bool compare_and_swap(uint64_t *p, uint64_t val, uint64_t newval){
    if (*p != val){
        return false;
    }
    *p = newval;
    return true;
}