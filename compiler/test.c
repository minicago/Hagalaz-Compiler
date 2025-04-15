
int foo(int a[][4]){
    
}

int main(){
    const int a[1 + 1][2] = {1, 1, 1, 2 + 2};
    int b[a[1][1]][a[1][1]];
    foo(b);
}