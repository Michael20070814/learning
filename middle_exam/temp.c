if (n > 15)
    {
        a = 1;
    }
    else if (n > 7)
    {
        a = 2;
    }
    else if (n > 3)
    {
        a = 3;
    }
    else if (n > 1)
    {
        a = 4
    }
    else
        a = 5;
if (n > 15)
    {
        for (int s = 15; s < n && input[s] != -1; s++)
        {
            if (continue_add(s, input) - input[0] == targetsum)
                value *= 0;
        }
    }
    else if (n > 7)
    {
        for (int s = 7; s < n && input[s] != -1; s++)
        {
            if (continue_add(s, input) - input[0] == targetsum)
                value *= 0;
        }
    }
    else if (n > 3)
    {
        for (int s = 3; s < n && input[s] != -1; s++)
        {
            if (continue_add(s, input) - input[0] == targetsum)
                value *= 0;
        }
    }
    else if (n > 1)
    {
        for (int s = 1; s < n && input[s] != -1; s++)
        {
            if (continue_add(s, input) - input[0] == targetsum)
                value *= 0;
        }
    }
    else