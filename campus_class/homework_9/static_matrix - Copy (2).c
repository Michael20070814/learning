#include<calc.h>
int main()
{
	int row = 0 , clm = 0 ;
	FILE* fpr = fopen("data.txt","r") ;
	fscanf(fpr , "%d%d" , &row , &clm) ;
	double arr[row][clm] ;
	for(int i = 0 ; i < row ; i++)
	{
		for(int j = 0 ; j < clm ; j++)
		{
			fscanf(fpr , "%lf" , &arr[i][j]) ;
		}
		
	}
	printf("%.0lf\n",MODE_SNGL(arr , row * clm)) ;
	fclose(fpr);
	return 0 ;
}