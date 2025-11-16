double* convertTemperature(double celsius, int* returnSize) 
{
    double *ans;

    ans = (double *) malloc(2 * sizeof(double));
    ans[0] = celsius + 273.15;
    ans[1] = celsius * 1.80 + 32.00;
    returnSize[0] = ans[0];
    returnSize[1] = ans[1];
    
    free(ans);
    
    return returnSize;
}
