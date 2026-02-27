#include <stdio.h>
#include <dirent.h>
#include <cJSON.h>
#include <stdlib.h>
#include <string.h>
#define TARGET_DIR "../target-test/"

int main(){
	struct dirent* de;
	DIR *dr = opendir(TARGET_DIR);
    if (dr == NULL) {
        printf("Не удалось открыть директорию" );
        return 0;
    }
    // Чтение всех файлов
    while ((de = readdir(dr)) != NULL){
    	if(strcmp(de->d_name, ".") == 0) continue;
   		if(strcmp(de->d_name, "..") == 0) continue;
    	char result[100] = {0x0};
    	snprintf(result, 100, "%s%s", TARGET_DIR, de->d_name);
    	printf("%s\n", result);
		FILE* json = fopen(result, "r");
		if (!json) {
			printf("not valid file %s", de->d_name);	
		}
		char *line = NULL;
		size_t len = 0;
		ssize_t read;

		while ((read = getline(&line, &len, json)) != -1) {
        	cJSON *json = cJSON_Parse(line);
        	char *string = cJSON_Print(json);
        	printf("%s", string);
        	free(string);
        	free(json);
	    }

	    free(line);
	    fclose(json);
    }

    closedir(dr);
	return 1;

}