#include <stdio.h>
#include <string.h>
#include <ctype.h>


/* ============================================================
                         MEMBER 1
        FASTA INPUT + DNA VALIDATION + SEQUENCE INFORMATION
   ============================================================ */


/* Remove FASTA header and spaces/newlines */
void getDNA(char dna[])
{
    char line[5000];
    int firstLine = 1;
    int i, j = 0;

    printf("\nPaste FASTA sequence from NCBI.\n");
    printf("Enter the FASTA header and sequence.\n");
    printf("After pasting, press ENTER on an empty line.\n\n");

    while(1)
    {
        fgets(line, sizeof(line), stdin);

        /* Stop when user enters an empty line */
        if(line[0] == '\n')
            break;

        /* Ignore FASTA header */
        if(firstLine == 1 && line[0] == '>')
        {
            firstLine = 0;
            continue;
        }

        firstLine = 0;

        /* Copy only A, T, G and C */
        for(i = 0; line[i] != '\0'; i++)
        {
            char ch = toupper(line[i]);

            if(ch == 'A' || ch == 'T' || ch == 'G' || ch == 'C')
            {
                dna[j] = ch;
                j++;
            }
        }
    }

    dna[j] = '\0';
}


/* Check whether DNA contains only A, T, G and C */
int isValidDNA(char dna[])
{
    int i;

    if(strlen(dna) == 0)
        return 0;

    for(i = 0; dna[i] != '\0'; i++)
    {
        if(dna[i] != 'A' && dna[i] != 'T' &&
           dna[i] != 'G' && dna[i] != 'C')
        {
            return 0;
        }
    }

    return 1;
}


/* Display sequence information */
void sequenceInformation(char dna[])
{
    int length;

    length = strlen(dna);

    printf("\n--- Sequence Information ---\n");
    printf("DNA Sequence: %s\n", dna);
    printf("Length: %d nucleotides\n", length);
    printf("Complete codons: %d\n", length / 3);
}


/*
EXAMPLE OUTPUT FOR MEMBER 1

CODON TRANSLATOR & DNA SEQUENCE ANALYZER

Paste FASTA sequence from NCBI.

>NM_000207.3 Homo sapiens insulin (INS)
ATGGCCCTGTGGATGCGCCTCCTGCCCCTGCTGGCC

--- Sequence Information ---
DNA Sequence: ATGGCCCTGTGGATGCGCCTCCTGCCCCTGCTGGCC
Length: 39 nucleotides
Complete codons: 13

*/


/* ============================================================
                         MEMBER 2
              NUCLEOTIDE COUNT + PERCENTAGE
   ============================================================ */


/* Count A, T, G and C */
void countNucleotides(char dna[], int *a, int *t, int *g, int *c)
{
    int i;

    *a = 0;
    *t = 0;
    *g = 0;
    *c = 0;

    for(i = 0; dna[i] != '\0'; i++)
    {
        if(dna[i] == 'A')
            (*a)++;

        else if(dna[i] == 'T')
            (*t)++;

        else if(dna[i] == 'G')
            (*g)++;

        else if(dna[i] == 'C')
            (*c)++;
    }
}


/* Display nucleotide count and percentage */
void nucleotideAnalysis(char dna[])
{
    int a, t, g, c;
    int length;

    length = strlen(dna);

    countNucleotides(dna, &a, &t, &g, &c);

    printf("\n--- Nucleotide Count ---\n");
    printf("A = %d\n", a);
    printf("T = %d\n", t);
    printf("G = %d\n", g);
    printf("C = %d\n", c);

    printf("\n--- Nucleotide Percentage ---\n");

    printf("A = %.2f%%\n", (a * 100.0) / length);
    printf("T = %.2f%%\n", (t * 100.0) / length);
    printf("G = %.2f%%\n", (g * 100.0) / length);
    printf("C = %.2f%%\n", (c * 100.0) / length);
}


/*
EXAMPLE OUTPUT FOR MEMBER 2

--- Nucleotide Count ---
A = 8
T = 9
G = 12
C = 10

--- Nucleotide Percentage ---
A = 20.51%
T = 23.08%
G = 30.77%
C = 25.64%

*/


/* ============================================================
                         MEMBER 3
                 SHOW CODONS + START/STOP
   ============================================================ */


/* Display DNA in groups of three */
void showCodons(char dna[])
{
    int i;
    int length = strlen(dna);

    printf("\n--- Codons ---\n");

    for(i = 0; i + 2 < length; i = i + 3)
    {
        printf("%c%c%c ", dna[i], dna[i + 1], dna[i + 2]);
    }

    printf("\n");
}


/* Find ATG start codon */
void findStartCodon(char dna[])
{
    int i;
    int found = 0;
    int length = strlen(dna);

    printf("\n--- Start Codon ---\n");

    for(i = 0; i + 2 < length; i++)
    {
        if(dna[i] == 'A' &&
           dna[i + 1] == 'T' &&
           dna[i + 2] == 'G')
        {
            printf("ATG found at position %d\n", i + 1);
            found = 1;
        }
    }

    if(found == 0)
        printf("No ATG start codon found.\n");
}


/* Find TAA, TAG and TGA stop codons */
void findStopCodons(char dna[])
{
    int i;
    int found = 0;
    int length = strlen(dna);

    printf("\n--- Stop Codons ---\n");

    for(i = 0; i + 2 < length; i++)
    {
        if((dna[i] == 'T' && dna[i + 1] == 'A' && dna[i + 2] == 'A') ||
           (dna[i] == 'T' && dna[i + 1] == 'A' && dna[i + 2] == 'G') ||
           (dna[i] == 'T' && dna[i + 1] == 'G' && dna[i + 2] == 'A'))
        {
            printf("%c%c%c found at position %d\n",
                   dna[i], dna[i + 1], dna[i + 2], i + 1);

            found = 1;
        }
    }

    if(found == 0)
        printf("No stop codon found.\n");
}


/*
EXAMPLE OUTPUT FOR MEMBER 3

--- Codons ---
ATG GCC CTG TGG ATG CGC CTC CTG CCC CTG CTG GCC

--- Start Codon ---
ATG found at position 1
ATG found at position 13

--- Stop Codons ---
No stop codon found.

*/


/* ============================================================
                         MEMBER 4
                    DNA TO PROTEIN TRANSLATION
   ============================================================ */


/* Convert codon into amino acid */
char codonToAminoAcid(char codon[])
{
    /* Phenylalanine */
    if(strcmp(codon, "TTT") == 0 || strcmp(codon, "TTC") == 0)
        return 'F';

    /* Leucine */
    if(strcmp(codon, "TTA") == 0 || strcmp(codon, "TTG") == 0 ||
       strcmp(codon, "CTT") == 0 || strcmp(codon, "CTC") == 0 ||
       strcmp(codon, "CTA") == 0 || strcmp(codon, "CTG") == 0)
        return 'L';

    /* Isoleucine */
    if(strcmp(codon, "ATT") == 0 || strcmp(codon, "ATC") == 0 ||
       strcmp(codon, "ATA") == 0)
        return 'I';

    /* Methionine */
    if(strcmp(codon, "ATG") == 0)
        return 'M';

    /* Valine */
    if(strcmp(codon, "GTT") == 0 || strcmp(codon, "GTC") == 0 ||
       strcmp(codon, "GTA") == 0 || strcmp(codon, "GTG") == 0)
        return 'V';

    /* Serine */
    if(strcmp(codon, "TCT") == 0 || strcmp(codon, "TCC") == 0 ||
       strcmp(codon, "TCA") == 0 || strcmp(codon, "TCG") == 0 ||
       strcmp(codon, "AGT") == 0 || strcmp(codon, "AGC") == 0)
        return 'S';

    /* Proline */
    if(strcmp(codon, "CCT") == 0 || strcmp(codon, "CCC") == 0 ||
       strcmp(codon, "CCA") == 0 || strcmp(codon, "CCG") == 0)
        return 'P';

    /* Threonine */
    if(strcmp(codon, "ACT") == 0 || strcmp(codon, "ACC") == 0 ||
       strcmp(codon, "ACA") == 0 || strcmp(codon, "ACG") == 0)
        return 'T';

    /* Alanine */
    if(strcmp(codon, "GCT") == 0 || strcmp(codon, "GCC") == 0 ||
       strcmp(codon, "GCA") == 0 || strcmp(codon, "GCG") == 0)
        return 'A';

    /* Tyrosine */
    if(strcmp(codon, "TAT") == 0 || strcmp(codon, "TAC") == 0)
        return 'Y';

    /* Histidine */
    if(strcmp(codon, "CAT") == 0 || strcmp(codon, "CAC") == 0)
        return 'H';

    /* Glutamine */
    if(strcmp(codon, "CAA") == 0 || strcmp(codon, "CAG") == 0)
        return 'Q';

    /* Asparagine */
    if(strcmp(codon, "AAT") == 0 || strcmp(codon, "AAC") == 0)
        return 'N';

    /* Lysine */
    if(strcmp(codon, "AAA") == 0 || strcmp(codon, "AAG") == 0)
        return 'K';

    /* Aspartic acid */
    if(strcmp(codon, "GAT") == 0 || strcmp(codon, "GAC") == 0)
        return 'D';

    /* Glutamic acid */
    if(strcmp(codon, "GAA") == 0 || strcmp(codon, "GAG") == 0)
        return 'E';

    /* Cysteine */
    if(strcmp(codon, "TGT") == 0 || strcmp(codon, "TGC") == 0)
        return 'C';

    /* Tryptophan */
    if(strcmp(codon, "TGG") == 0)
        return 'W';

    /* Arginine */
    if(strcmp(codon, "CGT") == 0 || strcmp(codon, "CGC") == 0 ||
       strcmp(codon, "CGA") == 0 || strcmp(codon, "CGG") == 0 ||
       strcmp(codon, "AGA") == 0 || strcmp(codon, "AGG") == 0)
        return 'R';

    /* Glycine */
    if(strcmp(codon, "GGT") == 0 || strcmp(codon, "GGC") == 0 ||
       strcmp(codon, "GGA") == 0 || strcmp(codon, "GGG") == 0)
        return 'G';

    /* Stop codons */
    if(strcmp(codon, "TAA") == 0 ||
       strcmp(codon, "TAG") == 0 ||
       strcmp(codon, "TGA") == 0)
        return '*';

    return '?';
}


/* Translate DNA into protein */
void translateDNA(char dna[])
{
    int i;
    int length = strlen(dna);
    char codon[4];
    char aminoAcid;

    printf("\n--- DNA to Protein Translation ---\n");

    printf("Protein sequence: ");

    for(i = 0; i + 2 < length; i = i + 3)
    {
        codon[0] = dna[i];
        codon[1] = dna[i + 1];
        codon[2] = dna[i + 2];
        codon[3] = '\0';

        aminoAcid = codonToAminoAcid(codon);

        if(aminoAcid == '*')
            printf("*");
        else
            printf("%c", aminoAcid);
    }

    printf("\n");
}


/*
EXAMPLE OUTPUT FOR MEMBER 4

--- DNA to Protein Translation ---
Protein sequence: MALWMRLLLWA

*/


/* ============================================================
                              MAIN
                 FINAL COMBINED PROJECT
   ============================================================ */


int main()
{
    char dna[5000];
    int choice;

    printf("==============================================\n");
    printf("     CODON TRANSLATOR & DNA SEQUENCE ANALYZER\n");
    printf("==============================================\n");

    /*
       MEMBER 1:
       Get FASTA sequence from user
    */

    getDNA(dna);

    if(isValidDNA(dna) == 0)
    {
        printf("\nInvalid DNA sequence!\n");
        printf("No valid DNA sequence was found.\n");
        return 0;
    }

    printf("\nDNA sequence successfully loaded.\n");


    /* Main menu */

    while(1)
    {
        printf("\n====================================\n");
        printf("              MAIN MENU\n");
        printf("====================================\n");

        printf("1. Sequence Information\n");
        printf("2. Nucleotide Count + Percentage\n");
        printf("3. Show Codons\n");
        printf("4. Translate DNA to Protein\n");
        printf("5. Find Start/Stop Codon\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);


        /* MEMBER 1 */
        if(choice == 1)
        {
            sequenceInformation(dna);
        }


        /* MEMBER 2 */
        else if(choice == 2 )
        {
            nucleotideAnalysis(dna);
        }


        /* MEMBER 3 */
        else if(choice == 3)
        {
            showCodons(dna);
        }


        /* MEMBER 4 */
        else if(choice == 4)
        {
            translateDNA(dna);
        }


        /* MEMBER 3 */
        else if(choice == 5)
        {
            findStartCodon(dna);
            findStopCodons(dna);
        }


        /* EXIT */
        else if(choice == 6)
        {
            printf("\nThank you for using the DNA Sequence Analyzer!\n");
            break;
        }


        /* WRONG CHOICE */
        else
        {
            printf("\nInvalid choice! Please enter 1-6.\n");
        }
    }

    return 0;
}