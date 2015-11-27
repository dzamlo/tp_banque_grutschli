/*********
** uti.h
** Utilities
** Loïc Damien et Simon Menetrey
** 27.11.2015
**********/
#ifndef UTIL_H
#define UTIL_H

#define CHECK_EXIT(condition, msg) \
  if (condition) {                 \
    perror(msg);                   \
    exit(EXIT_FAILURE);            \
  }

#endif
