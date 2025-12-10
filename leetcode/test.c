 && path[i + 1] != '.')
        {   
            num--; 
            i++;
        }
        else if (path[i] == '.' && path[i + 1] == '.' && path[i + 2] != '.')
        {
            if (i < 2)
                num = num - 1;
            else
            {    
                for (n = 2; path[i - n] != '/'; n++)
                    continue;
                num = num - n - 1;
            }
            i = i + 2;
        }