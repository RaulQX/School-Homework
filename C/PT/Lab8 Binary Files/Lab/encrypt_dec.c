//***Modifies initial file to be a multiple of 128***//

#include <x86intrin.h>
#include <stdio.h>
#include <string.h>

#define LCS _lrotl
#define RCS _lrotr
#define u64 unsigned long long
#define R(x, y, k) (x=RCS(x, 8), x+=y, x^=k, y=LCS (y ,3) ,y^=x)
#define INV_R(x, y, k) (y^=x, y=RCS (y, 3), x^=k, x-=y, x=LCS(x, 8))
#define ENCRYPT 1

void Speck128ExpandKeyAndEncrypt (u64 pt[], u64 ct[], u64 K[])
{
    u64 i, B=K [1], A=K[0];
    ct [0] = pt[0];
    ct [1] = pt[1];

    for (i=0; i <32; i++)
    {
        R (ct [1], ct[0], A);
        R (B, A, i);
    }
}

void Speck128Encrypt (u64 pt[], u64 ct[], u64 k[])
{
    u64 i;

    ct[0] = pt [0];
    ct[1] = pt[1];

    for (i = 0; i <32; i++)
        R (ct[1], ct[0], k[i]);
}

void Speck128Decrypt (u64 pt[], u64 ct[], u64 K[])
{
    long long i;

    for (i = 31; i >= 0; i--)
        INV_R (ct [1], ct [0], K[i]);
}


static void speck_keyexpand (u64 K[]) 
{
    u64 tmp [32], *p;
    memcpy (tmp, K, sizeof tmp);

    u64 i;

    for (i = 0; i < (31) ;)
    {
        p = tmp + (1 + (i % (2 - 1)));
        R (*p, tmp [0], i);
        ++i;
        K[i] = tmp [0];
    }
}

void fill_k (char *s, u64 k[])
{
    int len = strlen(s);
    int i;

    u64 a=0;
    u64 b=0;

    for (i = 0; i < len/2; i++)
        a += s[i];

    for (; i<len; i++)
        b += 2*s[i];

    k[0] = a*b;
    k[1] = b;
}

int main (int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Please format the command line arguments as such:\n");
        printf("%s <file_to_read> {[encrypt] or [anything else]}\n", argv[0]);
        printf("Where if you write encrypt you encrypt the file or anything else then you decrypt it\n");
        exit(2);
    }

    u64 k[32];
    char keyboard_buffer[100];

    printf("Please introduce the key\n");
    scanf("%100s", keyboard_buffer);

    fill_k(keyboard_buffer, k);

    printf("%llx %llx\n", k[0],k[1]);

    FILE *fp = fopen (argv[1], "rb+");
    if (!fp)
    {
        printf("Couldnt open file for reading\n");
        exit(1);
    }

    FILE *fp2 = fopen (argv[2], "wb");
    if (!fp2)
    {
        printf("Couldnt open file for writing\n");
        exit(3);
    }

    u64 pt[2];
    u64 ct[2];

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    fseek(fp, 0, SEEK_SET);

    speck_keyexpand (k);
    
	fseek(fp, 0, SEEK_END);

    while (size%128!=0)
    {
    	char c = ' ';
    	size++;
    	fwrite(&c, 1, 1,fp);
    }

    fseek(fp, 0, SEEK_SET);
    
    while(fread(pt, sizeof(pt), 1, fp))
    {
        ct[1] = 0x0;
        ct[0] = 0x0;

        if (!strcmp(argv[2], "encrypt"))
        {
            Speck128Encrypt (pt, ct, k);
            fwrite(ct, sizeof(ct), 1, fp2);
        }

        else
        {
            Speck128Decrypt (pt, pt, k);
            fwrite(pt, sizeof(pt), 1, fp2);
        }
    }
    
    fclose(fp);
    fclose(fp2);

    return 0;
}
