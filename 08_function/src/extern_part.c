
int sum(int i, int j){
    return i + j;
}

static int static_method(int num) {
    int result = num * 2;
    return (result);     // <==> return result;
}

void update_prt(int* const p){
    *p = 12302;
}