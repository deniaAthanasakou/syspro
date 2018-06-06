#ifndef _SEARCH_H_
#define _SEARCH_H_

void searchHandler(int fd, char* command, char* save_dir);

char* createDocFile(char* save_dir);
void createJobExecutor(char* docFile, int fd, char* searchWords);

#endif