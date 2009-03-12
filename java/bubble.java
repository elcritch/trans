{
    int i;
    int j;
    int v;
    int[10] a;
    a[0]=12; a[1]=11; a[2]=14; a[3]=17; a[4]=15;
    a[5]=5;  a[6]=19; a[7]=2;  a[8]=0;  a[9]=16;
    i=0;
    while (i<10) {
        j=i;
        v=i;
        while (j<10) {
            if (a[j]<a[v])
                v=j;
            j=j+1;
        }
        {
            int t;
            t=a[i];
            a[i]=a[v];
            a[v]=t;
        }
        i=i+1;
    }
    i=0;
    while (i<10) {
        write a[i];
        i=i+1;
    }
}
