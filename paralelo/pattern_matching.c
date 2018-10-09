/**
 * Lucas Bergmann
 * Programação Paralela 2018/2
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <ctype.h>

/**
 * Disponível em: https://www.geeksforgeeks.org/wildcard-character-matching/
 */
 
// The main function that checks if two given strings 
// match. The first string may contain wildcard characters 
bool match(char *first, char * second) { 
  // If we reach at the end of both strings, we are done 
  if (*first == '\0' && *second == '\0') 
    return true; 
  
  // Make sure that the characters after '*' are present 
  // in second string. This function assumes that the first 
  // string will not contain two consecutive '*' 
  if (*first == '*' && *(first+1) != '\0' && *second == '\0') 
    return false; 
  
  // If the first string contains '?', or current characters 
  // of both strings match 
  if (*first == '?' || *first == *second) 
    return match(first+1, second+1); 
  
  // If there is *, then there are two possibilities 
  // a) We consider current character of second string 
  // b) We ignore current character of second string. 
  if (*first == '*') 
    return match(first+1, second) || match(first, second+1); 
  return false; 
} 


/**
 * Disponível em: https://stackoverflow.com/questions/1841758/how-to-remove-punctuation-from-a-string-in-c?noredirect=1&lq=1
 */
void remove_punct_and_make_lower_case(char *p) {
  char *src = p, *dst = p;

  while (*src) {
    if (ispunct((unsigned char)*src)) {
      /* Skip this character */
      src++;
    } else if (isupper((unsigned char)*src)) {
      /* Make it lowercase */
      *dst++ = tolower((unsigned char)*src);
      src++;
    } else if (src == dst) {
      /* Increment both pointers without copying */
      src++;
      dst++;
    } else {
      /* Copy character */
      *dst++ = *src++;
    }
  }

  *dst = 0;
}

int main(void) {
  char x[1024];
  char pattern[100];

  printf("WILDCARD PATTERN MATCHING - SEQUENCIAL");
  printf("\n\nDigite o padrão desejado: ");
  scanf("%s", pattern);

  printf("\n\n");

  FILE *arquivo;
  arquivo = fopen("texto.txt", "r");

  if (arquivo == NULL)
    return EXIT_FAILURE;

  int i = 0;
  int countPatternFound = 0;
  while(fscanf(arquivo, "%s", x) == 1) {
    i++;
    // Transforma em lower case e remove caracteres especiais (exceto acentuação)
    remove_punct_and_make_lower_case(x);
    
    bool result = match(pattern, x);
    if(result){
      countPatternFound++;
    }
    printf("%d. Padrão: %s ; Palavra: %s -> Resultado: %s\n", i, pattern, x, result?"Yes": "No");
  }

  fclose(arquivo);

  printf("\nFIM DA EXECUÇÃO\n");
  printf("O PADRÃO OCORREU %d VEZES\n", countPatternFound);
  
  return EXIT_SUCCESS;
}
