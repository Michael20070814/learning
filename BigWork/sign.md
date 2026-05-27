fseek(fp, 0, SEEK_END);
long fsize = ftell(fp);
fseek(fp, 0, SEEK_SET);