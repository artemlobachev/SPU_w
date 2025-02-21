#ifndef CFP_H
#define CFP_H
   
#include <stdio.h>
#include <stdio.h>
#include <stdarg.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define ORANGE "\033[33m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"
#define CYAN "\033[36m"
#define GREY "\033[37m"
#define RESET "\033[0m"


#define COLOR_PRINTF(COLOR, ...)    \
do                                   \
 {                                    \
    printf(COLOR __VA_ARGS__);         \
    printf(RESET);                      \
 } while(0)   

 #define COLOR_PUTS(COLOR, ...)    \
do                                   \
 {                                    \
    puts(COLOR __VA_ARGS__);         \
    puts(RESET);                      \
 } while(0)                          

#define PRINT_STARS puts("******************************************")

#define COLOR_PRINT_BETWEEN_STARS(COLOR, ...) COLOR_PRINTF(COLOR, __VA_ARGS__)
#define COLOR_PUTS_BETWEEN_STARS(COLOR, ...)  COLOR_PUTS  (COLOR, "**************\t" __VA_ARGS__ "\t**************")

/*---------------FOR HTML--------------------------------------*/

#define HEAD_WHITE       "<h1 style=\"color: white;\">"
#define HEAD_RED         "<h1 style=\"color: red;\">"
#define HEAD_LIGHT_GREEN "<h1 style=\"color: greenyellow;\">"

#define BACKGROUND_DARK_BLUE ""

#define HEAD_END "</h>"

#endif