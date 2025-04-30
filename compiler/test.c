int f(int a){
    if(a==1) return 1;
    if(a==2) return 1;
    return f(a-1) + f(a-2);
}

int a = 2;

int main(){
    return f(a);
    
}