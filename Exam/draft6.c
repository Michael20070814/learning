void invert (char str [] )
{
    int i,j, ;
    for(i=0,j=strlen(str), char k ='0';i<j;i++,j--)
    {
        k=str[i];
        str[i]=str[j];
        str[j]=k;
    }
}