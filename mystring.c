#include "mystring.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#define TEST 1

string *init_string()
{
	string *buf = (string*)calloc(1, sizeof(string));
	if(!buf)
		return NULL;
	
	buf->add_string = &add_string;
	buf->add_string_from_terminal = &add_string_from_terminal;
	buf->free_string = &free_string;

	return buf;
}

size_t add_string(string *str, const char *_data)
{
	char *str_data_buf = NULL;

	// _data boşsa veya MAX_STRING_SIZE'dan büyükse 0 döndür.
	if(_data == NULL || (strlen(_data) + str->size) > MAX_STRING_SIZE) 	
		return 0;
	
	// str'ın data üyesi boşsa hafıza tahsisi ile _data'yı üyeye ekle.
	if(str->size == 0) {	
		if ((str->data = strdup(_data)) == NULL) {
			return 0;
		} else {
			str->size = strlen(str->data)+1;
			return str->size;
		}
	}
	
	//'str->data' doluysa sonuna bir boşlukla beraber '_data' yı ekle.
	if((str_data_buf = strdup(str->data)) == NULL) {
		return 0;
	} else {
		free(str->data);
		str->data = NULL;
		
		str->data = (char *)calloc(((strlen(str_data_buf) + strlen(_data)) + 1), sizeof(char));
		if(str->data == NULL) {
			free(str_data_buf);
			return 0;
		} else {
			sprintf(str->data, "%s %s", str_data_buf, _data);
			str->size = strlen(str->data) + 1;
			free(str_data_buf);
			str_data_buf = NULL;
			return (size_t)(strlen(str->data) + 1);
		}
	}		
}

size_t add_string_from_terminal(string *str) {		// BURASI İLE İLGİLEN!
	char *string_data_buf = NULL;
	char *input_buf = NULL;
	size_t input_buf_size = 0;
	
	// Kullanıcıdan 'MAX_STRING_SIZE - str->size' kadar giriş alınabilir.  
	// Bunun için önce 'buf' için hafızadan alan alıp daha sonra bu alana kullanıcıdan
	// bilgi alacağız. Tabi her şey yolunda giderse :)
	if ((input_buf = (char *)calloc((MAX_STRING_SIZE - str->size),sizeof(char))) == NULL) {
		if (TEST)
			fprintf(stderr, "Hata: input_buf %d\n", __LINE__);
		return 0;
	}
	if (fgets(input_buf, (MAX_STRING_SIZE - str->size), stdin) == NULL) {
		if (TEST)
			fprintf(stderr, "Hata: fgets %d\n", __LINE__);

		free(input_buf);
		input_buf = NULL;
        	return 0;
    	}

	//Buraya kadar 'buf için hafızadan alan aldık ve kullanıcıdan buraya giriş yapmasını istedik.
	// fgets giriş sırasında \n karakterini de değişkene aktarıyor, biz de bunu istemiyoruz.
	// O yüzden \n karakterini bulup onu NULL ile değiştirelim. 
	char *new_line = strchr(input_buf, '\n');
	if (new_line != NULL) {
        	*new_line = '\0';
	}

	input_buf_size = strlen(input_buf);
	if (input_buf_size == 0){
		if (TEST)
			fprintf(stderr, "Hata: input_buf_size %d\n", __LINE__);

		free(input_buf);
		input_buf = NULL;
		return 0;
	}
	
	// Eğer 'data' için ilk değer verilecekse bunu burada yapıyoruz. 
    	if (str->data == NULL) {
		if (TEST)
			fprintf(stderr, "Hata: str->data bos %d\n", __LINE__);

        	if ((str->data = strdup(input_buf)) == NULL) {
			if (TEST)
				fprintf(stderr, "Hata: %d\n", __LINE__);
			free(input_buf);
			input_buf = NULL;
			return 0;
		} else {
			free(input_buf);
			input_buf = NULL;
			str->size = input_buf_size + 1;
			return input_buf_size;
		}
	} else {
		if ((string_data_buf = (char *)calloc((input_buf_size + str->size + 1), sizeof(char))) == NULL) {
			if (TEST)
				fprintf(stderr, "Hata: string_data_buf %d\n", __LINE__);
			free(input_buf);
			input_buf = NULL;
			return 0;
		} else {
			strcpy(string_data_buf, str->data);
			strcat(string_data_buf, " ");
			strcat(string_data_buf, input_buf);


			free(str->data);
			free(input_buf);

			str->data = string_data_buf;
			str->size = strlen(str->data) + 1;
			return input_buf_size;
		}
    	}
}

void free_string(string *str)
{
	if(str->data != NULL){
		free(str->data);
		str->data = NULL;
	}
	if(str != NULL) {
		free(str);
		str = NULL;
	}
}
