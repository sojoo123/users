int addressMap(int VA)
{
    // INVALID ADDRESS

    if(VA >= 100)
    {
        PI = 2;

        return -1;
    }

    // PAGE NUMBER

    int pageNo = VA / 10;

    // OFFSET

    int offset = VA % 10;

    // PAGE TABLE ENTRY

    int pte = PTR + pageNo;

    // PAGE NOT PRESENT

    if(memory[pte][0] == '*')
    {
        PI = 3;

        return -1;
    }

    // GET FRAME NUMBER

    int frame =
        (memory[pte][2]-'0')*10 +
        (memory[pte][3]-'0');

    // PHYSICAL ADDRESS

    int RA = frame*10 + offset;

    return RA;
}
